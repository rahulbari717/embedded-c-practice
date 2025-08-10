/*
 * Q) 3 leds blinks using freeRTOS tasks
 * */

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void red_led_task(){
    printf("Red led on"); 
    vTaskDelay(1000);
}

void yellow_led_task(){

    printf("yellow led on"); 
    vTaskDelay(1000);
}

void blue_led_task(){

    printf("blue led on"); 
    vTaskDelay(1000);
}

void app_main(void)
{
    red_led_task(); 
    blue_led_task();
    yellow_led_task(); 
}
