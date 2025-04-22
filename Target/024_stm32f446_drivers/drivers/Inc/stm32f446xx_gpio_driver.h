/*
 * stm32f446xx_gpio_driver.h
 *
 *  Created on: Mar 31, 2025
 *      Author: Rahul B.
 */

#ifndef INC_STM32F446XX_GPIO_DRIVER_H_
#define INC_STM32F446XX_GPIO_DRIVER_H_

#include "stm32f446xx.h"

/*
 * GPIO Pin Configuration Structure
 * This structure holds the configuration settings for a GPIO pin.
 */
typedef struct
{
    uint8_t GPIO_PinNumber;      /*!< Specifies the GPIO pin number (0 to 15). */
    uint8_t GPIO_PinMode;        /*!< Specifies the mode of the GPIO pin (@GPIO_PIN_MODES). */
    uint8_t GPIO_PinSpeed;       /*!< Specifies the speed of the GPIO pin (@GPIO_PIN_SPEEDS). */
    uint8_t GPIO_PinPuPdControl; /*!< Specifies the pull-up/pull-down configuration. */
    uint8_t GPIO_PinOPType;      /*!< Specifies the output type (Push-Pull/Open-Drain). */
    uint8_t GPIO_PinAltFunMode;  /*!< Specifies the alternate function mode (if applicable). */
} GPIO_PinConfig_t;

/*
 * GPIO Handle Structure
 * This structure is used to handle GPIO operations, linking a GPIO port with its configuration.
 */
typedef struct
{
    GPIO_RegDef_t *pGPIOx;       /*!< Pointer to the GPIO port base address. */
    GPIO_PinConfig_t GPIO_PinConfig; /*!< Configuration settings for the GPIO pin. */
} GPIO_Handle_t;

/*
 *  @GPIO_PIN_NUMBERS
*/
#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_No_15		15

/*
 *  @GPIO_PIN_MODES
 *  GPIO pin possible modes
*/
#define GPIO_MODE_IN      0  /*!< Input mode */
#define GPIO_MODE_OUT     1  /*!< Output mode */
#define GPIO_MODE_ALTFN   2  /*!< Alternate function mode */
#define GPIO_MODE_ANALOG  3  /*!< Analog mode */

/*
 * GPIO Interrupt Modes
 */
#define GPIO_MODE_IT_FT   4  /*!< Falling edge trigger */
#define GPIO_MODE_IT_RT   5  /*!< Rising edge trigger */
#define GPIO_MODE_IT_RFT  6  /*!< Rising and falling edge trigger */

/*
 * GPIO Output Type
 */
#define GPIO_OP_TYPE_PP   0  /*!< Push-pull output */
#define GPIO_OP_TYPE_OD   1  /*!< Open-drain output */

/*
 * @GPIO_PIN_SPEEDS
 * GPIO pin possible output speed
*/
#define GPIO_SPEED_LOW    0  /*!< Low speed */
#define GPIO_SPEED_MEDIUM 1  /*!< Medium speed */
#define GPIO_SPEED_FAST   2  /*!< Fast speed */
#define GPIO_SPEED_HIGH   3  /*!< High speed */

/*
 * GPIO pin pull up and pull down configuration macros
*/
#define GPIO_NO_PUPD      0  /*!< No pull-up, no pull-down */
#define GPIO_PIN_PU       1  /*!< Pull-up enabled */
#define GPIO_PIN_PD       2  /*!< Pull-down enabled */

/*********************************************************************************
 * 						APIs supported by this driver
 * 		For more information about the APIs check the function definitions
 *********************************************************************************/
/* Initialization and De-initialization */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/* Peripheral Clock Setup */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/* Data Read and Write */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/* IRQ Configuration and ISR Handling */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);

#endif /* INC_STM32F446XX_GPIO_DRIVER_H_ */
