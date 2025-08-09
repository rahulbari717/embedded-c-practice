/*******************************************************************************
 * @file    stm32f446xx.h
 * @author  Rahul Bari
 * @date    Mar 31, 2025
 * @brief   STM32F446xx MCU Device Peripheral Access Layer Header File
 *
 * This file contains:
 *  - Data structures and the address mapping for all peripherals
 *  - Peripheral registers declarations and bit definitions
 *  - Macros to access peripheral registers hardware
 *  - Clock enable/disable macros
 *  - Memory mapping definitions
 *******************************************************************************/

 #ifndef INC_STM32F446XX_H_
 #define INC_STM32F446XX_H_

 #include <stdint.h>

 /**
  * @brief Define for volatile keyword to use with memory-mapped registers
  */
 #define __vo volatile

 /*******************************************************************************
  * 1. BASE ADDRESSES OF FLASH AND SRAM MEMORIES
  *******************************************************************************/
 #define FLASH_BASEADDR        0x08000000U  /*!< Flash Base Address: 0x0800 0000 - 0x080F FFFF, 1MB */
 #define SRAM1_BASEADDR        0x20000000U  /*!< SRAM1 Base Address: 0x2000 0000 - 0x2001 BFFF, 112KB */
 #define SRAM2_BASEADDR        0x20001C00U  /*!< SRAM2 Base Address: 0x2001 C000 - 0x2001 FFFF, 16KB */
 #define ROM_BASEADDR          0x1FFF0000U  /*!< System Memory (Boot ROM) Base Address */
 #define SRAM_BASEADDR         SRAM1_BASEADDR  /*!< Alias for SRAM1 base address */

 /*******************************************************************************
  * 2. BUS PERIPHERAL BASE ADDRESSES
  *******************************************************************************/
 #define PERIPH_BASE           0x40000000U  /*!< Base address for all peripherals */
 #define APB1PERIPH_BASE       PERIPH_BASE  /*!< APB1 Bus Base Address: 0x4000 0000 */
 #define APB2PERIPH_BASE       0x40010000U  /*!< APB2 Bus Base Address: 0x4001 0000 */
 #define AHB1PERIPH_BASE       0x40020000U  /*!< AHB1 Bus Base Address: 0x4002 0000 */
 #define AHB2PERIPH_BASE       0x50000000U  /*!< AHB2 Bus Base Address: 0x5000 0000 */

 /*******************************************************************************
  * 3. PERIPHERAL BASE ADDRESSES
  *******************************************************************************/

 /**
  * @defgroup APB1_Peripherals APB1 Peripheral Base Addresses
  * @{
  */
 #define I2C1_BASEADDR         (APB1PERIPH_BASE + 0x5400)  /*!< I2C1 Base Address */
 #define I2C2_BASEADDR         (APB1PERIPH_BASE + 0x5800)  /*!< I2C2 Base Address */
 #define I2C3_BASEADDR         (APB1PERIPH_BASE + 0x5C00)  /*!< I2C3 Base Address */
 
 /*******************************************************************************
  * 4. PERIPHERAL REGISTER DEFINITION STRUCTURES
  *******************************************************************************/

 /**
  * @brief I2C (Inter-Integrated Circuit) Register Definition Structure
  */
 typedef struct {
     __vo uint32_t CR1;         /*!< I2C Control register 1,                 Address offset: 0x00 */
     __vo uint32_t CR2;         /*!< I2C Control register 2,                 Address offset: 0x04 */
     __vo uint32_t OAR1;        /*!< I2C Own address register 1,             Address offset: 0x08 */
     __vo uint32_t OAR2;        /*!< I2C Own address register 2,             Address offset: 0x0C */
     __vo uint32_t DR;          /*!< I2C Data register,                      Address offset: 0x10 */
     __vo uint32_t SR1;         /*!< I2C Status register 1,                  Address offset: 0x14 */
     __vo uint32_t SR2;         /*!< I2C Status register 2,                  Address offset: 0x18 */
     __vo uint32_t CCR;         /*!< I2C Clock control register,             Address offset: 0x1C */
     __vo uint32_t TRISE;       /*!< I2C TRISE register,                     Address offset: 0x20 */
     __vo uint32_t FLTR;        /*!< I2C FLTR register,                      Address offset: 0x24 */
 } I2C_RegDef_t;


 /*******************************************************************************
  * 5. PERIPHERAL DEFINITIONS (Peripheral Base Address Typecasting)
  *******************************************************************************/


 /**
  * @defgroup I2C_Clock_Enable Clock Enable Macros for I2C Peripherals
  * @{
  */
 #define I2C1_PCLK_EN()   (RCC->APB1ENR |= (1 << 21)) /*!< Enable clock for I2C1 */
 #define I2C2_PCLK_EN()   (RCC->APB1ENR |= (1 << 22)) /*!< Enable clock for I2C2 */
 #define I2C3_PCLK_EN()   (RCC->APB1ENR |= (1 << 23)) /*!< Enable clock for I2C3 */
 /** @} */


 /**
  * @defgroup Other_Clock_Enable Clock Enable Macros for Other Peripherals
  * @{
  */
 #define SYSCFG_PCLK_EN() (RCC->APB2ENR |= (1 << 14)) /*!< Enable clock for SYSCFG */

 #define TIM1_PCLK_EN()   (RCC->APB2ENR |= (1 << 0))  /*!< Enable clock for TIM1 */
 #define TIM2_PCLK_EN()   (RCC->APB1ENR |= (1 << 0))  /*!< Enable clock for TIM2 */
 #define TIM3_PCLK_EN()   (RCC->APB1ENR |= (1 << 1))  /*!< Enable clock for TIM3 */
 #define TIM4_PCLK_EN()   (RCC->APB1ENR |= (1 << 2))  /*!< Enable clock for TIM4 */
 #define TIM5_PCLK_EN()   (RCC->APB1ENR |= (1 << 3))  /*!< Enable clock for TIM5 */
 #define TIM6_PCLK_EN()   (RCC->APB1ENR |= (1 << 4))  /*!< Enable clock for TIM6 */
 #define TIM7_PCLK_EN()   (RCC->APB1ENR |= (1 << 5))  /*!< Enable clock for TIM7 */
 #define TIM8_PCLK_EN()   (RCC->APB2ENR |= (1 << 1))  /*!< Enable clock for TIM8 */

 /** @} */

 /*******************************************************************************
  * 7. CLOCK DISABLE MACROS
  *******************************************************************************/

 /**
  * @defgroup I2C_Clock_Disable Clock Disable Macros for I2C Peripherals
  * @{
  */
 #define I2C1_PCLK_DI()   (RCC->APB1ENR &= ~(1 << 21)) /*!< Disable clock for I2C1 */
 #define I2C2_PCLK_DI()   (RCC->APB1ENR &= ~(1 << 22)) /*!< Disable clock for I2C2 */
 #define I2C3_PCLK_DI()   (RCC->APB1ENR &= ~(1 << 23)) /*!< Disable clock for I2C3 */
 /** @} */

 /**
  * @defgroup Other_Clock_Disable Clock Disable Macros for Other Peripherals
  * @{
  */
 #define SYSCFG_PCLK_DI() (RCC->APB2ENR &= ~(1 << 14)) /*!< Disable clock for SYSCFG */

 #define TIM1_PCLK_DI()   (RCC->APB2ENR &= ~(1 << 0))  /*!< Disable clock for Tim*/

