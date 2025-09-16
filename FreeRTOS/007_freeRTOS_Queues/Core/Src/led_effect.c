/*
 * led_effect.c
 *
 *  Created on: Sep 9, 2025
 *      Author: Rahul B.
 */

#include "main.h"  

void LED_control(uint8_t led_mask)
{
    // LD1 = bit0, LD2 = bit1, LD3 = bit2, LD4 = bit3
    HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, (led_mask & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, (led_mask & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, (led_mask & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, (led_mask & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void led_effect_stop(void)
{
    for(int i=0; i<4; i++) xTimerStop(handle_led_timer[i], portMAX_DELAY); 
}

void led_effect(int n)
{
    led_effect_stop(); 
    xTimerStart(handle_led_timer[n-1], portMAX_DELAY); 
}

void turn_on_odd_leds(void)
{
    HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);

}

void turn_on_even_leds(void)
{
    HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
}

void turn_off_all_leds(void)
{
    HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);

}

void turn_on_all_leds(void)
{
    HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
}

void LED_effect1(void){
    static int flag =1; 
    (flag ^= 1) ? turn_off_all_leds() : turn_on_all_leds(); 
}

void LED_effect2(void){
    static int flag =1; 
    (flag ^= 1) ? turn_on_even_leds() : turn_on_odd_leds(); 
}

void LED_effect3(void){
    static int i = 0; 
    LED_control( 0x1 << (i++ %4));  
}

void LED_effect4(void){
    static int i = 0; 
    LED_control( 0x8 >> (i++ %4)); 
}
