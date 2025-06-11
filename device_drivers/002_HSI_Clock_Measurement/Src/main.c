/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Rahul B.
 * @date           : June 7, 2024 (Example date, adjust as needed)
 * @version        : V1.0 (Initial release)

 ******************************************************************************
 */

#include <stdint.h>

#define RCC_BASE_ADDR                   (0x40023800UL)
#define RCC_CFGR_REG_OFFSET             (0x08UL) // APB2 peripheral clock enable register
#define RCC_CFGR_REG_ADDR               (RCC_BASE_ADDR + RCC_CFGR_REG_OFFSET)

#define RCC_AHB1ENR_REG_OFFSET 			(0x30UL) // AHB1 peripheral clock enable register
#define RCC_AHB1ENR_REG_ADDR 			(RCC_BASE_ADDR + RCC_AHB1ENR_REG_OFFSET)

#define GPIOA_BASE_ADDR 				(0x40020000UL)
#define GPIOA_MODER_REG_OFFSET 			(0x00UL) // GPIO port mode register
#define GPIOA_MODER_REG_ADDR 			(GPIOA_BASE_ADDR + GPIOA_MODER_REG_OFFSET)

#define GPIOA_AFRH_REG_OFFSET 			(0x24UL) // GPIO alternate function high register
#define GPIOA_AFRH_REG_ADDR 			(GPIOA_BASE_ADDR + GPIOA_AFRH_REG_OFFSET)

int main(void)
{
	uint32_t *pRccCfgrReg = (uint32_t *) RCC_CFGR_REG_ADDR;
	uint32_t *pRccAhb1EnrReg = (uint32_t *) RCC_AHB1ENR_REG_ADDR;
	uint32_t *pGpioaModerReg = (uint32_t *) GPIOA_MODER_REG_ADDR;
	uint32_t *pGpioaAfrhReg = (uint32_t *) GPIOA_AFRH_REG_ADDR;

	    // 1. Configure the RCC_CFGR register MCO1 bit fields to select HSI as clock source
	    *pRccCfgrReg &= ~(0x3 << 21); // clear 21 and 22 bit positions (MCO1 = 00 for HSI)

	    *pRccCfgrReg |= (0x1 <<25);
	    *pRccCfgrReg |= (0x1 <<26);

	    // 2. Configure PA8 to AF0 mode to behave as MCO1 signal

	    // a) Enable the peripheral clock for GPIOA peripheral
	    *pRccAhb1EnrReg |= (1 << 0); // Set bit 0 to enable GPIOA clock

	    // b) Configure the mode of GPIOA pin 8 as alternate function mode
	    *pGpioaModerReg &= ~(0x3 << 16); // Clear bits 16 and 17 for PA8
	    *pGpioaModerReg |= (0x2 << 16);  // Set bits to 10 for alternate function mode

	    // c) Configure the alternate function register to set the mode 0 for PA8
	    *pGpioaAfrhReg &= ~(0xF << 0);   // Clear bits 0-3 for PA8 (AFRH[0:3])
	    // AF0 = 0000, so no need to set any bits (already cleared)

	    // Optional: Configure MCO1 prescaler (divide by 1)
	    // *pRccCfgrReg &= ~(0x7 << 24);    // Clear MCO1 prescaler bits (24-26)
	    // Prescaler = 000 means no division



    /* Loop forever */
	for(;;);
}