/*
 * IRQ Numbers of STM32F446RE MCU
 * NOTE : IRQ numbers are different for different MCU
*/
#define IRQ_NO_EXTI0             6
#define IRQ_NO_EXTI1             7
#define IRQ_NO_EXTI2             8
#define IRQ_NO_EXTI3             9
#define IRQ_NO_EXTI4             10
#define IRQ_NO_EXTI5_9           23
#define IRQ_NO_EXTI10_15         40

/*
 * macros for all the possible priority levels
*/
#define NVIC_IRQ_PRI0        0
#define NVIC_IRQ_PRI15       15

/*
 * some genric macros
*/

#define ENABLE                  1
#define DISABLE                 0
#define SET                     ENABLE
#define RESET                   DISABLE
#define GPIO_PIN_SET            1
#define GPIO_PIN_RESET          0


/*******************************************************************************
  * I2C    
  *******************************************************************************/
/*
 * Bit positions for I2Cx CR1 Register
*/
#define I2C_CR1_PE              0   /* Peripheral Enable */
#define I2C_CR1_SMBUS           1   /* SMBus Mode */
#define I2C_CR1_SMBTYPE         3   /* SMBus Type */
#define I2C_CR1_ENARP           4   /* ARP Enable */
#define I2C_CR1_ENPEC           5   /* PEC Enable */
#define I2C_CR1_ENGC            6   /* General Call Enable */
#define I2C_CR1_NOSTRETCH       7   /* Clock Stretching Disable */
#define I2C_CR1_START           8   /* Start Generation */
#define I2C_CR1_STOP            9   /* Stop Generation */
#define I2C_CR1_ACK            10   /* Acknowledge Enable */
#define I2C_CR1_POS            11   /* Acknowledge/PEC Position */
#define I2C_CR1_PEC            12   /* Packet Error Checking */
#define I2C_CR1_ALERT          13   /* SMBus Alert */
#define I2C_CR1_SWRST          15   /* Software Reset */

