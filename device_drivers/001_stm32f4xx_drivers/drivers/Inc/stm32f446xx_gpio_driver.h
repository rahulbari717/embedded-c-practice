/*
 * stm32f446xx_gpio_driver.h
 *
 *  Created on: Jun 9, 2025
 *      Author: Rahul B.
 */

#ifndef INC_STM32F446XX_GPIO_DRIVER_H_
#define INC_STM32F446XX_GPIO_DRIVER_H_

#include "stm32f446xx.h"

/*
 * Configuration structure for a GPIO pin
 */
typedef struct
{
    uint8_t GPIO_PinNumber;          /*!< Possible values from @GPIO_PIN_NUMBERS */
    uint8_t GPIO_PinMode;            /*!< Possible values from @GPIO_PIN_MODES */
    uint8_t GPIO_PinSpeed;           /*!< Possible values from @GPIO_PIN_SPEED */
    uint8_t GPIO_PinPuPdControl;     /*!< Possible values from @GPIO_PIN_PUPD */
    uint8_t GPIO_PinOPType;          /*!< Possible values from @GPIO_PIN_OUTPUT_TYPES */
    uint8_t GPIO_PinAltFunMode;      /*!< Possible values from @GPIO_PIN_ALT_FUN_MODE */
} GPIO_PinConfig_t;

/*
 * Handle structure for a GPIO pin
 */
typedef struct
{
    GPIO_RegDef_t *pGPIOx;           /*!< This holds the base address of the GPIO port to which the pin belongs */
    GPIO_PinConfig_t GPIO_PinConfig; /*!< This holds GPIO pin configuration settings */
} GPIO_Handle_t;

/*
 * @GPIO_PIN_NUMBERS
 * GPIO pin numbers
 */
#define GPIO_PIN_NO_0       0
#define GPIO_PIN_NO_1       1
#define GPIO_PIN_NO_2       2
#define GPIO_PIN_NO_3       3
#define GPIO_PIN_NO_4       4
#define GPIO_PIN_NO_5       5
#define GPIO_PIN_NO_6       6
#define GPIO_PIN_NO_7       7
#define GPIO_PIN_NO_8       8
#define GPIO_PIN_NO_9       9
#define GPIO_PIN_NO_10      10
#define GPIO_PIN_NO_11      11
#define GPIO_PIN_NO_12      12
#define GPIO_PIN_NO_13      13
#define GPIO_PIN_NO_14      14
#define GPIO_PIN_NO_15      15

/*
 * @GPIO_PIN_MODES
 * GPIO pin possible modes
 */
#define GPIO_MODE_IN        0       /*!< GPIO Input mode */
#define GPIO_MODE_OUT       1       /*!< GPIO Output mode */
#define GPIO_MODE_ALTFN     2       /*!< GPIO Alternate function mode */
#define GPIO_MODE_ANALOG    3       /*!< GPIO Analog mode */

#define GPIO_MODE_IT_FT     4       /*!< GPIO Interrupt falling edge trigger */
#define GPIO_MODE_IT_RT     5       /*!< GPIO Interrupt rising edge trigger */
#define GPIO_MODE_IT_RFT    6       /*!< GPIO Interrupt rising falling edge trigger */

/*
 * @GPIO_PIN_OUTPUT_TYPES
 * GPIO pin possible output types
 */
#define GPIO_OP_TYPE_PP     0       /*!< GPIO Push Pull output type */
#define GPIO_OP_TYPE_OD     1       /*!< GPIO Open Drain output type */

/*
 * @GPIO_PIN_SPEED
 * GPIO pin possible output speeds
 */
#define GPIO_SPEED_LOW      0       /*!< GPIO Low speed */
#define GPIO_SPEED_MEDIUM   1       /*!< GPIO Medium speed */
#define GPIO_SPEED_FAST     2       /*!< GPIO Fast speed */
#define GPIO_SPEED_HIGH     3       /*!< GPIO High speed */

/*
 * @GPIO_PIN_PUPD
 * GPIO pin pull up and pull down configuration macros
 */
#define GPIO_NO_PUPD        0       /*!< GPIO No pull-up, pull-down */
#define GPIO_PIN_PU         1       /*!< GPIO Pull-up */
#define GPIO_PIN_PD         2       /*!< GPIO Pull-down */

/*
 * @GPIO_PIN_ALT_FUN_MODE
 * GPIO pin alternate function modes
 */
#define GPIO_AF0            0       /*!< GPIO Alternate function 0 */
#define GPIO_AF1            1       /*!< GPIO Alternate function 1 */
#define GPIO_AF2            2       /*!< GPIO Alternate function 2 */
#define GPIO_AF3            3       /*!< GPIO Alternate function 3 */
#define GPIO_AF4            4       /*!< GPIO Alternate function 4 */
#define GPIO_AF5            5       /*!< GPIO Alternate function 5 */
#define GPIO_AF6            6       /*!< GPIO Alternate function 6 */
#define GPIO_AF7            7       /*!< GPIO Alternate function 7 */
#define GPIO_AF8            8       /*!< GPIO Alternate function 8 */
#define GPIO_AF9            9       /*!< GPIO Alternate function 9 */
#define GPIO_AF10           10      /*!< GPIO Alternate function 10 */
#define GPIO_AF11           11      /*!< GPIO Alternate function 11 */
#define GPIO_AF12           12      /*!< GPIO Alternate function 12 */
#define GPIO_AF13           13      /*!< GPIO Alternate function 13 */
#define GPIO_AF14           14      /*!< GPIO Alternate function 14 */
#define GPIO_AF15           15      /*!< GPIO Alternate function 15 */


/*******************************************************************************
 *          APIs supported by this driver
 *          For more information about the APIs check the function definitions
 *******************************************************************************/

/*
 * Peripheral Clock setup
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/*
 * Init and De-init
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/*
 * Data read and write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/*
 * IRQ Configuration and ISR handling
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);

#endif /* INC_STM32F446XX_GPIO_DRIVER_H_ */
