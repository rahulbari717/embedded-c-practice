#include <stdio.h>
#include "nvs_flash.h"
#include "esp_log.h"
#include "wifi_connect.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_http_client.h"

static const char *TAG = "main";
extern const uint8_t cert[] asm("_binary_amazon_cer_start");

typedef struct chunk_payload_t
{
    uint8_t *buffer;
    int buffer_index;
} chunk_payload_t;

esp_err_t on_client_data(esp_http_client_event_t *evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
    {
        // ESP_LOGI(TAG, "Length=%d", evt->data_len);
        // printf("%.*s\n", evt->data_len, (char *)evt->data);
        chunk_payload_t *chunk_payload = evt->user_data;
        chunk_payload->buffer = realloc(chunk_payload->buffer, chunk_payload->buffer_index + evt->data_len + 1);
        memcpy(&chunk_payload->buffer[chunk_payload->buffer_index],(uint8_t *) evt->data, evt->data_len );
        chunk_payload->buffer_index = chunk_payload->buffer_index + evt->data_len;
        chunk_payload->buffer[chunk_payload->buffer_index] = 0;

        // printf("buffer******** %s\n",chunk_payload->buffer);

    }
    break;

    default:
        break;
    }
    return ESP_OK;
}

void fetch_quote()
{
    chunk_payload_t chunk_payload = {0};

    esp_http_client_config_t esp_http_client_config = {
        // .url = "https://www.movebank.org/movebank/service/public/json?entity_type=study",
        .url = "https://open-weather13.p.rapidapi.com/fivedaysforcast?latitude=21.244262&longitude=75.296381&lang=HI", 
        .method = HTTP_METHOD_GET,
        .cert_pem = (char*) cert, 
        .event_handler = on_client_data,
        .user_data = &chunk_payload};
    esp_http_client_handle_t client = esp_http_client_init(&esp_http_client_config);
    esp_http_client_set_header(client, "Contnet-Type", "application/json");
    esp_http_client_set_header(client, "x-rapidapi-key", "02fca18a5emsh664bf8b16dd2d80p16f3eajsnd29c6bf04b33");
    esp_http_client_set_header(client, "x-rapidapi-host", "open-weather13.p.rapidapi.com");
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK)
    {
        ESP_LOGI(TAG, "HTTP GET status = %d, result = %s\n",
                 esp_http_client_get_status_code(client),  chunk_payload.buffer);
    }
    else
    {
        ESP_LOGE(TAG, "HTTP GET request failed: %s", esp_err_to_name(err));
    }
    if(chunk_payload.buffer != NULL){
       free(chunk_payload.buffer); 
    }
    esp_http_client_cleanup(client);
    wifi_disconnect();
}


void app_main(void)
{
    esp_err_t ret;
    // api - https://www.movebank.org/movebank/service/public/json?entity_type=study

    ESP_LOGI(TAG, "Initializing NVS...");
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG, "NVS no free pages or new version found, erasing...");
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK(ret);
    ESP_LOGI(TAG, "NVS initialized.");

    wifi_connect_init(); 
    ESP_LOGI(TAG, "Initialized wifi...");

    ESP_ERROR_CHECK(wifi_connect_sta("Rahul", "rahul8459", 10000)); 
    
    fetch_quote();

}