/*
 * Bit positions for I2Cx CR2 Register
*/
#define I2C_CR2_FREQ           0    /* Peripheral Clock Frequency */
#define I2C_CR2_ITERREN        8    /* Error Interrupt Enable */
#define I2C_CR2_ITEVTEN        9    /* Event Interrupt Enable */
#define I2C_CR2_ITBUFEN       10    /* Buffer Interrupt Enable */
#define I2C_CR2_DMAEN         11    /* DMA Requests Enable */
#define I2C_CR2_LAST          12    /* DMA Last Transfer */

/*
 * Bit positions for I2Cx SR1 Register
*/
#define I2C_SR1_SB             0    /* Start Bit Generated */
#define I2C_SR1_ADDR           1    /* Address Sent/Matched */
#define I2C_SR1_BTF            2    /* Byte Transfer Finished */
#define I2C_SR1_ADD10          3    /* 10-bit Header Sent */
#define I2C_SR1_STOPF          4    /* Stop Detection */
#define I2C_SR1_RXNE           6    /* Data Register Not Empty */
#define I2C_SR1_TXE            7    /* Data Register Empty */
#define I2C_SR1_BERR           8    /* Bus Error */
#define I2C_SR1_ARLO          9     /* Arbitration Lost */
#define I2C_SR1_AF            10    /* Acknowledge Failure */
#define I2C_SR1_OVR           11    /* Overrun/Underrun */
#define I2C_SR1_PECERR        12    /* PEC Error in Reception */
#define I2C_SR1_TIMEOUT       14    /* Timeout or Tlow Error */
#define I2C_SR1_SMBALERT     15    /* SMBus Alert */

/*
 * Bit positions for I2Cx SR2 Register
*/
#define I2C_SR2_MSL            0    /* Master/Slave */
#define I2C_SR2_BUSY           1    /* Bus Busy */
#define I2C_SR2_TRA            2    /* Transmitter/Receiver */
#define I2C_SR2_GENCALL        4    /* General Call Address */
#define I2C_SR2_SMBDEFAULT     5    /* SMBus Device Default Address */
#define I2C_SR2_SMBHOST        6    /* SMBus Host Header */
#define I2C_SR2_DUALF          7    /* Dual Flag */
#define I2C_SR2_PEC            8    /* Packet Error Checking Register */

/*
 * Bit positions for I2C_CCR  Register
*/

#define I2C_CCR_CCR            0    /* Clock Control Register */
#define I2C_CCR_DUTY          14    /* Fast Mode Duty Cycle */
#define I2C_CCR_FS            15    /* I2C Master Mode Selection */

#include "stm32f446xx_i2c_driver.h"

#endif
