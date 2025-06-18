/**
 * @file stm32f446xx.h
 * @brief STM32F446xx microcontroller peripheral definitions and macros.
 * @details This file provides comprehensive register definitions, base addresses,
 * and helper macros for the STM32F446xx family of ARM Cortex-M4 microcontrollers.
 * It acts as the central header for hardware abstraction, allowing direct
 * access and configuration of various on-chip peripherals and processor-specific features.
 *
 * @author Rahul B.
 * @date Jun 9, 2025
 * @version 1.0
 *
 * @note This header is specifically designed for the STM32F446xx series microcontrollers.
 * @warning Ensure proper understanding of the STM32F446xx reference manual for correct
 * usage of these definitions, especially regarding clock and reset configurations.
 */

#ifndef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#define __weak __attribute__((weak))
//==============================================================================
// START: Processor Specific Details
// ARM Cortex-M Processor NVIC (Nested Vectored Interrupt Controller) Registers
//==============================================================================

// NVIC Interrupt Set-Enable Registers (ISERx)
// These registers enable interrupts by writing a '1' to the corresponding bit.
#define NVIC_ISER0 (*(volatile uint32_t*)0xE000E100U)
#define NVIC_ISER1 (*(volatile uint32_t*)0xE000E104U)
#define NVIC_ISER2 (*(volatile uint32_t*)0xE000E108U)
#define NVIC_ISER3 (*(volatile uint32_t*)0xE000E10CU)
#define NVIC_ISER4 (*(volatile uint32_t*)0xE000E110U)
#define NVIC_ISER5 (*(volatile uint32_t*)0xE000E114U)
#define NVIC_ISER6 (*(volatile uint32_t*)0xE000E118U)
#define NVIC_ISER7 (*(volatile uint32_t*)0xE000E11CU)

// NVIC Interrupt Clear-Enable Registers (ICERx)
// These registers disable interrupts by writing a '1' to the corresponding bit.
#define NVIC_ICER0 (*(volatile uint32_t*)0xE000E180U)
#define NVIC_ICER1 (*(volatile uint32_t*)0xE000E184U)
#define NVIC_ICER2 (*(volatile uint32_t*)0xE000E188U)
#define NVIC_ICER3 (*(volatile uint32_t*)0xE000E18CU)
#define NVIC_ICER4 (*(volatile uint32_t*)0xE000E190U)
#define NVIC_ICER5 (*(volatile uint32_t*)0xE000E194U)
#define NVIC_ICER6 (*(volatile uint32_t*)0xE000E198U)
#define NVIC_ICER7 (*(volatile uint32_t*)0xE000E19CU)

// NVIC Interrupt Set-Pending Registers (ISPRx)
// These registers force interrupts into the pending state by writing a '1'.
#define NVIC_ISPR0 (*(volatile uint32_t*)0xE000E200U)
#define NVIC_ISPR1 (*(volatile uint32_t*)0xE000E204U)
#define NVIC_ISPR2 (*(volatile uint32_t*)0xE000E208U)
#define NVIC_ISPR3 (*(volatile uint32_t*)0xE000E20CU)
#define NVIC_ISPR4 (*(volatile uint32_t*)0xE000E210U)
#define NVIC_ISPR5 (*(volatile uint32_t*)0xE000E214U)
#define NVIC_ISPR6 (*(volatile uint32_t*)0xE000E218U)
#define NVIC_ISPR7 (*(volatile uint32_t*)0xE000E21CU)

// NVIC Interrupt Clear-Pending Registers (ICPRx)
// These registers remove interrupts from the pending state by writing a '1'.
#define NVIC_ICPR0 (*(volatile uint32_t*)0xE000E280U)
#define NVIC_ICPR1 (*(volatile uint32_t*)0xE000E284U)
#define NVIC_ICPR2 (*(volatile uint32_t*)0xE000E288U)
#define NVIC_ICPR3 (*(volatile uint32_t*)0xE000E28CU)
#define NVIC_ICPR4 (*(volatile uint32_t*)0xE000E290U)
#define NVIC_ICPR5 (*(volatile uint32_t*)0xE000E294U)
#define NVIC_ICPR6 (*(volatile uint32_t*)0xE000E298U)
#define NVIC_ICPR7 (*(volatile uint32_t*)0xE000E29CU)

// NVIC Interrupt Priority Registers Base Address
// Individual priority registers can be accessed using `NVIC_IPR(n)` macro.
#define NVIC_IPR_BASE (0xE000E400U)
#define NVIC_IPR(n) (*(volatile uint8_t*)(NVIC_IPR_BASE + (n)))

// Define NVIC_PR_BASE_ADDR for compatibility (redundant with NVIC_IPR_BASE but kept for consistency)
#define NVIC_PR_BASE_ADDR ((volatile uint32_t*)0xE000E400U)

// Number of priority bits implemented in the NVIC for STM32F446xx.
// This indicates the granularity of interrupt priority levels.
#define NO_PR_BITS_IMPLEMENTED (4)

// Helper macros for basic interrupt control (for IRQ 0-31).
// For higher IRQs, use the `_EXT` version.
#define NVIC_ENABLE_IRQ(irq) (NVIC_ISER0 |= (1U << (irq)))
#define NVIC_DISABLE_IRQ(irq) (NVIC_ICER0 |= (1U << (irq)))
#define NVIC_SET_PENDING(irq) (NVIC_ISPR0 |= (1U << (irq)))
#define NVIC_CLEAR_PENDING(irq) (NVIC_ICPR0 |= (1U << (irq)))

// Extended macro for enabling interrupts across all NVIC ISER registers (IRQ 0-95).
// This covers all available STM32F446xx interrupts.
#define NVIC_ENABLE_IRQ_EXT(irq)                           \
  do {                                                     \
    if ((irq) < 32)                                        \
      NVIC_ISER0 |= (1U << (irq));                         \
    else if ((irq) < 64)                                   \
      NVIC_ISER1 |= (1U << ((irq) - 32));                  \
    else if ((irq) < 96)                                   \
      NVIC_ISER2 |= (1U << ((irq) - 64));                  \
  } while (0)

