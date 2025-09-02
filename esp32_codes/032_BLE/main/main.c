/*
main.c 
BLE GATT Server using NimBLE on ESP32
 * Services:
 *  - Device Information Service (Manufacturer Name, Custom Write)
 *  - Battery Service (Battery Level with Notify)
 * */

#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "host/ble_hs.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"

// -----------------------------------------------------------------------------
// CONFIG
// -----------------------------------------------------------------------------
#define DEVICE_NAME "RAHUL_ESP32_BLE"
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

#define DEVICE_INFO_SERVICE   0x180A
#define MANUFACTURER_NAME     0x2A29

#define BATTERY_SERVICE       0x180F
#define BATTERY_LEVEL_CHAR    0x2A19
#define BATTERY_CCC_DESC      0x2902

static const char *TAG = "NimBLE";

// -----------------------------------------------------------------------------
// STATE VARIABLES
// -----------------------------------------------------------------------------
static uint8_t ble_addr_type;
static bool advertising_active = false;
static uint16_t batt_char_att_hdl;   // Handle for battery characteristic
static uint16_t conn_handle = 0;     // Active connection handle
static TimerHandle_t timer_handler = NULL;

static void ble_app_advertise(void);

// -----------------------------------------------------------------------------
// GATT CALLBACKS
// -----------------------------------------------------------------------------

// Battery read (simple fixed value)
static int battery_read(uint16_t conn_handle, uint16_t attr_handle,
                        struct ble_gatt_access_ctxt *ctxt, void *arg) {
    uint8_t battery_level = 85; // fixed value
    os_mbuf_append(ctxt->om, &battery_level, sizeof(battery_level));
    return 0;
}

// Battery CCCD (Client Characteristic Configuration Descriptor)
static uint8_t notify_config[2] = {0x01, 0x00};

static int battery_ccc_cb(uint16_t conn_handle, uint16_t attr_handle,
                          struct ble_gatt_access_ctxt *ctxt, void *arg) {
    if (ctxt->op == BLE_GATT_ACCESS_OP_READ_DSC) {
        os_mbuf_append(ctxt->om, &notify_config, sizeof(notify_config));
    } else {
        memcpy(notify_config, ctxt->om->om_data, ctxt->om->om_len);
    }
    if (notify_config[0] == 0x01) {
        ESP_LOGI(TAG, "Notifications enabled");
        xTimerStart(timer_handler, 0);
    } else {
        ESP_LOGI(TAG, "Notifications disabled");
        xTimerStop(timer_handler, 0);
    }
    return 0;
}

// Write characteristic
static int device_write(uint16_t conn_handle, uint16_t attr_handle,
                        struct ble_gatt_access_ctxt *ctxt, void *arg) {
    printf("Incoming message: %.*s\n", ctxt->om->om_len, ctxt->om->om_data);
    return 0;
}

// Manufacturer info
static int device_info(uint16_t conn_handle, uint16_t attr_handle,
                       struct ble_gatt_access_ctxt *ctxt, void *arg) {
    const char *manufacturer = "ESP32 Developer";
    os_mbuf_append(ctxt->om, manufacturer, strlen(manufacturer));
    return 0;
}

// -----------------------------------------------------------------------------
// GATT SERVICES
// -----------------------------------------------------------------------------
static const struct ble_gatt_svc_def gatt_svcs[] = {
    {
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid = BLE_UUID16_DECLARE(DEVICE_INFO_SERVICE),
        .characteristics = (struct ble_gatt_chr_def[]) {
            {
                .uuid = BLE_UUID16_DECLARE(MANUFACTURER_NAME),
                .flags = BLE_GATT_CHR_F_READ,
                .access_cb = device_info
            },
            {
                .uuid = BLE_UUID128_DECLARE(0x00,0x11,0x22,0x33,
                                            0x44,0x55,0x66,0x77,
                                            0x88,0x99,0xaa,0xbb,
                                            0xcc,0xdd,0xee,0xff),
                .flags = BLE_GATT_CHR_F_WRITE,
                .access_cb = device_write
            },
            {0}
        }
    },
    {
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid = BLE_UUID16_DECLARE(BATTERY_SERVICE),
        .characteristics = (struct ble_gatt_chr_def[]) {
            {
                .uuid = BLE_UUID16_DECLARE(BATTERY_LEVEL_CHAR),
                .flags = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_NOTIFY,
                .access_cb = battery_read,
                .val_handle = &batt_char_att_hdl,
                .descriptors = (struct ble_gatt_dsc_def[]) {
                    {
                        .uuid = BLE_UUID16_DECLARE(BATTERY_CCC_DESC),
                        .att_flags = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_WRITE,
                        .access_cb = battery_ccc_cb
                    },
                    {0}
                }
            },
            {0}
        }
    },
    {0}
};

