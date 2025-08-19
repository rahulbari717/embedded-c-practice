#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "oled.h"
#include "esp_log.h"

#define I2C_MASTER_SCL_IO           (22)
#define I2C_MASTER_SDA_IO           (21)
#define I2C_MASTER_PORT             (0)
#define I2C_MASTER_FREQ_HZ          (100000)

static i2c_master_bus_handle_t bus_handle;
static i2c_master_dev_handle_t dev_handle;

static void i2c_master_init(void)
{
    i2c_master_bus_config_t bus_cfg = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_MASTER_PORT,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_cfg, &bus_handle));

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = SSD1306_I2C_ADDR,
        .scl_speed_hz = I2C_MASTER_FREQ_HZ,
    };
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle));
}

void app_main(void)
{
    i2c_master_init();
    
    esp_err_t ret = ssd1306_init(dev_handle);
    if (ret != ESP_OK) {
        printf("OLED init failed: %s\n", esp_err_to_name(ret));
        return;
    }
    
    
    printf("OLED initialized successfully\n");
    ssd1306_clear(dev_handle);

     // Test with simple text first
    while (1) {
        printf("Drawing text...\n");
        ssd1306_draw_text(dev_handle, 0, 0, "HELLO");
        vTaskDelay(pdMS_TO_TICKS(3000));
        
        ssd1306_clear(dev_handle);
        printf("Cleared display\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        
        ssd1306_draw_text(dev_handle, 0, 0, "rahul");
        vTaskDelay(pdMS_TO_TICKS(3000));
        
        ssd1306_clear(dev_handle);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}