//==============================================================================
// Base Addresses of Flash and SRAM Memories
//==============================================================================

#define FLASH_BASEADDR (0x08000000U) // Flash memory base address
#define SRAM1_BASEADDR (0x20000000U) // SRAM1 base address (112KB)
#define SRAM2_BASEADDR (0x2001C000U) // SRAM2 base address (16KB)
#define ROM_BASEADDR (0x1FFF0000U)   // System memory (ROM/Bootloader) base address
#define SRAM (SRAM1_BASEADDR)        // Default SRAM base address points to SRAM1

//==============================================================================
// AHBx and APBx Bus Peripheral Base Addresses
// These define the starting addresses for peripherals connected to different buses.
//==============================================================================

#define PERIPH_BASEADDR (0x40000000U)       // Base address for all peripherals
#define APB1PERIPH_BASEADDR (PERIPH_BASEADDR) // APB1 bus base address (same as general peripheral base)
#define APB2PERIPH_BASEADDR (0x40010000U)   // APB2 bus base address
#define AHB1PERIPH_BASEADDR (0x40020000U)   // AHB1 bus base address
#define AHB2PERIPH_BASEADDR (0x50000000U)   // AHB2 bus base address

//==============================================================================
// Base Addresses of Peripherals on AHB1 Bus
// GPIO ports and RCC are connected to the AHB1 bus.
// GPIO ports are mapped in 1KB blocks (0x400 offset between each port).
//==============================================================================

#define GPIOA_BASEADDR (AHB1PERIPH_BASEADDR + 0x0000) // GPIO Port A base address
#define GPIOB_BASEADDR (AHB1PERIPH_BASEADDR + 0x0400) // GPIO Port B base address
#define GPIOC_BASEADDR (AHB1PERIPH_BASEADDR + 0x0800) // GPIO Port C base address
#define GPIOD_BASEADDR (AHB1PERIPH_BASEADDR + 0x0C00) // GPIO Port D base address
#define GPIOE_BASEADDR (AHB1PERIPH_BASEADDR + 0x1000) // GPIO Port E base address
#define GPIOF_BASEADDR (AHB1PERIPH_BASEADDR + 0x1400) // GPIO Port F base address
#define GPIOG_BASEADDR (AHB1PERIPH_BASEADDR + 0x1800) // GPIO Port G base address
#define GPIOH_BASEADDR (AHB1PERIPH_BASEADDR + 0x1C00) // GPIO Port H base address

#define RCC_BASEADDR (AHB1PERIPH_BASEADDR + 0x3800) // RCC (Reset and Clock Control) base address

//==============================================================================
// Base Addresses of Peripherals on APB1 Bus
// APB1 peripherals generally operate at lower frequencies.
//==============================================================================

#define I2C1_BASEADDR (APB1PERIPH_BASEADDR + 0x5400) // I2C1 base address
#define I2C2_BASEADDR (APB1PERIPH_BASEADDR + 0x5800) // I2C2 base address
#define I2C3_BASEADDR (APB1PERIPH_BASEADDR + 0x5C00) // I2C3 base address

#define SPI2_BASEADDR (APB1PERIPH_BASEADDR + 0x3800) // SPI2 base address
#define SPI3_BASEADDR (APB1PERIPH_BASEADDR + 0x3C00) // SPI3 base address

#define USART2_BASEADDR (APB1PERIPH_BASEADDR + 0x4400) // USART2 base address
#define USART3_BASEADDR (APB1PERIPH_BASEADDR + 0x4800) // USART3 base address

#define UART4_BASEADDR (APB1PERIPH_BASEADDR + 0x4C00) // UART4 base address
#define UART5_BASEADDR (APB1PERIPH_BASEADDR + 0x5000) // UART5 base address

//==============================================================================
// Base Addresses of Peripherals on APB2 Bus
// APB2 peripherals generally operate at higher frequencies.
//==============================================================================

#define EXTI_BASEADDR (APB2PERIPH_BASEADDR + 0x3C00)   // EXTI (External Interrupt) base address
#define SPI1_BASEADDR (APB2PERIPH_BASEADDR + 0x3000)   // SPI1 base address
#define SYSCFG_BASEADDR (APB2PERIPH_BASEADDR + 0x3800) // SYSCFG (System Configuration Controller) base address
#define USART1_BASEADDR (APB2PERIPH_BASEADDR + 0x1000) // USART1 base address
#define USART6_BASEADDR (APB2PERIPH_BASEADDR + 0x1400) // USART6 base address
#define SPI4_BASEADDR (APB2PERIPH_BASEADDR + 0x3400) // SPI4 base address

//==============================================================================
// Peripheral Register Definition Structures
// These structures define the memory-mapped registers for each peripheral.
// Using `volatile` ensures that the compiler doesn't optimize away memory accesses.
//==============================================================================

/**
 * @brief GPIO peripheral registers
 * Each GPIO port (A-H) has the same register layout, with 32-bit registers.
 */
typedef struct {
  volatile uint32_t MODER;    // GPIO port mode register, Address offset: 0x00
  volatile uint32_t OTYPER;   // GPIO port output type register, Address offset: 0x04
  volatile uint32_t OSPEEDR;  // GPIO port output speed register, Address offset: 0x08
  volatile uint32_t PUPDR;    // GPIO port pull-up/pull-down register, Address offset: 0x0C
  volatile uint32_t IDR;      // GPIO port input data register, Address offset: 0x10
  volatile uint32_t ODR;      // GPIO port output data register, Address offset: 0x14
  volatile uint32_t BSRR;     // GPIO port bit set/reset register, Address offset: 0x18
  volatile uint32_t LCKR;     // GPIO port configuration lock register, Address offset: 0x1C
  volatile uint32_t AFR[2];   // GPIO alternate function registers, Address offset: 0x20-0x24
                              // AFR[0] = AFRL (for pins 0-7), AFR[1] = AFRH (for pins 8-15)
} GPIO_RegDef_t;