// -----------------------------------------------------------------------------
// GAP EVENTS
// -----------------------------------------------------------------------------
static int ble_gap_event(struct ble_gap_event *event, void *arg) {
    switch (event->type) {
    case BLE_GAP_EVENT_CONNECT:
        ESP_LOGI(TAG, "GAP CONNECT %s",
                 event->connect.status == 0 ? "OK" : "FAILED");
        if (event->connect.status == 0) {
            conn_handle = event->connect.conn_handle;
        } else {
            ble_app_advertise();
        }
        break;

    case BLE_GAP_EVENT_DISCONNECT:
        ESP_LOGI(TAG, "GAP DISCONNECT");
        conn_handle = 0;
        ble_app_advertise();
        break;

    case BLE_GAP_EVENT_ADV_COMPLETE:
        ESP_LOGI(TAG, "GAP ADV COMPLETE -> restarting");
        ble_app_advertise();
        break;

    case BLE_GAP_EVENT_SUBSCRIBE:
        ESP_LOGI(TAG, "GAP SUBSCRIBE attr_handle=%d", event->subscribe.attr_handle);
        break;

    default:
        ESP_LOGD(TAG, "Unhandled GAP event %d", event->type);
        break;
    }
    return 0;
}

// -----------------------------------------------------------------------------
// ADVERTISING
// -----------------------------------------------------------------------------
static void ble_app_advertise(void) {
    if (advertising_active) return;

    struct ble_hs_adv_fields fields = {0};
    fields.flags = BLE_HS_ADV_F_DISC_GEN | BLE_HS_ADV_F_BREDR_UNSUP;
    fields.name = (uint8_t *)DEVICE_NAME;
    fields.name_len = DEVICE_NAME_LEN;
    fields.name_is_complete = 1;

    int rc = ble_gap_adv_set_fields(&fields);
    if (rc != 0) {
        ESP_LOGE(TAG, "Failed to set adv fields rc=%d", rc);
        return;
    }

    struct ble_gap_adv_params adv_params = {0};
    adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;
    adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;

    rc = ble_gap_adv_start(ble_addr_type, NULL, BLE_HS_FOREVER,
                           &adv_params, ble_gap_event, NULL);
    if (rc == 0) {
        advertising_active = true;
        ESP_LOGI(TAG, "Advertising started: %s", DEVICE_NAME);
    }
}

// -----------------------------------------------------------------------------
// SYNC + HOST
// -----------------------------------------------------------------------------
static void ble_app_on_sync(void) {
    int rc = ble_hs_id_infer_auto(0, &ble_addr_type);
    if (rc != 0) {
        ESP_LOGE(TAG, "Error determining address type rc=%d", rc);
        return;
    }
    ble_app_advertise();
}

static void host_task(void *param) {
    nimble_port_run();
    nimble_port_freertos_deinit();
}

// -----------------------------------------------------------------------------
// APP MAIN
// -----------------------------------------------------------------------------
void app_main(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "Initializing BLE stack");

    timer_handler = xTimerCreate("battery_timer", pdMS_TO_TICKS(5000),
                                 pdTRUE, NULL, NULL);

    nimble_port_init();
    ble_svc_gap_init();
    ble_svc_gatt_init();

    ble_gatts_count_cfg(gatt_svcs);
    ble_gatts_add_svcs(gatt_svcs);

    ble_hs_cfg.sync_cb = ble_app_on_sync;

    nimble_port_freertos_init(host_task);

    ESP_LOGI(TAG, "BLE initialization complete");
}
