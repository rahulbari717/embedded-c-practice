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
 * This is a Handle structure fro a GPIO pin
 * */

typedef struct
{
	GPIO_RegDef_t *pGPIOx; 		// coment somethisng
}GPIO_Handle_t;



#endif /* INC_STM32F446XX_GPIO_DRIVER_H_ */