/**
 * @brief RCC peripheral registers
 * The Reset and Clock Control (RCC) peripheral manages system clocks and
 * peripheral resets across the microcontroller.
 */
typedef struct {
  volatile uint32_t CR;         // RCC clock control register, Address offset: 0x00
  volatile uint32_t PLLCFGR;    // RCC PLL configuration register, Address offset: 0x04
  volatile uint32_t CFGR;       // RCC clock configuration register, Address offset: 0x08
  volatile uint32_t CIR;        // RCC clock interrupt register, Address offset: 0x0C
  volatile uint32_t AHB1RSTR;   // RCC AHB1 peripheral reset register, Address offset: 0x10
  volatile uint32_t AHB2RSTR;   // RCC AHB2 peripheral reset register, Address offset: 0x14
  volatile uint32_t AHB3RSTR;   // RCC AHB3 peripheral reset register, Address offset: 0x18
  uint32_t RESERVED0;           // Reserved, Address offset: 0x1C
  volatile uint32_t APB1RSTR;   // RCC APB1 peripheral reset register, Address offset: 0x20
  volatile uint32_t APB2RSTR;   // RCC APB2 peripheral reset register, Address offset: 0x24
  uint32_t RESERVED1[2];        // Reserved, Address offset: 0x28-0x2C
  volatile uint32_t AHB1ENR;    // RCC AHB1 peripheral clock enable register, Address offset: 0x30
  volatile uint32_t AHB2ENR;    // RCC AHB2 peripheral clock enable register, Address offset: 0x34
  volatile uint32_t AHB3ENR;    // RCC AHB3 peripheral clock enable register, Address offset: 0x38
  uint32_t RESERVED2;           // Reserved, Address offset: 0x3C
  volatile uint32_t APB1ENR;    // RCC APB1 peripheral clock enable register, Address offset: 0x40
  volatile uint32_t APB2ENR;    // RCC APB2 peripheral clock enable register, Address offset: 0x44
  uint32_t RESERVED3[2];        // Reserved, Address offset: 0x48-0x4C
  volatile uint32_t AHB1LPENR;  // RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50
  volatile uint32_t AHB2LPENR;  // RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54
  volatile uint32_t AHB3LPENR;  // RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58
  uint32_t RESERVED4;           // Reserved, Address offset: 0x5C
  volatile uint32_t APB1LPENR;  // RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60
  volatile uint32_t APB2LPENR;  // RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64
  uint32_t RESERVED5[2];        // Reserved, Address offset: 0x68-0x6C
  volatile uint32_t BDCR;       // RCC Backup domain control register, Address offset: 0x70
  volatile uint32_t CSR;        // RCC clock control & status register, Address offset: 0x74
  uint32_t RESERVED6[2];        // Reserved, Address offset: 0x78-0x7C
  volatile uint32_t SSCGR;      // RCC spread spectrum clock generation register, Address offset: 0x80
  volatile uint32_t PLLI2SCFGR; // RCC PLLI2S configuration register, Address offset: 0x84
  volatile uint32_t PLLSAICFGR; // RCC PLLSAI configuration register, Address offset: 0x88
  volatile uint32_t DCKCFGR;    // RCC Dedicated Clocks configuration register, Address offset: 0x8C
  volatile uint32_t CKGATENR;   // RCC Clocks Gated Enable Register, Address offset: 0x90
  volatile uint32_t DCKCFGR2;   // RCC Dedicated Clocks configuration register 2, Address offset: 0x94
} RCC_RegDef_t;

/**
 * @brief EXTI peripheral registers
 * The External Interrupt/Event Controller (EXTI) manages interrupt and event
 * requests from external sources (GPIO pins) and some internal peripherals.
 */

typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIE;
	volatile uint32_t PR;
}EXTI_RegDef_t;

/*
 * Peripheral register definition structure for SPI
 */
typedef struct
{
	volatile uint32_t CR1;       /*!< SPI control register 1          - Address offset: 0x00 */
	volatile uint32_t CR2;       /*!< SPI control register 2          - Address offset: 0x04 */
	volatile uint32_t SR;        /*!< SPI status register             - Address offset: 0x08 */
	volatile uint32_t DR;        /*!< SPI data register               - Address offset: 0x0C */
	volatile uint32_t CRCPR;     /*!< SPI CRC polynomial register     - Address offset: 0x10 */
	volatile uint32_t RXCRCR;    /*!< SPI RX CRC register             - Address offset: 0x14 */
	volatile uint32_t TXCRCR;    /*!< SPI TX CRC register             - Address offset: 0x18 */
	volatile uint32_t I2SCFGR;   /*!< SPI_I2S configuration register  - Address offset: 0x1C */
	volatile uint32_t I2SPR;     /*!< SPI_I2S prescaler register      - Address offset: 0x20 */
} SPI_RegDef_t;

 /*
 * Peripheral register definition structure for I2C
 */
typedef struct
{
  volatile uint32_t CR1;        /*!< I2C Control register 1         - Address offset: 0x00 */
  volatile uint32_t CR2;        /*!< I2C Control register 2         - Address offset: 0x04 */
  volatile uint32_t OAR1;       /*!< I2C Own address register 1     - Address offset: 0x08 */
  volatile uint32_t OAR2;       /*!< I2C Own address register 2     - Address offset: 0x0C */
  volatile uint32_t DR;         /*!< I2C Data register              - Address offset: 0x10 */
  volatile uint32_t SR1;        /*!< I2C Status register 1          - Address offset: 0x14 */
  volatile uint32_t SR2;        /*!< I2C Status register 2          - Address offset: 0x18 */
  volatile uint32_t CCR;        /*!< I2C Clock control register     - Address offset: 0x1C */
  volatile uint32_t TRISE;      /*!< I2C TRISE register             - Address offset: 0x20 */
  volatile uint32_t FLTR;       /*!< I2C FLTR register              - Address offset: 0x24 */
} I2C_RegDef_t;

/**
 * @brief SYSCFG peripheral registers
 * The System Configuration Controller (SYSCFG) manages various system
 * configuration aspects, including external interrupt line mapping.
 */
