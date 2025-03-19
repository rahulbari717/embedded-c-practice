
/*
 * main.c
 *
 *  Created on: Mar 19, 2025
 *      Author: Rahul B.
 */
#include "main.h"

// Global variables for Timer and UART
TIM_HandleTypeDef htimer2;
UART_HandleTypeDef huart2;

uint32_t pulse1_value = 25000;
uint32_t pulse2_value = 12500;
uint32_t pulse3_value = 6250;
uint32_t pulse4_value = 3125;
uint32_t ccr_content;

int main(void){

	uint16_t brightness = 0;

	HAL_Init();

	SystemClock_Config(SYSCLOCK_FREQ_50MHZ);

	GPIO_Init();

	UART2_Init();

	TIMER2_Init();
    
	if( HAL_TIM_PWM_Start(&htimer2, TIM_CHANNEL_1) != HAL_OK){
        Error_handler();
    }

	while(1){
		while(brightness < htimer2.Init.Period){
			brightness+=10;
			__HAL_TIM_SET_COMPARE(&htimer2, TIM_CHANNEL_1, brightness);
			HAL_Delay(1);
		}

		while(brightness > htimer2.Init.Period){
			brightness-=10;
			__HAL_TIM_SET_COMPARE(&htimer2, TIM_CHANNEL_1, brightness);
			HAL_Delay(1);
		}
	}

	return 0;
}
// UART Initialization Function
void UART2_Init() {
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;

    if (HAL_UART_Init(&huart2) != HAL_OK) {
        Error_handler();
    }
}

// GPIO Initialization Function
void GPIO_Init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef ledgpio;
    ledgpio.Pin = GPIO_PIN_5;
    ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
    ledgpio.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &ledgpio);
}

// Timer 2 Initialization Function (To be implemented)
void TIMER2_Init(void) {

    TIM_OC_InitTypeDef tim2PWM_Config;
	htimer2.Instance = TIM2;
    htimer2.Init.Period = 10000-1;
    htimer2.Init.Prescaler = 4999;

    if(HAL_TIM_PWM_Init(&htimer2) != HAL_OK){
    	Error_handler();
    }

    memset(&tim2PWM_Config,0, sizeof(tim2PWM_Config));

    tim2PWM_Config.OCMode = TIM_OCMODE_PWM1;
    // tim2PWM_Config.Polarity = TIM_OC_POLARITY_HIGH;
    tim2PWM_Config.OCPolarity = TIM_OCPOLARITY_HIGH;

    tim2PWM_Config.Pulse = 0;
    if(HAL_TIM_PWM_ConfigChannel(&htimer2, &tim2PWM_Config, TIM_CHANNEL_1)!= HAL_OK){
        Error_handler();
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
        ccr_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
        __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, ccr_content+pulse1_value);
    }

    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
        ccr_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
        __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_2, ccr_content+pulse2_value);
    }

    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3) {
        ccr_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);
        __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_3, ccr_content+pulse3_value);
    }

    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4) {
        ccr_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
        __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_4, ccr_content+pulse4_value);
    }
}


// Error Handler Function
void Error_handler(void) {
    while (1);
}

// System Clock Configuration Function
void SystemClock_Config(uint8_t clock_freq) {
    RCC_OscInitTypeDef osc_init;
    RCC_ClkInitTypeDef clk_init;
    uint32_t FLatency = 0;

    osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_HSI;
    osc_init.HSIState = RCC_HSI_ON;
    osc_init.LSEState = RCC_LSE_ON;
    osc_init.HSEState = RCC_HSE_ON;
    osc_init.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    osc_init.PLL.PLLState = RCC_PLL_ON;
    osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSI;

    switch (clock_freq) {
        case SYSCLOCK_FREQ_50MHZ:
            osc_init.PLL.PLLM = 16;
            osc_init.PLL.PLLN = 100;
            osc_init.PLL.PLLP = 2;
            osc_init.PLL.PLLQ = 2;
            osc_init.PLL.PLLR = 2;
            FLatency = FLASH_ACR_LATENCY_1WS;
            break;
        case SYSCLOCK_FREQ_84MHZ:
            osc_init.PLL.PLLM = 16;
            osc_init.PLL.PLLN = 168;
            osc_init.PLL.PLLP = 2;
            osc_init.PLL.PLLQ = 2;
            osc_init.PLL.PLLR = 2;
            FLatency = FLASH_ACR_LATENCY_2WS;
            break;
        case SYSCLOCK_FREQ_120MHZ:
            osc_init.PLL.PLLM = 16;
            osc_init.PLL.PLLN = 240;
            osc_init.PLL.PLLP = 2;
            osc_init.PLL.PLLQ = 2;
            osc_init.PLL.PLLR = 2;
            FLatency = FLASH_ACR_LATENCY_3WS;
            break;
        default:
            return;
    }

    if (HAL_RCC_OscConfig(&osc_init) != HAL_OK) {
        Error_handler();
    }
    if (HAL_RCC_ClockConfig(&clk_init, FLatency) != HAL_OK) {
        Error_handler();
    }
    if (HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000) != HAL_OK) {
        Error_handler();
    }
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}
