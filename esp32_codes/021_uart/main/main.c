#include <stdio.h>
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TXD_PIN 4
#define RXD_PIN 5
#define RX_BUF_SIZE 1024

void uart_init(void) {
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_1, RX_BUF_SIZE, 0, 0, NULL, 0);
}

void send_msg(void) {
    char message[] = "rahul";
    printf("sending: %s\n", message);
    uart_write_bytes(UART_NUM_1, message, strlen(message));   // use strlen

    char incoming_message[RX_BUF_SIZE];
    memset(incoming_message, 0, sizeof(incoming_message));

    int len = uart_read_bytes(UART_NUM_1, (uint8_t *)incoming_message, RX_BUF_SIZE - 1, pdMS_TO_TICKS(500));
    if (len > 0) {
        incoming_message[len] = '\0';  // null terminate
        printf("received: %s\n", incoming_message);
    } else {
        printf("no data received\n");
    }
}

void delay(void){
    vTaskDelay(pdMS_TO_TICKS(10000));  // 10 seconds delay
}


void app_main(void) {
    uart_init();

    while (true) {
        
        send_msg();
        delay(); 
    }
}