typedef struct {
  volatile uint32_t MEMRMP;       // Memory remap register, Address offset: 0x00
  volatile uint32_t PMC;          // Peripheral mode configuration register, Address offset: 0x04
  volatile uint32_t EXTICR[4];    // External interrupt configuration registers, Address offset: 0x08-0x14
  volatile uint32_t RESERVED1[2]; // Reserved, Address offset: 0x18-0x1C
  volatile uint32_t CMPCR;        // Compensation cell control register, Address offset: 0x20
  volatile uint32_t RESERVED2[2]; // Reserved, Address offset: 0x24-0x28
  volatile uint32_t CFGR;         // Configuration register, Address offset: 0x2C
} SYSCFG_RegDef_t;

//==============================================================================
// Peripheral Definitions
// These macros provide easy access to peripheral registers by typecasting their
// base addresses to the corresponding register definition structures.
//==============================================================================

#define GPIOA ((GPIO_RegDef_t*)GPIOA_BASEADDR) // Pointer to GPIO Port A registers
#define GPIOB ((GPIO_RegDef_t*)GPIOB_BASEADDR) // Pointer to GPIO Port B registers
#define GPIOC ((GPIO_RegDef_t*)GPIOC_BASEADDR) // Pointer to GPIO Port C registers
#define GPIOD ((GPIO_RegDef_t*)GPIOD_BASEADDR) // Pointer to GPIO Port D registers
#define GPIOE ((GPIO_RegDef_t*)GPIOE_BASEADDR) // Pointer to GPIO Port E registers
#define GPIOF ((GPIO_RegDef_t*)GPIOF_BASEADDR) // Pointer to GPIO Port F registers
#define GPIOG ((GPIO_RegDef_t*)GPIOG_BASEADDR) // Pointer to GPIO Port G registers
#define GPIOH ((GPIO_RegDef_t*)GPIOH_BASEADDR) // Pointer to GPIO Port H registers

#define RCC ((RCC_RegDef_t*)RCC_BASEADDR)          // Pointer to RCC registers
#define EXTI ((EXTI_RegDef_t*)EXTI_BASEADDR)       // Pointer to EXTI registers
#define SYSCFG ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR) // Pointer to SYSCFG registers

#define SPI1 ((SPI_RegDef_t*)SPI1_BASEADDR) // Pointer to SPI1 registers
#define SPI2 ((SPI_RegDef_t*)SPI2_BASEADDR) // Pointer to SPI2 registers
#define SPI3 ((SPI_RegDef_t*)SPI3_BASEADDR) // Pointer to SPI3 registers
#define SPI4 ((SPI_RegDef_t*)SPI4_BASEADDR) // Pointer to SPI4 registers

#define USART1 ((USART_RegDef_t*)USART1_BASEADDR) // Pointer to USART1 registers
#define USART2 ((USART_RegDef_t*)USART2_BASEADDR) // Pointer to USART2 registers
#define USART3 ((USART_RegDef_t*)USART3_BASEADDR) // Pointer to USART3 registers
#define UART4 ((USART_RegDef_t*)UART4_BASEADDR)   // Pointer to UART4 registers
#define UART5 ((USART_RegDef_t*)UART5_BASEADDR)   // Pointer to UART5 registers
#define USART6 ((USART_RegDef_t*)USART6_BASEADDR) // Pointer to USART6 registers
=======
#define I2C1 ((I2C_RegDef_t *)I2C1_BASEADDR)
#define I2C2 ((I2C_RegDef_t *)I2C2_BASEADDR)
#define I2C3 ((I2C_RegDef_t *)I2C3_BASEADDR)


//==============================================================================
// Clock Enable Macros for GPIOx Peripherals
// These macros enable the clock for specific GPIO ports by setting the
// corresponding bit in the RCC AHB1 peripheral clock enable register (AHB1ENR).
//==============================================================================

#define GPIOA_PCLK_EN() (RCC->AHB1ENR |= (1 << 0)) // Enable GPIOA peripheral clock
#define GPIOB_PCLK_EN() (RCC->AHB1ENR |= (1 << 1)) // Enable GPIOB peripheral clock
#define GPIOC_PCLK_EN() (RCC->AHB1ENR |= (1 << 2)) // Enable GPIOC peripheral clock
#define GPIOD_PCLK_EN() (RCC->AHB1ENR |= (1 << 3)) // Enable GPIOD peripheral clock
#define GPIOE_PCLK_EN() (RCC->AHB1ENR |= (1 << 4)) // Enable GPIOE peripheral clock
#define GPIOF_PCLK_EN() (RCC->AHB1ENR |= (1 << 5)) // Enable GPIOF peripheral clock
#define GPIOG_PCLK_EN() (RCC->AHB1ENR |= (1 << 6)) // Enable GPIOG peripheral clock
#define GPIOH_PCLK_EN() (RCC->AHB1ENR |= (1 << 7)) // Enable GPIOH peripheral clock

#define SYSCFG_PCLK_EN()                     			(RCC->AHB1ENR |= (1 << 14))          /* Enable GPIOH peripheral clock */

/*
* Clock Enable Macros for SPI peripherals
*/
#define SPI1_PCLK_EN()                        (RCC->APB2ENR |= (1 << 12))   /* Enable SPI1 peripheral clock */
#define SPI2_PCLK_EN()                        (RCC->APB1ENR |= (1 << 14))   /* Enable SPI2 peripheral clock */
#define SPI3_PCLK_EN()                        (RCC->APB1ENR |= (1 << 15))   /* Enable SPI3 peripheral clock */
#define SPI4_PCLK_EN()                        (RCC->APB2ENR |= (1 << 13))   /* Enable SPI4 peripheral clock */

