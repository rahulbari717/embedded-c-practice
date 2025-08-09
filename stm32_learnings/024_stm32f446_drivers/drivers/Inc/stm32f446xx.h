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
  * @defgroup AHB1_Peripherals AHB1 Peripheral Base Addresses
  * @{
  */
 #define GPIOA_BASEADDR        (AHB1PERIPH_BASE + 0x0000)  /*!< GPIO Port A Base Address */
 #define GPIOB_BASEADDR        (AHB1PERIPH_BASE + 0x0400)  /*!< GPIO Port B Base Address */
 #define GPIOC_BASEADDR        (AHB1PERIPH_BASE + 0x0800)  /*!< GPIO Port C Base Address */
 #define GPIOD_BASEADDR        (AHB1PERIPH_BASE + 0x0C00)  /*!< GPIO Port D Base Address */
 #define GPIOE_BASEADDR        (AHB1PERIPH_BASE + 0x1000)  /*!< GPIO Port E Base Address */
 /* Note: GPIOF and GPIOG not available on STM32F446RE Nucleo */
 /* #define GPIOF_BASEADDR     (AHB1PERIPH_BASE + 0x1400) */
 /* #define GPIOG_BASEADDR     (AHB1PERIPH_BASE + 0x1800) */
 #define GPIOH_BASEADDR        (AHB1PERIPH_BASE + 0x1C00)  /*!< GPIO Port H Base Address */

 #define RCC_BASEADDR          (AHB1PERIPH_BASE + 0x3800)  /*!< Reset and Clock Control Base Address */
 #define DMA1_BASEADDR         (AHB1PERIPH_BASE + 0x6000)  /*!< DMA1 Controller Base Address */
 #define DMA2_BASEADDR         (AHB1PERIPH_BASE + 0x6400)  /*!< DMA2 Controller Base Address */
 /** @} */

 /**
  * @defgroup APB1_Peripherals APB1 Peripheral Base Addresses
  * @{
  */
 #define I2C1_BASEADDR         (APB1PERIPH_BASE + 0x5400)  /*!< I2C1 Base Address */
 #define I2C2_BASEADDR         (APB1PERIPH_BASE + 0x5800)  /*!< I2C2 Base Address */
 #define I2C3_BASEADDR         (APB1PERIPH_BASE + 0x5C00)  /*!< I2C3 Base Address */
 
 #define SPI2_BASEADDR         (APB1PERIPH_BASE + 0x3800)  /*!< SPI2 Base Address */
 #define SPI3_BASEADDR         (APB1PERIPH_BASE + 0x3C00)  /*!< SPI3 Base Address */
 
 #define USART2_BASEADDR       (APB1PERIPH_BASE + 0x4400)  /*!< USART2 Base Address */
 #define USART3_BASEADDR       (APB1PERIPH_BASE + 0x4800)  /*!< USART3 Base Address */
 
 #define CAN1_BASEADDR         (APB1PERIPH_BASE + 0x6400)  /*!< CAN1 Base Address */
 #define CAN2_BASEADDR         (APB1PERIPH_BASE + 0x6800)  /*!< CAN2 Base Address */

 #define DAC_BASEADDR          (APB1PERIPH_BASE + 0x7400)  /*!< Digital to Analog Converter Base Address */
 /** @} */

 /**
  * @defgroup APB2_Peripherals APB2 Peripheral Base Addresses
  * @{
  */
 #define EXTI_BASEADDR         (APB2PERIPH_BASE + 0x3C00)  /*!< External Interrupt/Event Controller Base Address */
 #define SYSCFG_BASEADDR       (APB2PERIPH_BASE + 0x3800)  /*!< System Configuration Controller Base Address */
 #define SPI1_BASEADDR         (APB2PERIPH_BASE + 0x3000)  /*!< SPI1 Base Address */
 #define USART1_BASEADDR       (APB2PERIPH_BASE + 0x1000)  /*!< USART1 Base Address */
 /** @} */

 /*******************************************************************************
  * 4. PERIPHERAL REGISTER DEFINITION STRUCTURES
  *******************************************************************************/

 /**
  * @brief GPIO (General Purpose I/O) Register Definition Structure
  */
 typedef struct {
     __vo uint32_t MODER;      /*!< GPIO port mode register,                 Address offset: 0x00 */
     __vo uint32_t OTYPER;     /*!< GPIO port output type register,          Address offset: 0x04 */
     __vo uint32_t OSPEEDR;    /*!< GPIO port output speed register,         Address offset: 0x08 */
     __vo uint32_t PUPDR;      /*!< GPIO port pull-up/pull-down register,    Address offset: 0x0C */
     __vo uint32_t IDR;        /*!< GPIO port input data register,           Address offset: 0x10 */
     __vo uint32_t ODR;        /*!< GPIO port output data register,          Address offset: 0x14 */
     __vo uint32_t BSRR;       /*!< GPIO port bit set/reset register,        Address offset: 0x18 */
     __vo uint32_t LCKR;       /*!< GPIO port configuration lock register,   Address offset: 0x1C */
     __vo uint32_t AFR[2];     /*!< GPIO alternate function registers,       Address offset: 0x20-0x24 */
 } GPIO_RegDef_t;

 /**
  * @brief RCC (Reset and Clock Control) Register Definition Structure
  */
 typedef struct {
     __vo uint32_t CR;          /*!< RCC clock control register,                  Address offset: 0x00 */
     __vo uint32_t PLLCFGR;     /*!< RCC PLL configuration register,              Address offset: 0x04 */
     __vo uint32_t CFGR;        /*!< RCC clock configuration register,            Address offset: 0x08 */
     __vo uint32_t CIR;         /*!< RCC clock interrupt register,                Address offset: 0x0C */
     __vo uint32_t AHB1RSTR;    /*!< RCC AHB1 peripheral reset register,          Address offset: 0x10 */
     __vo uint32_t AHB2RSTR;    /*!< RCC AHB2 peripheral reset register,          Address offset: 0x14 */
     __vo uint32_t AHB3RSTR;    /*!< RCC AHB3 peripheral reset register,          Address offset: 0x18 */
     uint32_t RESERVED0;        /*!< Reserved, 0x1C                                                    */
     __vo uint32_t APB1RSTR;    /*!< RCC APB1 peripheral reset register,          Address offset: 0x20 */
     __vo uint32_t APB2RSTR;    /*!< RCC APB2 peripheral reset register,          Address offset: 0x24 */
     uint32_t RESERVED1;        /*!< Reserved, 0x28                                                    */
     __vo uint32_t AHB1ENR;     /*!< RCC AHB1 peripheral clock enable register,   Address offset: 0x30 */
     __vo uint32_t AHB2ENR;     /*!< RCC AHB2 peripheral clock enable register,   Address offset: 0x34 */
     __vo uint32_t AHB3ENR;     /*!< RCC AHB3 peripheral clock enable register,   Address offset: 0x38 */
     uint32_t RESERVED2;        /*!< Reserved, 0x3C                                                    */
     __vo uint32_t APB1ENR;     /*!< RCC APB1 peripheral clock enable register,   Address offset: 0x40 */
     __vo uint32_t APB2ENR;     /*!< RCC APB2 peripheral clock enable register,   Address offset: 0x44 */
     uint32_t RESERVED3;        /*!< Reserved, 0x48                                                    */
 } RCC_RegDef_t;

 /**
  * @brief SPI (Serial Peripheral Interface) Register Definition Structure
  */
 typedef struct {
     __vo uint32_t CR1;         /*!< SPI control register 1,                 Address offset: 0x00 */
     __vo uint32_t CR2;         /*!< SPI control register 2,                 Address offset: 0x04 */
     __vo uint32_t SR;          /*!< SPI status register,                    Address offset: 0x08 */
     __vo uint32_t DR;          /*!< SPI data register,                      Address offset: 0x0C */
     __vo uint32_t CRCPR;       /*!< SPI CRC polynomial register,            Address offset: 0x10 */
     __vo uint32_t RXCRCR;      /*!< SPI RX CRC register,                    Address offset: 0x14 */
     __vo uint32_t TXCRCR;      /*!< SPI TX CRC register,                    Address offset: 0x18 */
     __vo uint32_t I2SCFGR;     /*!< SPI_I2S configuration register,         Address offset: 0x1C */
     __vo uint32_t I2SPR;       /*!< SPI_I2S prescaler register,             Address offset: 0x20 */
 } SPI_RegDef_t;

 /**
  * @brief USART (Universal Synchronous/Asynchronous Receiver Transmitter) Register Definition Structure
  */
 typedef struct {
     __vo uint32_t SR;          /*!< USART Status register,                  Address offset: 0x00 */
     __vo uint32_t DR;          /*!< USART Data register,                    Address offset: 0x04 */
     __vo uint32_t BRR;         /*!< USART Baud rate register,               Address offset: 0x08 */
     __vo uint32_t CR1;         /*!< USART Control register 1,               Address offset: 0x0C */
     __vo uint32_t CR2;         /*!< USART Control register 2,               Address offset: 0x10 */
     __vo uint32_t CR3;         /*!< USART Control register 3,               Address offset: 0x14 */
     __vo uint32_t GTPR;        /*!< USART Guard time and prescaler register, Address offset: 0x18 */
 } USART_RegDef_t;

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

 /**
  * @brief Timer Register Definition Structure
  */
 typedef struct {
     __vo uint32_t CR1;         /*!< TIM control register 1,                 Address offset: 0x00 */
     __vo uint32_t CR2;         /*!< TIM control register 2,                 Address offset: 0x04 */
     __vo uint32_t SMCR;        /*!< TIM slave mode control register,        Address offset: 0x08 */
     __vo uint32_t DIER;        /*!< TIM DMA/interrupt enable register,      Address offset: 0x0C */
     __vo uint32_t SR;          /*!< TIM status register,                    Address offset: 0x10 */
     __vo uint32_t EGR;         /*!< TIM event generation register,          Address offset: 0x14 */
     __vo uint32_t CCMR1;       /*!< TIM capture/compare mode register 1,    Address offset: 0x18 */
     __vo uint32_t CCMR2;       /*!< TIM capture/compare mode register 2,    Address offset: 0x1C */
     __vo uint32_t CCER;        /*!< TIM capture/compare enable register,    Address offset: 0x20 */
     __vo uint32_t CNT;         /*!< TIM counter register,                   Address offset: 0x24 */
     __vo uint32_t PSC;         /*!< TIM prescaler,                          Address offset: 0x28 */
     __vo uint32_t ARR;         /*!< TIM auto-reload register,               Address offset: 0x2C */
     __vo uint32_t RCR;         /*!< TIM repetition counter register,        Address offset: 0x30 */
     __vo uint32_t CCR1;        /*!< TIM capture/compare register 1,         Address offset: 0x34 */
     __vo uint32_t CCR2;        /*!< TIM capture/compare register 2,         Address offset: 0x38 */
     __vo uint32_t CCR3;        /*!< TIM capture/compare register 3,         Address offset: 0x3C */
     __vo uint32_t CCR4;        /*!< TIM capture/compare register 4,         Address offset: 0x40 */
     __vo uint32_t BDTR;        /*!< TIM break and dead-time register,       Address offset: 0x44 */
     __vo uint32_t DCR;         /*!< TIM DMA control register,               Address offset: 0x48 */
     __vo uint32_t DMAR;        /*!< TIM DMA address for full transfer,      Address offset: 0x4C */
 } TIM_RegDef_t;

 /*******************************************************************************
  * 5. PERIPHERAL DEFINITIONS (Peripheral Base Address Typecasting)
  *******************************************************************************/
 #define GPIOA   ((GPIO_RegDef_t *)GPIOA_BASEADDR)  /*!< GPIOA peripheral definition */
 #define GPIOB   ((GPIO_RegDef_t *)GPIOB_BASEADDR)  /*!< GPIOB peripheral definition */
 #define GPIOC   ((GPIO_RegDef_t *)GPIOC_BASEADDR)  /*!< GPIOC peripheral definition */
 #define GPIOD   ((GPIO_RegDef_t *)GPIOD_BASEADDR)  /*!< GPIOD peripheral definition */
 #define GPIOE   ((GPIO_RegDef_t *)GPIOE_BASEADDR)  /*!< GPIOE peripheral definition */
 #define GPIOH   ((GPIO_RegDef_t *)GPIOH_BASEADDR)  /*!< GPIOE peripheral definition */

 #define RCC     ((RCC_RegDef_t *)RCC_BASEADDR)     /*!< RCC peripheral definition */
 #define EXTI    ((EXTI_RegDef_t *)EXTI_BASEADDR)   /*!< EXTI peripheral definition */
 #define SYSCFG  ((SYSCFG_RegDef_t *)SYSCFG_BASEADDR) /*!< SYSCFG peripheral definition */

 #define SPI1    ((SPI_RegDef_t *)SPI1_BASEADDR)   /*!< SPI1 peripheral definition */
 #define SPI2    ((SPI_RegDef_t *)SPI2_BASEADDR)   /*!< SPI2 peripheral definition */
 #define SPI3    ((SPI_RegDef_t *)SPI3_BASEADDR)   /*!< SPI3 peripheral definition */

 /*******************************************************************************
  * 6. CLOCK ENABLE MACROS
  *******************************************************************************/

 /**
  * @defgroup GPIO_Clock_Enable Clock Enable Macros for GPIO Peripherals
  * @brief Macros to enable peripheral clock for GPIO ports
  * @{
  */
 #define GPIOA_PCLK_EN()  (RCC->AHB1ENR |= (1 << 0))  /*!< Enable clock for GPIOA */
 #define GPIOB_PCLK_EN()  (RCC->AHB1ENR |= (1 << 1))  /*!< Enable clock for GPIOB */
 #define GPIOC_PCLK_EN()  (RCC->AHB1ENR |= (1 << 2))  /*!< Enable clock for GPIOC */
 #define GPIOD_PCLK_EN()  (RCC->AHB1ENR |= (1 << 3))  /*!< Enable clock for GPIOD */
 #define GPIOE_PCLK_EN()  (RCC->AHB1ENR |= (1 << 4))  /*!< Enable clock for GPIOE */
 /* Note: GPIOF and GPIOG not available on STM32F446RE Nucleo */
 /* #define GPIOF_PCLK_EN()  (RCC->AHB1ENR |= (1 << 5)) */
 /* #define GPIOG_PCLK_EN()  (RCC->AHB1ENR |= (1 << 6)) */
 #define GPIOH_PCLK_EN()  (RCC->AHB1ENR |= (1 << 7))  /*!< Enable clock for GPIOH (PH0 & PH1 for HSE) */
 /** @} */

 /**
  * @defgroup I2C_Clock_Enable Clock Enable Macros for I2C Peripherals
  * @{
  */
 #define I2C1_PCLK_EN()   (RCC->APB1ENR |= (1 << 21)) /*!< Enable clock for I2C1 */
 #define I2C2_PCLK_EN()   (RCC->APB1ENR |= (1 << 22)) /*!< Enable clock for I2C2 */
 #define I2C3_PCLK_EN()   (RCC->APB1ENR |= (1 << 23)) /*!< Enable clock for I2C3 */
 /** @} */

 /**
  * @defgroup SPI_Clock_Enable Clock Enable Macros for SPI Peripherals
  * @{
  */
 #define SPI1_PCLK_EN()   (RCC->APB2ENR |= (1 << 12)) /*!< Enable clock for SPI1 */
 #define SPI2_PCLK_EN()   (RCC->APB1ENR |= (1 << 14)) /*!< Enable clock for SPI2 */
 #define SPI3_PCLK_EN()   (RCC->APB1ENR |= (1 << 15)) /*!< Enable clock for SPI3 */
 // #define SPI4_PCLK_EN()   (RCC->APB2ENR |= (1 << 13)) /*!< Enable clock for SPI4 */
 /** @} */

 /**
  * @defgroup USART_Clock_Enable Clock Enable Macros for USART Peripherals
  * @{
  */
 #define USART1_PCLK_EN() (RCC->APB2ENR |= (1 << 4))  /*!< Enable clock for USART1 */
 #define USART2_PCLK_EN() (RCC->APB1ENR |= (1 << 17)) /*!< Enable clock for USART2 */
 #define USART3_PCLK_EN() (RCC->APB1ENR |= (1 << 18)) /*!< Enable clock for USART3 */
 #define UART4_PCLK_EN()  (RCC->APB1ENR |= (1 << 19)) /*!< Enable clock for UART4 */
 #define UART5_PCLK_EN()  (RCC->APB1ENR |= (1 << 20)) /*!< Enable clock for UART5 */
 #define USART6_PCLK_EN() (RCC->APB2ENR |= (1 << 5))  /*!< Enable clock for USART6 */
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

 #define ADC1_PCLK_EN()   (RCC->APB2ENR |= (1 << 8))  /*!< Enable clock for ADC1 */
 #define ADC2_PCLK_EN()   (RCC->APB2ENR |= (1 << 9))  /*!< Enable clock for ADC2 */
 #define ADC3_PCLK_EN()   (RCC->APB2ENR |= (1 << 10)) /*!< Enable clock for ADC3 */

 #define DAC_PCLK_EN()    (RCC->APB1ENR |= (1 << 29)) /*!< Enable clock for DAC */

 #define DMA1_PCLK_EN()   (RCC->AHB1ENR |= (1 << 21)) /*!< Enable clock for DMA1 */
 #define DMA2_PCLK_EN()   (RCC->AHB1ENR |= (1 << 22)) /*!< Enable clock for DMA2 */
 /** @} */

 /*******************************************************************************
  * 7. CLOCK DISABLE MACROS
  *******************************************************************************/

 /**
  * @defgroup GPIO_Clock_Disable Clock Disable Macros for GPIO Peripherals
  * @brief Macros to disable peripheral clock for GPIO ports
  * @{
  */
 #define GPIOA_PCLK_DI()  (RCC->AHB1ENR &= ~(1 << 0))  /*!< Disable clock for GPIOA */
 #define GPIOB_PCLK_DI()  (RCC->AHB1ENR &= ~(1 << 1))  /*!< Disable clock for GPIOB */
 #define GPIOC_PCLK_DI()  (RCC->AHB1ENR &= ~(1 << 2))  /*!< Disable clock for GPIOC */
 #define GPIOD_PCLK_DI()  (RCC->AHB1ENR &= ~(1 << 3))  /*!< Disable clock for GPIOD */
 #define GPIOE_PCLK_DI()  (RCC->AHB1ENR &= ~(1 << 4))  /*!< Disable clock for GPIOE */
 /* Note: GPIOF and GPIOG not available on STM32F446RE Nucleo */
 /* #define GPIOF_PCLK_DI()  (RCC->AHB1ENR &= ~(1 << 5)) */
 /* #define GPIOG_PCLK_DI()  (RCC->AHB1ENR &= ~(1 << 6)) */
 #define GPIOH_PCLK_DI()  (RCC->AHB1ENR &= ~(1 << 7))  /*!< Disable clock for GPIOH */
 /** @} */

 /**
  * @defgroup I2C_Clock_Disable Clock Disable Macros for I2C Peripherals
  * @{
  */
 #define I2C1_PCLK_DI()   (RCC->APB1ENR &= ~(1 << 21)) /*!< Disable clock for I2C1 */
 #define I2C2_PCLK_DI()   (RCC->APB1ENR &= ~(1 << 22)) /*!< Disable clock for I2C2 */
 #define I2C3_PCLK_DI()   (RCC->APB1ENR &= ~(1 << 23)) /*!< Disable clock for I2C3 */
 /** @} */

 /**
  * @defgroup SPI_Clock_Disable Clock Disable Macros for SPI Peripherals
  * @{
  */
 #define SPI1_PCLK_DI()   (RCC->APB2ENR &= ~(1 << 12)) /*!< Disable clock for SPI1 */
 #define SPI2_PCLK_DI()   (RCC->APB1ENR &= ~(1 << 14)) /*!< Disable clock for SPI2 */
 #define SPI3_PCLK_DI()   (RCC->APB1ENR &= ~(1 << 15)) /*!< Disable clock for SPI3 */
 #define SPI4_PCLK_DI()   (RCC->APB2ENR &= ~(1 << 13)) /*!< Disable clock for SPI4 */
 /** @} */

 /**
  * @defgroup USART_Clock_Disable Clock Disable Macros for USART Peripherals
  * @{
  */
 #define USART1_PCLK_DI() (RCC->APB2ENR &= ~(1 << 4))  /*!< Disable clock for USART1 */
 #define USART2_PCLK_DI() (RCC->APB1ENR &= ~(1 << 17)) /*!< Disable clock for USART2 */
 #define USART3_PCLK_DI() (RCC->APB1ENR &= ~(1 << 18)) /*!< Disable clock for USART3 */
 #define UART4_PCLK_DI()  (RCC->APB1ENR &= ~(1 << 19)) /*!< Disable clock for UART4 */
 #define UART5_PCLK_DI()  (RCC->APB1ENR &= ~(1 << 20)) /*!< Disable clock for UART5 */
 #define USART6_PCLK_DI() (RCC->APB2ENR &= ~(1 << 5))  /*!< Disable clock for USART6 */
 /** @} */

 /**
  * @defgroup Other_Clock_Disable Clock Disable Macros for Other Peripherals
  * @{
  */
 #define SYSCFG_PCLK_DI() (RCC->APB2ENR &= ~(1 << 14)) /*!< Disable clock for SYSCFG */

 #define TIM1_PCLK_DI()   (RCC->APB2ENR &= ~(1 << 0))  /*!< Disable clock for Tim*/


/**
 * Macros to reset GPIOx peripherals 
 */
#define GPIOA_REG_RESET()      do{ (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0)); } while(0)      /*!< Reset GPIOA */
#define GPIOB_REG_RESET()      do{ (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= (1 << 1)); } while(0)      /*!< Reset GPIOB */
#define GPIOC_REG_RESET()      do{ (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= (1 << 2)); } while(0)      /*!< Reset GPIOC */
#define GPIOD_REG_RESET()      do{ (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= (1 << 3)); } while(0)      /*!< Reset GPIOD */
#define GPIOE_REG_RESET()      do{ (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= (1 << 4)); } while(0)      /*!< Reset GPIOE */
#define GPIOH_REG_RESET()      do{ (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= (1 << 7)); } while(0)      /*!< Reset GPIOH */

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

#include "stm32f446xx_gpio_driver.h"
#endif

