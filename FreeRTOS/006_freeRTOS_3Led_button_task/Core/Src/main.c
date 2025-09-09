/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
static void led1_task1_handler(void *Parameters);
static void led2_task2_handler(void *Parameters);
static void led3_task3_handler(void *Parameters);
static void button_task4_handler(void *Parameters);

TaskHandle_t led1_task1_handle;
TaskHandle_t led2_task2_handle;
TaskHandle_t led3_task3_handle;
TaskHandle_t button_task4_handle;

TaskHandle_t volatile next_task_handle= NULL;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	BaseType_t status;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

	printf("\r\n=== SYSTEM STARTING ===\r\n");

	status = xTaskCreate(led1_task1_handler, "Task-1", 200, NULL, 1, &led1_task1_handle);
	configASSERT(status == pdPASS);
	printf("LED1 Task created, handle: %p\r\n", led1_task1_handle);

	next_task_handle = led1_task1_handle;
	printf("next_task_handle initialized to: %p\r\n", next_task_handle);

	status = xTaskCreate(led2_task2_handler, "Task-2", 200, NULL, 2, &led2_task2_handle);
	configASSERT(status == pdPASS);
	printf("LED2 Task created, handle: %p\r\n", led2_task2_handle);

	status = xTaskCreate(led3_task3_handler, "Task-3", 200, NULL, 3, &led3_task3_handle);
	configASSERT(status == pdPASS);
	printf("LED3 Task created, handle: %p\r\n", led3_task3_handle);

	status = xTaskCreate(button_task4_handler, "Button Task-4", 200, NULL, 4, &button_task4_handle);
	configASSERT(status == pdPASS);
	printf("Button Task created, handle: %p\r\n", button_task4_handle);

	printf("All tasks created successfully\r\n");
	printf("Starting FreeRTOS scheduler...\r\n");

	// start FreeRTOS scheduler
	vTaskStartScheduler();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD1_Pin|LD2_Pin|LD3_Pin|LD4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;  /* Changed to INPUT for polling */
  GPIO_InitStruct.Pull = GPIO_PULLUP;      /* Added pull-up resistor */
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : USART_TX_Pin USART_RX_Pin */
  GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD2_Pin LD3_Pin LD4_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD2_Pin|LD3_Pin|LD4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
static void led1_task1_handler(void *Parameters)
{
    BaseType_t status;
    printf("=== LED1 Task Started ===\r\n");

    while(1)
    {
        printf("LED1: Toggling led1 (PA5)\r\n");
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

        printf("LED1: Waiting for notification (timeout: 2000ms)...\r\n");
        status = xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(2000));

        if(status == pdTRUE)
        {
            printf("LED1: *** NOTIFICATION RECEIVED! ***\r\n");
            vTaskSuspendAll();
            next_task_handle = led2_task2_handle;
            printf("LED1: next_task_handle changed to LED2: %p\r\n", next_task_handle);
            xTaskResumeAll();
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            printf("LED1: LED turned OFF, deleting task1\r\n");
            vTaskDelete(NULL);
        }
        else
        {
            printf("LED1: Timeout - no notification received\r\n");
        }
    }
}

static void led2_task2_handler(void *Parameters)
{
    BaseType_t status;
    printf("=== LED2 Task Started ===\r\n");

    while(1)
    {
        printf("LED2: Toggling led2 (PA6)\r\n");
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);

        printf("LED2: Waiting for notification (timeout: 1500ms)...\r\n");
        status = xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(1500));

        if(status == pdTRUE)
        {
            printf("LED2: *** NOTIFICATION RECEIVED! ***\r\n");
            vTaskSuspendAll();
            next_task_handle = led3_task3_handle;
            printf("LED2: next_task_handle changed to LED3: %p\r\n", next_task_handle);
            xTaskResumeAll();
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
            printf("LED2: LED turned OFF, deleting task2\r\n");
            vTaskDelete(NULL);
        }
        else
        {
            printf("LED2: Timeout - no notification received\r\n");
        }
    }
}