/*

* Clock Enable Macros for USART/UART peripherals
*/
#define USART1_PCLK_EN()                      (RCC->APB2ENR |= (1 << 4))    /* Enable USART1 peripheral clock */
#define USART2_PCLK_EN()                      (RCC->APB1ENR |= (1 << 17))   /* Enable USART2 peripheral clock */
#define USART3_PCLK_EN()                      (RCC->APB1ENR |= (1 << 18))   /* Enable USART3 peripheral clock */
#define UART4_PCLK_EN()                       (RCC->APB1ENR |= (1 << 19))   /* Enable UART4 peripheral clock */
#define UART5_PCLK_EN()                       (RCC->APB1ENR |= (1 << 20))   /* Enable UART5 peripheral clock */
#define USART6_PCLK_EN()                      (RCC->APB2ENR |= (1 << 5))    /* Enable USART6 peripheral clock */

=======
* Clock Enable Macros for I2C peripherals
*/
#define I2C1_PCLK_EN()                        (RCC->APB1ENR |= (1 << 21))   /* Enable I2C1 peripheral clock */
#define I2C2_PCLK_EN()                        (RCC->APB1ENR |= (1 << 22))   /* Enable I2C2 peripheral clock */
#define I2C3_PCLK_EN()                        (RCC->APB1ENR |= (1 << 23))   /* Enable I2C3 peripheral clock */


//==============================================================================
// Clock Disable Macros for GPIOx Peripherals
// These macros disable peripheral clocks by clearing the corresponding bit in RCC_AHB1ENR.
//==============================================================================

#define GPIOA_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 0)) // Disable GPIOA peripheral clock
#define GPIOB_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 1)) // Disable GPIOB peripheral clock
#define GPIOC_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 2)) // Disable GPIOC peripheral clock
#define GPIOD_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 3)) // Disable GPIOD peripheral clock
#define GPIOE_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 4)) // Disable GPIOE peripheral clock
#define GPIOF_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 5)) // Disable GPIOF peripheral clock
#define GPIOG_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 6)) // Disable GPIOG peripheral clock
#define GPIOH_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 7)) // Disable GPIOH peripheral clock

/*
* Clock Disable Macros for SPI peripherals
*/
#define SPI1_PCLK_DI()                        (RCC->APB2ENR &= ~(1 << 12))   /* Disable SPI1 peripheral clock */
#define SPI2_PCLK_DI()                        (RCC->APB1ENR &= ~(1 << 14))   /* Disable SPI2 peripheral clock */
#define SPI3_PCLK_DI()                        (RCC->APB1ENR &= ~(1 << 15))   /* Disable SPI3 peripheral clock */
#define SPI4_PCLK_DI()                        (RCC->APB2ENR &= ~(1 << 13))   /* Disable SPI4 peripheral clock */

/*

* Clock Disable Macros for USART/UART peripherals
*/
#define USART1_PCLK_DI()                      (RCC->APB2ENR &= ~(1 << 4))    /* Disable USART1 peripheral clock */
#define USART2_PCLK_DI()                      (RCC->APB1ENR &= ~(1 << 17))   /* Disable USART2 peripheral clock */
#define USART3_PCLK_DI()                      (RCC->APB1ENR &= ~(1 << 18))   /* Disable USART3 peripheral clock */
#define UART4_PCLK_DI()                       (RCC->APB1ENR &= ~(1 << 19))   /* Disable UART4 peripheral clock */
#define UART5_PCLK_DI()                       (RCC->APB1ENR &= ~(1 << 20))   /* Disable UART5 peripheral clock */
#define USART6_PCLK_DI()                      (RCC->APB2ENR &= ~(1 << 5))    /* Disable USART6 peripheral clock */

=======
* Clock Disable Macros for I2C peripherals
*/
#define I2C1_PCLK_DI()                        (RCC->APB1ENR &= ~(1 << 21))   /* Disable I2C1 peripheral clock */
#define I2C2_PCLK_DI()                        (RCC->APB1ENR &= ~(1 << 22))   /* Disable I2C2 peripheral clock */
#define I2C3_PCLK_DI()                        (RCC->APB1ENR &= ~(1 << 23))   /* Disable I2C3 peripheral clock */

/*
 * Macros to reset GPIOx peripherals
 * These macros perform a peripheral reset by toggling the reset bit in RCC_AHB1RSTR
 * The do-while(0) construct ensures the macro behaves like a function call
 */
#define GPIOA_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)  /* Reset GPIOA peripheral */
#define GPIOB_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)  /* Reset GPIOB peripheral */
#define GPIOC_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)  /* Reset GPIOC peripheral */
#define GPIOD_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3)); }while(0)  /* Reset GPIOD peripheral */
#define GPIOE_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4)); }while(0)  /* Reset GPIOE peripheral */
#define GPIOF_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5)); }while(0)  /* Reset GPIOF peripheral */
#define GPIOG_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6)); }while(0)  /* Reset GPIOG peripheral */
#define GPIOH_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7)); }while(0)  /* Reset GPIOH peripheral */

#define SPI1_REG_RESET()     do { RCC->APB2RSTR |=  (1 << 12); RCC->APB2RSTR &= ~(1 << 12); } while(0)
#define SPI2_REG_RESET()     do { RCC->APB1RSTR |=  (1 << 14); RCC->APB1RSTR &= ~(1 << 14); } while(0)
#define SPI3_REG_RESET()     do { RCC->APB1RSTR |=  (1 << 15); RCC->APB1RSTR &= ~(1 << 15); } while(0)
#define SPI4_REG_RESET()     do { RCC->APB2RSTR |=  (1 << 13); RCC->APB2RSTR &= ~(1 << 13); } while(0)


/*
 * Macros to reset USART/UART peripherals
 */
#define USART1_REG_RESET()   do { RCC->APB2RSTR |=  (1 << 4);  RCC->APB2RSTR &= ~(1 << 4);  } while(0)
#define USART2_REG_RESET()   do { RCC->APB1RSTR |=  (1 << 17); RCC->APB1RSTR &= ~(1 << 17); } while(0)
#define USART3_REG_RESET()   do { RCC->APB1RSTR |=  (1 << 18); RCC->APB1RSTR &= ~(1 << 18); } while(0)
#define UART4_REG_RESET()    do { RCC->APB1RSTR |=  (1 << 19); RCC->APB1RSTR &= ~(1 << 19); } while(0)
#define UART5_REG_RESET()    do { RCC->APB1RSTR |=  (1 << 20); RCC->APB1RSTR &= ~(1 << 20); } while(0)
#define USART6_REG_RESET()   do { RCC->APB2RSTR |=  (1 << 5);  RCC->APB2RSTR &= ~(1 << 5);  } while(0)
=======
#define I2C1_REG_RESET()       do{ (RCC->APB1RSTR |= (1 << 21)); (RCC->APB1RSTR &= ~(1 << 21)); }while(0)
#define I2C2_REG_RESET()       do{ (RCC->APB1RSTR |= (1 << 22)); (RCC->APB1RSTR &= ~(1 << 22)); }while(0)
#define I2C3_REG_RESET()       do{ (RCC->APB1RSTR |= (1 << 23)); (RCC->APB1RSTR &= ~(1 << 23)); }while(0)



/**
 * @brief Returns the port code for a given GPIOx base address.
 * This macro returns a unique code (0-7) for each GPIO port base address,
 * useful for array indexing or switch statements.
 * @param x The base address of the GPIO port (e.g., GPIOA).
 * @return An integer representing the GPIO port code.
 */
#define GPIO_BASEADDR_TO_CODE(x)                                                                  \
  ((x == GPIOA) ? 0 : (x == GPIOB) ? 1 : (x == GPIOC) ? 2 : (x == GPIOD) ? 3 : (x == GPIOE) ? 4   \
                                                                       : (x == GPIOF) ? 5         \
                                                                       : (x == GPIOG) ? 6         \
                                                                       : (x == GPIOH) ? 7         \
                                                                                      : 0)

//==============================================================================
// IRQ (Interrupt Request) Numbers for STM32F446RE MCU
// These define the positions in the Nested Vectored Interrupt Controller (NVIC)
// vector table for each interrupt source.
// NOTE: These values are specific to the STM32F446RE and should be verified
// against the device's reference manual if targeting a different MCU.
//==============================================================================

// IRQ Numbers for EXTI (External Interrupt/Event Controller) Lines
#define IRQ_NO_EXTI0 6      // EXTI Line 0 interrupt
#define IRQ_NO_EXTI1 7      // EXTI Line 1 interrupt
#define IRQ_NO_EXTI2 8      // EXTI Line 2 interrupt
#define IRQ_NO_EXTI3 9      // EXTI Line 3 interrupt
#define IRQ_NO_EXTI4 10     // EXTI Line 4 interrupt
#define IRQ_NO_EXTI9_5 23   // EXTI Lines [9:5] interrupts
#define IRQ_NO_EXTI15_10 40 // EXTI Lines [15:10] interrupts

// NVIC Interrupt Priority Levels for STM32F446RE
// These define the possible priority levels for interrupts. A lower number
// indicates a higher priority. The STM32F446xx implements 4 bits for priority.
#define NVIC_IRQ_PRI0 0  // Highest priority
#define NVIC_IRQ_PRI1 1
#define NVIC_IRQ_PRI2 2
#define NVIC_IRQ_PRI3 3
#define NVIC_IRQ_PRI4 4
#define NVIC_IRQ_PRI5 5
#define NVIC_IRQ_PRI6 6
#define NVIC_IRQ_PRI7 7
#define NVIC_IRQ_PRI8 8
#define NVIC_IRQ_PRI9 9
#define NVIC_IRQ_PRI10 10
#define NVIC_IRQ_PRI11 11
#define NVIC_IRQ_PRI12 12
#define NVIC_IRQ_PRI13 13
#define NVIC_IRQ_PRI14 14
#define NVIC_IRQ_PRI15 15 // Lowest priority

// IRQ Numbers for SPI (Serial Peripheral Interface)
#define IRQ_NO_SPI1 35
#define IRQ_NO_SPI2 36
#define IRQ_NO_SPI3 51
#define IRQ_NO_SPI4 84

// IRQ Numbers for I2C (Inter-Integrated Circuit)
#define IRQ_NO_I2C1_EV 31 // I2C1 Event interrupt
#define IRQ_NO_I2C1_ER 32 // I2C1 Error interrupt
#define IRQ_NO_I2C2_EV 33 // I2C2 Event interrupt
#define IRQ_NO_I2C2_ER 34 // I2C2 Error interrupt
#define IRQ_NO_I2C3_EV 72 // I2C3 Event interrupt
#define IRQ_NO_I2C3_ER 73 // I2C3 Error interrupt

// IRQ Numbers for UART/USART (Universal Asynchronous Receiver/Transmitter)
#define IRQ_NO_USART1 37
#define IRQ_NO_USART2 38
#define IRQ_NO_USART3 39
#define IRQ_NO_UART4 52
#define IRQ_NO_UART5 53
#define IRQ_NO_USART6 71

// IRQ Numbers for Timers
#define IRQ_NO_TIM1_BRK_TIM9 24    // TIM1 Break interrupt and TIM9 global interrupt
#define IRQ_NO_TIM1_UP_TIM10 25    // TIM1 Update interrupt and TIM10 global interrupt
#define IRQ_NO_TIM1_TRG_COM_TIM11 26 // TIM1 Trigger and Commutation interrupts and TIM11 global interrupt
#define IRQ_NO_TIM1_CC 27          // TIM1 Capture Compare interrupt
#define IRQ_NO_TIM2 28             // TIM2 global interrupt
#define IRQ_NO_TIM3 29             // TIM3 global interrupt
#define IRQ_NO_TIM4 30             // TIM4 global interrupt
#define IRQ_NO_TIM5 50             // TIM5 global interrupt
#define IRQ_NO_TIM6_DAC 54         // TIM6 global interrupt and DAC underrun interrupt
#define IRQ_NO_TIM7 55             // TIM7 global interrupt
#define IRQ_NO_TIM8_BRK_TIM12 43   // TIM8 Break interrupt and TIM12 global interrupt
#define IRQ_NO_TIM8_UP_TIM13 44    // TIM8 Update interrupt and TIM13 global interrupt
#define IRQ_NO_TIM8_TRG_COM_TIM14 45 // TIM8 Trigger and Commutation interrupts and TIM14 global interrupt
#define IRQ_NO_TIM8_CC 46          // TIM8 Capture Compare interrupt