static void led3_task3_handler(void *Parameters)
{
    BaseType_t status;
    printf("=== LED3 Task Started ===\r\n");

    while(1)
    {
        printf("LED3: Toggling led3 (PA4)\r\n");
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);

        printf("LED3: Waiting for notification (timeout: 1000ms)...\r\n");
        status = xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(1000));

        if(status == pdTRUE)
        {
            printf("LED3: *** NOTIFICATION RECEIVED! ***\r\n");
            vTaskSuspendAll();
            next_task_handle = NULL;
            printf("LED3: next_task_handle set to NULL\r\n");
            xTaskResumeAll();
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
            printf("LED3: LED turned OFF\r\n");
            printf("LED3: Deleting button task (%p)\r\n", button_task4_handle);
            vTaskDelete(button_task4_handle);
            printf("LED3: Deleting LED3 task (self)\r\n");
            vTaskDelete(NULL);
        }
        else
        {
            printf("LED3: Timeout - no notification received\r\n");
        }
    }
}

static void button_task4_handler(void *Parameters)
{
    uint8_t btn_read = 0;
    uint8_t prev_read = 0;
    static uint32_t button_press_count = 0;
    static uint32_t debug_counter = 0;

    printf("=== BUTTON Task Started ===\r\n");
    printf("BUTTON: Current next_task_handle: %p\r\n", next_task_handle);

    // Print pin definitions for debugging
    printf("BUTTON: B1_Pin = 0x%04X, B1_GPIO_Port = %p\r\n", (uint16_t)B1_Pin, B1_GPIO_Port);

    // Initialize previous state - USING CORRECT PIN!
    prev_read = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);
    printf("BUTTON: Initial button state (B1_Pin): %d\r\n", prev_read);

    // Also check PA0 for comparison
    uint8_t pa0_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
    printf("BUTTON: Initial PA0 state: %d\r\n", pa0_state);

    while(1)
    {
        // Read the CORRECT button pin - B1_Pin, not GPIO_PIN_0!
        btn_read = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);

        debug_counter++;

        // Print button state every 100 cycles for debugging
        if(debug_counter % 100 == 0)
        {
            printf("BUTTON: Debug #%lu - B1_Pin: %d, PA0: %d, next_task: %p\r\n",
                   debug_counter/100, btn_read, HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0), next_task_handle);
        }

        // Print any button state changes immediately
        if(btn_read != prev_read)
        {
            printf("BUTTON: *** STATE CHANGE #%lu *** %d -> %d\r\n", ++button_press_count, prev_read, btn_read);
        }

        // For STM32 Nucleo, button is typically:
        // - HIGH when not pressed (with pull-up)
        // - LOW when pressed
        // So we detect HIGH to LOW (falling edge) for button press

        if(!btn_read && prev_read)  // Falling edge: button pressed
        {
            printf("BUTTON: *** BUTTON PRESSED *** (Falling Edge Detection)\r\n");

            // Debounce delay
            vTaskDelay(pdMS_TO_TICKS(50));

            // Re-read to confirm
            btn_read = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);
            printf("BUTTON: After debounce, button state: %d\r\n", btn_read);

            if(!btn_read) // Still pressed after debounce
            {
                printf("BUTTON: Button press confirmed, current next_task_handle: %p\r\n", next_task_handle);

                if(next_task_handle != NULL)
                {
                    printf("BUTTON: Sending notification to task %p\r\n", next_task_handle);
                    BaseType_t notify_result = xTaskNotify(next_task_handle, 0, eNoAction);

                    if(notify_result == pdPASS)
                    {
                        printf("BUTTON: *** NOTIFICATION SENT SUCCESSFULLY ***\r\n");
                    }
                    else
                    {
                        printf("BUTTON: *** NOTIFICATION FAILED ***\r\n");
                    }
                }
                else
                {
                    printf("BUTTON: next_task_handle is NULL - no task to notify\r\n");
                }

                // Wait for button release
                printf("BUTTON: Waiting for button release...\r\n");
                while(!HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))
                {
                    vTaskDelay(pdMS_TO_TICKS(10));
                }
                printf("BUTTON: Button released\r\n");
            }
        }

        prev_read = btn_read;
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