// IRQ Numbers for ADC (Analog-to-Digital Converter)
#define IRQ_NO_ADC 18

// IRQ Numbers for DMA (Direct Memory Access) controllers.
// DMA1 Streams
#define IRQ_NO_DMA1_STREAM0 11
#define IRQ_NO_DMA1_STREAM1 12
#define IRQ_NO_DMA1_STREAM2 13
#define IRQ_NO_DMA1_STREAM3 14
#define IRQ_NO_DMA1_STREAM4 15
#define IRQ_NO_DMA1_STREAM5 16
#define IRQ_NO_DMA1_STREAM6 17
#define IRQ_NO_DMA1_STREAM7 47

// DMA2 Streams
#define IRQ_NO_DMA2_STREAM0 56
#define IRQ_NO_DMA2_STREAM1 57
#define IRQ_NO_DMA2_STREAM2 58
#define IRQ_NO_DMA2_STREAM3 59
#define IRQ_NO_DMA2_STREAM4 60
#define IRQ_NO_DMA2_STREAM5 68
#define IRQ_NO_DMA2_STREAM6 69
#define IRQ_NO_DMA2_STREAM7 70

// IRQ Numbers for CAN (Controller Area Network) interfaces.
#define IRQ_NO_CAN1_TX 19    // CAN1 Transmit interrupt
#define IRQ_NO_CAN1_RX0 20   // CAN1 Receive FIFO 0 interrupt
#define IRQ_NO_CAN1_RX1 21   // CAN1 Receive FIFO 1 interrupt
#define IRQ_NO_CAN1_SCE 22   // CAN1 Status Change Error interrupt
#define IRQ_NO_CAN2_TX 63    // CAN2 Transmit interrupt
#define IRQ_NO_CAN2_RX0 64   // CAN2 Receive FIFO 0 interrupt
#define IRQ_NO_CAN2_RX1 65   // CAN2 Receive FIFO 1 interrupt
#define IRQ_NO_CAN2_SCE 66   // CAN2 Status Change Error interrupt

// IRQ Numbers for USB (Universal Serial Bus) interfaces.
#define IRQ_NO_OTG_FS 67         // USB On-The-Go Full Speed interrupt
#define IRQ_NO_OTG_HS_EP1_OUT 74 // USB On-The-Go High Speed EP1 Out interrupt
#define IRQ_NO_OTG_HS_EP1_IN 75  // USB On-The-Go High Speed EP1 In interrupt
#define IRQ_NO_OTG_HS_WKUP 76    // USB On-The-Go High Speed Wakeup interrupt
#define IRQ_NO_OTG_HS 77         // USB On-The-Go High Speed global interrupt

// IRQ Numbers for RTC (Real-Time Clock).
#define IRQ_NO_RTC_ALARM 41 // RTC Alarm interrupt
#define IRQ_NO_RTC_WKUP 3   // RTC Wakeup interrupt

// IRQ Numbers for System-level events.
#define IRQ_NO_WWDG 0       // Window Watchdog interrupt
#define IRQ_NO_PVD 1        // Power Voltage Detector interrupt
#define IRQ_NO_TAMP_STAMP 2 // Tamper and TimeStamp interrupts
#define IRQ_NO_FLASH 4      // Flash global interrupt
#define IRQ_NO_RCC 5        // Reset and Clock Control global interrupt

// IRQ Numbers for FPU (Floating Point Unit).
#define IRQ_NO_FPU 81

// IRQ Numbers for DCMI (Digital Camera Interface).
#define IRQ_NO_DCMI 78

// IRQ Numbers for FMPI2C1 (Fast-mode Plus I2C1) - specific to STM32F446.
#define IRQ_NO_FMPI2C1_EV 95 // FMPI2C1 Event interrupt
#define IRQ_NO_FMPI2C1_ER 96 // FMPI2C1 Error interrupt

// IRQ Numbers for QUADSPI (Quad SPI) - specific to STM32F446.
#define IRQ_NO_QUADSPI 91

// IRQ Numbers for CEC (Consumer Electronics Control) - specific to STM32F446.
#define IRQ_NO_CEC 94

// IRQ Numbers for SAI (Serial Audio Interface) - specific to STM32F446.
#define IRQ_NO_SAI1 87
#define IRQ_NO_SAI2 91

// IRQ Numbers for SPDIF-RX (Sony/Philips Digital Interface Receiver) - specific to STM32F446.
#define IRQ_NO_SPDIF_RX 97

/*
 * Some generic macros for common values.
 * These provide readable names for commonly used values across various
 * peripheral configurations and operations.
 */
#define ENABLE            (1)                 /* Generic enable value */
#define DISABLE           (0)                 /* Generic disable value */
#define SET               (ENABLE)            /* Generic set value */
#define RESET             (DISABLE)           /* Generic reset value */
#define GPIO_PIN_SET      (SET)               /* GPIO pin set state */
#define GPIO_PIN_RESET    (RESET)             /* GPIO pin reset state */
#define FLAG_RESET				RESET
#define FLAG_SET					SET

/*
 * Bit position definitions for SPI peripheral
 */

// SPI_CR1
#define SPI_CR1_CPHA         0  /*!< Clock Phase */
#define SPI_CR1_CPOL         1  /*!< Clock Polarity */
#define SPI_CR1_MSTR         2  /*!< Master Selection */
#define SPI_CR1_BR           3  /*!< Baud Rate Control (3 bits: [5:3]) */
#define SPI_CR1_SPE          6  /*!< SPI Enable */
#define SPI_CR1_LSBFIRST     7  /*!< Frame Format */
#define SPI_CR1_SSI          8  /*!< Internal Slave Select */
#define SPI_CR1_SSM          9  /*!< Software Slave Management */
#define SPI_CR1_RXONLY       10 /*!< Receive Only */
#define SPI_CR1_DFF          11 /*!< Data Frame Format */
#define SPI_CR1_CRCNEXT      12 /*!< CRC Transfer Next */
#define SPI_CR1_CRCEN        13 /*!< Hardware CRC Calculation Enable */
#define SPI_CR1_BIDIOE       14 /*!< Output Enable in Bidirectional Mode */
#define SPI_CR1_BIDIMODE     15 /*!< Bidirectional Data Mode Enable */

// SPI_CR2
#define SPI_CR2_RXDMAEN      0  /*!< Rx Buffer DMA Enable */
#define SPI_CR2_TXDMAEN      1  /*!< Tx Buffer DMA Enable */
#define SPI_CR2_SSOE         2  /*!< SS Output Enable */
#define SPI_CR2_FRF          4  /*!< Frame Format */
#define SPI_CR2_ERRIE        5  /*!< Error Interrupt Enable */
#define SPI_CR2_RXNEIE       6  /*!< RX buffer Not Empty Interrupt Enable */
#define SPI_CR2_TXEIE        7  /*!< Tx buffer Empty Interrupt Enable */

// SPI_SR
#define SPI_SR_RXNE          0  /*!< Receive Buffer Not Empty */
#define SPI_SR_TXE           1  /*!< Transmit Buffer Empty */
#define SPI_SR_CHSIDE        2  /*!< Channel Side */
#define SPI_SR_UDR           3  /*!< Underrun Flag */
#define SPI_SR_CRCERR        4  /*!< CRC Error Flag */
#define SPI_SR_MODF          5  /*!< Mode Fault */
#define SPI_SR_OVR           6  /*!< Overrun Flag */
#define SPI_SR_BSY           7  /*!< Busy Flag */
#define SPI_SR_FRE           8  /*!< Frame Format Error */

#include "stm32f446xx_gpio_driver.h"
#include "stm32f446xx_spi_driver.h"
#include "stm32f446xx_USART_driver.h"
#include "stm32f4xx_rcc_driver.h"

/*
 * Bit position definitions for I2C peripheral
 */

// I2C Control Register 1 (I2C_CR1)
#define I2C_CR1_PE           0  /*!< Peripheral Enable */
#define I2C_CR1_SMBUS        1  /*!< SMBus Mode */
#define I2C_CR1_SMBTYPE      3  /*!< SMBus Type */
#define I2C_CR1_ENARP        4  /*!< ARP Enable */
#define I2C_CR1_ENPEC        5  /*!< PEC Enable */
#define I2C_CR1_ENGC         6  /*!< General Call Enable */
#define I2C_CR1_NOSTRETCH    7  /*!< Clock Stretching Disable */
#define I2C_CR1_START        8  /*!< Start Generation */
#define I2C_CR1_STOP         9  /*!< Stop Generation */
#define I2C_CR1_ACK         10  /*!< Acknowledge Enable */
#define I2C_CR1_POS         11  /*!< Acknowledge/PEC Position */
#define I2C_CR1_PEC         12  /*!< Packet Error Checking */
#define I2C_CR1_ALERT       13  /*!< SMBus Alert */
#define I2C_CR1_SWRST       15  /*!< Software Reset */

// I2C Control Register 2 (I2C_CR2)
#define I2C_CR2_FREQ         0  /*!< Peripheral Clock Frequency */
#define I2C_CR2_ITERREN      8  /*!< Error Interrupt Enable */
#define I2C_CR2_ITEVTEN      9  /*!< Event Interrupt Enable */
#define I2C_CR2_ITBUFEN     10  /*!< Buffer Interrupt Enable */
#define I2C_CR2_DMAEN       11  /*!< DMA Requests Enable */
#define I2C_CR2_LAST        12  /*!< DMA Last Transfer */

// I2C Status Register 1 (I2C_SR1)
#define I2C_SR1_SB           0  /*!< Start Bit */
#define I2C_SR1_ADDR        1  /*!< Address Sent/Matched */
#define I2C_SR1_BTF         2  /*!< Byte Transfer Finished */
#define I2C_SR1_ADD10       3  /*!< 10-bit Header Sent */
#define I2C_SR1_STOPF       4  /*!< Stop Detection */
#define I2C_SR1_RXNE        6  /*!< Data Register Not Empty */
#define I2C_SR1_TXE         7  /*!< Data Register Empty */
#define I2C_SR1_BERR        8  /*!< Bus Error */
#define I2C_SR1_ARLO        9  /*!< Arbitration Lost */
#define I2C_SR1_AF         10  /*!< Acknowledge Failure */
#define I2C_SR1_OVR        11  /*!< Overrun/Underrun */
#define I2C_SR1_PECERR     12  /*!< PEC Error in Reception */
#define I2C_SR1_TIMEOUT    14  /*!< Timeout or Tlow Error */
#define I2C_SR1_SMBALERT   15  /*!< SMBus Alert */
 
// I2C Status Register 2 (I2C_SR2)
#define I2C_SR2_MSL         0  /*!< Master/Slave */
#define I2C_SR2_BUSY        1  /*!< Bus Busy */
#define I2C_SR2_TRA         2  /*!< Transmitter/Receiver */
#define I2C_SR2_GENCALL     4  /*!< General Call Address */
#define I2C_SR2_SMBDEFAULT  5  /*!< SMBus Device Default Address */
#define I2C_SR2_SMBHOST     6  /*!< SMBus Host Header */
#define I2C_SR2_DUALF       7  /*!< Dual Flag */
#define I2C_SR2_PEC         8  /*!< Packet Error Checking Register */

// I2C Clock Control Register (I2C_CCR)
#define I2C_CCR_CCR         0  /*!< Clock Control Register */
#define I2C_CCR_DUTY       14  /*!< Fast Mode Duty Cycle */
#define I2C_CCR_FS         15  /*!< I2C Master Mode Selection */

#include "stm32f446xx_gpio_driver.h"
#include "stm32f446xx_spi_driver.h"
#include "stm32f446xx_i2c_driver.h"
>>>>>>> i2c

#endif /* INC_STM32F446XX_H_ */
