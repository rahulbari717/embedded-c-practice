/*
 * stm32f446xx.h
 *
 * Created on: Jun 9, 2025
 * Author: Rahul B.
 */

#ifndef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_

#include <stdint.h>

/*
 * START : Processor Specific Details
 * ARM Cortex Mx Processor NVIC ISERx register addresses
 */

/* NVIC Interrupt Set-Enable Registers */
#define NVIC_ISER0          (*(volatile uint32_t*)0xE000E100U)
#define NVIC_ISER1          (*(volatile uint32_t*)0xE000E104U)
#define NVIC_ISER2          (*(volatile uint32_t*)0xE000E108U)
#define NVIC_ISER3          (*(volatile uint32_t*)0xE000E10CU)
#define NVIC_ISER4          (*(volatile uint32_t*)0xE000E110U)
#define NVIC_ISER5          (*(volatile uint32_t*)0xE000E114U)
#define NVIC_ISER6          (*(volatile uint32_t*)0xE000E118U)
#define NVIC_ISER7          (*(volatile uint32_t*)0xE000E11CU)

/* NVIC Interrupt Clear-Enable Registers */
#define NVIC_ICER0          (*(volatile uint32_t*)0xE000E180U)
#define NVIC_ICER1          (*(volatile uint32_t*)0xE000E184U)
#define NVIC_ICER2          (*(volatile uint32_t*)0xE000E188U)
#define NVIC_ICER3          (*(volatile uint32_t*)0xE000E18CU)
#define NVIC_ICER4          (*(volatile uint32_t*)0xE000E190U)
#define NVIC_ICER5          (*(volatile uint32_t*)0xE000E194U)
#define NVIC_ICER6          (*(volatile uint32_t*)0xE000E198U)
#define NVIC_ICER7          (*(volatile uint32_t*)0xE000E19CU)

/* NVIC Interrupt Set-Pending Registers */
#define NVIC_ISPR0          (*(volatile uint32_t*)0xE000E200U)
#define NVIC_ISPR1          (*(volatile uint32_t*)0xE000E204U)
#define NVIC_ISPR2          (*(volatile uint32_t*)0xE000E208U)
#define NVIC_ISPR3          (*(volatile uint32_t*)0xE000E20CU)
#define NVIC_ISPR4          (*(volatile uint32_t*)0xE000E210U)
#define NVIC_ISPR5          (*(volatile uint32_t*)0xE000E214U)
#define NVIC_ISPR6          (*(volatile uint32_t*)0xE000E218U)
#define NVIC_ISPR7          (*(volatile uint32_t*)0xE000E21CU)

/* NVIC Interrupt Clear-Pending Registers */
#define NVIC_ICPR0          (*(volatile uint32_t*)0xE000E280U)
#define NVIC_ICPR1          (*(volatile uint32_t*)0xE000E284U)
#define NVIC_ICPR2          (*(volatile uint32_t*)0xE000E288U)
#define NVIC_ICPR3          (*(volatile uint32_t*)0xE000E28CU)
#define NVIC_ICPR4          (*(volatile uint32_t*)0xE000E290U)
#define NVIC_ICPR5          (*(volatile uint32_t*)0xE000E294U)
#define NVIC_ICPR6          (*(volatile uint32_t*)0xE000E298U)
#define NVIC_ICPR7          (*(volatile uint32_t*)0xE000E29CU)

/* NVIC Interrupt Priority Registers Base Address */
#define NVIC_IPR_BASE         (0xE000E400U)
#define NVIC_IPR(n)           (*(volatile uint8_t*)(NVIC_IPR_BASE + (n)))

/* ADDED: Define NVIC_PR_BASE_ADDR for your function compatibility */
#define NVIC_PR_BASE_ADDR     ((volatile uint32_t*)0xE000E400U)


#define NO_PR_BITS_IMPLEMENTED			(4)

/* Helper macros for interrupt control */
#define NVIC_ENABLE_IRQ(irq)    (NVIC_ISER0 |= (1U << (irq)))
#define NVIC_DISABLE_IRQ(irq)   (NVIC_ICER0 |= (1U << (irq)))
#define NVIC_SET_PENDING(irq)   (NVIC_ISPR0 |= (1U << (irq)))
#define NVIC_CLEAR_PENDING(irq) (NVIC_ICPR0 |= (1U << (irq)))

/* For interrupts 32-63, use ISER1, etc. */
#define NVIC_ENABLE_IRQ_EXT(irq)  do { \
    if ((irq) < 32) NVIC_ISER0 |= (1U << (irq)); \
    else if ((irq) < 64) NVIC_ISER1 |= (1U << ((irq) - 32)); \
    else if ((irq) < 96) NVIC_ISER2 |= (1U << ((irq) - 64)); \
} while(0)

/*
 * Base addresses of Flash and SRAM memories
 */
#define FLASH_BASEADDR                      			(0x08000000U)       						/* Flash memory base address */
#define SRAM1_BASEADDR                      			(0x20000000U)       						/* SRAM1 base address (112KB) */
#define SRAM2_BASEADDR                      			(0x2001C000U)       						/* SRAM2 base address (16KB) */
#define ROM_BASEADDR                        			(0x1FFF0000U)       						/* System memory (ROM) base address */
#define SRAM                                							(SRAM1_BASEADDR)    			/* Default SRAM points to SRAM1 */

/*
 * AHBx and APBx Bus Peripheral base addresses
 */
#define PERIPH_BASEADDR                     			(0x40000000U)       						/* Peripheral base address */
#define APB1PERIPH_BASEADDR                 	(PERIPH_BASEADDR)   				/* APB1 peripheral base address */
#define APB2PERIPH_BASEADDR                 	(0x40010000U)       						/* APB2 peripheral base address */
#define AHB1PERIPH_BASEADDR                 	(0x40020000U)       						/* AHB1 peripheral base address */
#define AHB2PERIPH_BASEADDR                 	(0x50000000U)       						/* AHB2 peripheral base address */

/*
 * Base addresses of peripherals hanging on AHB1 bus
 * GPIO ports are mapped in 1KB blocks (0x400 offset between each port)
 */
#define GPIOA_BASEADDR                      			(AHB1PERIPH_BASEADDR + 0x0000)  			/* GPIO Port A base address */
#define GPIOB_BASEADDR                      			(AHB1PERIPH_BASEADDR + 0x0400)  			/* GPIO Port B base address */
#define GPIOC_BASEADDR                      			(AHB1PERIPH_BASEADDR + 0x0800)  			/* GPIO Port C base address */
#define GPIOD_BASEADDR                      			(AHB1PERIPH_BASEADDR + 0x0C00)  			/* GPIO Port D base address */
#define GPIOE_BASEADDR                      			(AHB1PERIPH_BASEADDR + 0x1000)  			/* GPIO Port E base address */
#define GPIOF_BASEADDR                      			(AHB1PERIPH_BASEADDR + 0x1400)  			/* GPIO Port F base address */
#define GPIOG_BASEADDR                      			(AHB1PERIPH_BASEADDR + 0x1800)  			/* GPIO Port G base address */
#define GPIOH_BASEADDR                      			(AHB1PERIPH_BASEADDR + 0x1C00)  			/* GPIO Port H base address */

#define RCC_BASEADDR                        			(AHB1PERIPH_BASEADDR + 0x3800)  			/* RCC (Reset and Clock Control) base address */

/*
 * Base addresses of peripherals hanging on APB1 bus
 * APB1 peripherals operate at lower frequencies
 */
#define I2C1_BASEADDR                       				(APB1PERIPH_BASEADDR + 0x5400) 			/* I2C1 base address */
#define I2C2_BASEADDR                       				(APB1PERIPH_BASEADDR + 0x5800)  			/* I2C2 base address */
#define I2C3_BASEADDR                       				(APB1PERIPH_BASEADDR + 0x5C00)  			/* I2C3 base address */

#define SPI2_BASEADDR                       				(APB1PERIPH_BASEADDR + 0x3800)  			/* SPI2 base address */
#define SPI3_BASEADDR                       				(APB1PERIPH_BASEADDR + 0x3C00)  			/* SPI3 base address */

#define USART2_BASEADDR                     		(APB1PERIPH_BASEADDR + 0x4400)  			/* USART2 base address */
#define USART3_BASEADDR                     		(APB1PERIPH_BASEADDR + 0x4800)  			/* USART3 base address */

#define UART4_BASEADDR                      			(APB1PERIPH_BASEADDR + 0x4C00)  			/* UART4 base address */
#define UART5_BASEADDR                      			(APB1PERIPH_BASEADDR + 0x5000)  			/* UART5 base address */

/*
 * Base addresses of peripherals hanging on APB2 bus
 * APB2 peripherals operate at higher frequencies
 */
#define EXTI_BASEADDR                      	 			(APB2PERIPH_BASEADDR + 0x3C00)  			/* EXTI (External Interrupt) base address */
#define SPI1_BASEADDR                       				(APB2PERIPH_BASEADDR + 0x3000)  			/* SPI1 base address */
#define SYSCFG_BASEADDR                     		(APB2PERIPH_BASEADDR + 0x3800)  			/* SYSCFG (System Configuration) base address */
#define USART1_BASEADDR                     		(APB2PERIPH_BASEADDR + 0x1000)  			/* USART1 base address */
#define USART6_BASEADDR                     		(APB2PERIPH_BASEADDR + 0x1400)  			/* USART6 base address */

/*
 * Peripheral register definition structures
 */

/*
 * GPIO peripheral registers
 * Each GPIO port has the same register layout with 32-bit registers
 */
typedef struct
{
    volatile uint32_t   MODER;                                /* GPIO port mode register,                   		 Address offset: 0x00 */
    volatile uint32_t   OTYPER;                               /* GPIO port output type register,            	Address offset: 0x04 */
    volatile uint32_t   OSPEEDR;                             /* GPIO port output speed register,          	 Address offset: 0x08 */
    volatile uint32_t   PUPDR;                                  	/* GPIO port pull-up/pull-down register,   Address offset: 0x0C */
    volatile uint32_t   IDR;                                    		/* GPIO port input data register,             		Address offset: 0x10 */
    volatile uint32_t   ODR;                                    	/* GPIO port output data register,            	Address offset: 0x14 */
    volatile uint32_t   BSRR;                                   	/* GPIO port bit set/reset register,          		Address offset: 0x18 */
    volatile uint32_t   LCKR;                                   	/* GPIO port configuration lock register,    Address offset: 0x1C */
    volatile uint32_t   AFR[2];                                 	/* GPIO alternate function registers,         	Address offset: 0x20-0x24 */
    																					/* AFR[0] = AFRL (pins 0-7), AFR[1] = AFRH (pins 8-15) */
} GPIO_RegDef_t;

/*
 * RCC peripheral registers
 * Reset and Clock Control peripheral manages system clocks and peripheral resets
 */
typedef struct
{
    volatile uint32_t CR;                                       		/* RCC clock control register,                Address offset: 0x00 */
    volatile uint32_t PLLCFGR;                               	/* RCC PLL configuration register,            Address offset: 0x04 */
    volatile uint32_t CFGR;                                     	/* RCC clock configuration register,          Address offset: 0x08 */
    volatile uint32_t CIR;                                      		/* RCC clock interrupt register,              Address offset: 0x0C */
    volatile uint32_t AHB1RSTR;                            /* RCC AHB1 peripheral reset register,        Address offset: 0x10 */
    volatile uint32_t AHB2RSTR;                            /* RCC AHB2 peripheral reset register,        Address offset: 0x14 */
    volatile uint32_t AHB3RSTR;                            /* RCC AHB3 peripheral reset register,        Address offset: 0x18 */
    uint32_t RESERVED0;                                         	/* Reserved, 0x1C                                                  */
    volatile uint32_t APB1RSTR;                             /* RCC APB1 peripheral reset register,        Address offset: 0x20 */
    volatile uint32_t APB2RSTR;                             /* RCC APB2 peripheral reset register,        Address offset: 0x24 */
    uint32_t RESERVED1[2];                                    	/* Reserved, 0x28-0x2C                                             */
    volatile uint32_t AHB1ENR;                              /* RCC AHB1 peripheral clock register,        Address offset: 0x30 */
    volatile uint32_t AHB2ENR;                              /* RCC AHB2 peripheral clock register,        Address offset: 0x34 */
    volatile uint32_t AHB3ENR;                              /* RCC AHB3 peripheral clock register,        Address offset: 0x38 */
    uint32_t RESERVED2;                                         /* Reserved, 0x3C                                                  */
    volatile uint32_t APB1ENR;                               /* RCC APB1 peripheral clock enable register, Address offset: 0x40 */
    volatile uint32_t APB2ENR;                               /* RCC APB2 peripheral clock enable register, Address offset: 0x44 */
    uint32_t RESERVED3[2];                                    	/* Reserved, 0x48-0x4C                                             */
    volatile uint32_t AHB1LPENR;                         /* RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
    volatile uint32_t AHB2LPENR;                         /* RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
    volatile uint32_t AHB3LPENR;                         /* RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
    uint32_t RESERVED4;                                         /* Reserved, 0x5C                                                  */
    volatile uint32_t APB1LPENR;                          /* RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
    volatile uint32_t APB2LPENR;                          /* RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
    uint32_t RESERVED5[2];                                    	/* Reserved, 0x68-0x6C                                             */
    volatile uint32_t BDCR;                                     	/* RCC Backup domain control register,        Address offset: 0x70 */
    volatile uint32_t CSR;                                      		/* RCC clock control & status register,       Address offset: 0x74 */
    uint32_t RESERVED6[2];                                    	/* Reserved, 0x78-0x7C                                             */
    volatile uint32_t SSCGR;                                    	/* RCC spread spectrum clock generation register, Address offset: 0x80 */
    volatile uint32_t PLLI2SCFGR;                         	/* RCC PLLI2S configuration register,         Address offset: 0x84 */
    volatile uint32_t PLLSAICFGR;                        	/* RCC PLLSAI configuration register,         Address offset: 0x88 */
    volatile uint32_t DCKCFGR;                             	/* RCC Dedicated Clocks configuration register, Address offset: 0x8C */
    volatile uint32_t CKGATENR;                           /* RCC Clocks Gated ENable Register,          Address offset: 0x90 */
    volatile uint32_t DCKCFGR2;                           /* RCC Dedicated Clocks configuration register 2, Address offset: 0x94 */
} RCC_RegDef_t;

/*
 * Peripheral register definition structures for EXTI
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
 * Peripheral register definition structures for SYSCFG
 */

typedef struct
{
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR[4];
	volatile uint32_t RESERVED1[2];
	volatile uint32_t CMPCR;
	volatile uint32_t RESERVED2[2];
	volatile uint32_t CFGR;
}SYSCFG_RegDef_t;

/*
 * Peripheral definitions (Peripheral base addresses typecasted to xxx_RegDef_t)
 * These macros provide easy access to peripheral registers
 */
#define GPIOA                              								((GPIO_RegDef_t*)GPIOA_BASEADDR)    /* GPIO Port A register pointer */
#define GPIOB                               								((GPIO_RegDef_t*)GPIOB_BASEADDR)    /* GPIO Port B register pointer */
#define GPIOC                               							((GPIO_RegDef_t*)GPIOC_BASEADDR)    /* GPIO Port C register pointer */
#define GPIOD                              								((GPIO_RegDef_t*)GPIOD_BASEADDR)    /* GPIO Port D register pointer */
#define GPIOE                               								((GPIO_RegDef_t*)GPIOE_BASEADDR)    /* GPIO Port E register pointer */
#define GPIOF                               								((GPIO_RegDef_t*)GPIOF_BASEADDR)    /* GPIO Port F register pointer */
#define GPIOG                               							((GPIO_RegDef_t*)GPIOG_BASEADDR)    /* GPIO Port G register pointer */
#define GPIOH                               							((GPIO_RegDef_t*)GPIOH_BASEADDR)    /* GPIO Port H register pointer */

#define RCC                                 								((RCC_RegDef_t*)RCC_BASEADDR)       /* RCC register pointer */

#define EXTI																((EXTI_RegDef_t*)EXTI_BASEADDR)

#define SYSCFG															((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

/*
 * Clock Enable Macros for GPIOx peripherals
 * These macros enable clocks by setting corresponding bits in RCC_AHB1ENR
 */
#define GPIOA_PCLK_EN()                     			(RCC->AHB1ENR |= (1 << 0))          /* Enable GPIOA peripheral clock */
#define GPIOB_PCLK_EN()                     				(RCC->AHB1ENR |= (1 << 1))          /* Enable GPIOB peripheral clock */
#define GPIOC_PCLK_EN()                     			(RCC->AHB1ENR |= (1 << 2))          /* Enable GPIOC peripheral clock */
#define GPIOD_PCLK_EN()                     			(RCC->AHB1ENR |= (1 << 3))          /* Enable GPIOD peripheral clock */
#define GPIOE_PCLK_EN()                     				(RCC->AHB1ENR |= (1 << 4))          /* Enable GPIOE peripheral clock */
#define GPIOF_PCLK_EN()                     				(RCC->AHB1ENR |= (1 << 5))          /* Enable GPIOF peripheral clock */
#define GPIOG_PCLK_EN()                     			(RCC->AHB1ENR |= (1 << 6))          /* Enable GPIOG peripheral clock */
#define GPIOH_PCLK_EN()                     			(RCC->AHB1ENR |= (1 << 7))          /* Enable GPIOH peripheral clock */

#define SYSCFG_PCLK_EN()                     			(RCC->AHB1ENR |= (1 << 14))          /* Enable GPIOH peripheral clock */

/*
 * Clock Disable Macros for GPIOx peripherals
 * These macros disable peripheral clocks by clearing corresponding bits in RCC_AHB1ENR
 */
#define GPIOA_PCLK_DI()                     				(RCC->AHB1ENR &= ~(1 << 0))         /* Disable GPIOA peripheral clock */
#define GPIOB_PCLK_DI()                     				(RCC->AHB1ENR &= ~(1 << 1))         /* Disable GPIOB peripheral clock */
#define GPIOC_PCLK_DI()                     				(RCC->AHB1ENR &= ~(1 << 2))         /* Disable GPIOC peripheral clock */
#define GPIOD_PCLK_DI()                     				(RCC->AHB1ENR &= ~(1 << 3))         /* Disable GPIOD peripheral clock */
#define GPIOE_PCLK_DI()                     				(RCC->AHB1ENR &= ~(1 << 4))         /* Disable GPIOE peripheral clock */
#define GPIOF_PCLK_DI()                     				(RCC->AHB1ENR &= ~(1 << 5))         /* Disable GPIOF peripheral clock */
#define GPIOG_PCLK_DI()                     				(RCC->AHB1ENR &= ~(1 << 6))         /* Disable GPIOG peripheral clock */
#define GPIOH_PCLK_DI()                     				(RCC->AHB1ENR &= ~(1 << 7))         /* Disable GPIOH peripheral clock */

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

/*
 *  returns port code for given GPIOx base address
 *  this macros returns a code (between 0 to 7) for a given GPIO base address (x)
 * */
#define GPIO_BASEADDR_TO_CODE(x)    	(	 (x == GPIOA) ? 0 :\
																			 (x == GPIOB) ? 1 :\
																			 (x == GPIOC) ? 2 :\
																			 (x == GPIOD) ? 3 :\
																			 (x == GPIOE) ? 4 :\
																			 (x == GPIOF) ? 5 :\
																			 (x == GPIOG) ? 6 :\
																			 (x == GPIOH) ? 7 : 0)

/*
 * IRQ no. of STM32F446RE MCU
 * NOTE: update these macros with valid values according to your MCU
 */

/* IRQ Numbers for EXTI Lines */
#define IRQ_NO_EXTI0                6
#define IRQ_NO_EXTI1                7
#define IRQ_NO_EXTI2                8
#define IRQ_NO_EXTI3                9
#define IRQ_NO_EXTI4                10
#define IRQ_NO_EXTI9_5              23
#define IRQ_NO_EXTI15_10            40

// NVIC Interrupt Priority Levels for STM32F446RE
#define NVIC_IRQ_PRI0              0   // Highest priority
#define NVIC_IRQ_PRI1              1
#define NVIC_IRQ_PRI2              2
#define NVIC_IRQ_PRI3              3
#define NVIC_IRQ_PRI4              4
#define NVIC_IRQ_PRI5              5
#define NVIC_IRQ_PRI6              6
#define NVIC_IRQ_PRI7              7
#define NVIC_IRQ_PRI8              8
#define NVIC_IRQ_PRI9              9
#define NVIC_IRQ_PRI10             10
#define NVIC_IRQ_PRI11             11
#define NVIC_IRQ_PRI12             12
#define NVIC_IRQ_PRI13             13
#define NVIC_IRQ_PRI14             14
#define NVIC_IRQ_PRI15             15  // Lowest priority


/* IRQ Numbers for SPI */
#define IRQ_NO_SPI1                 35
#define IRQ_NO_SPI2                 36
#define IRQ_NO_SPI3                 51
#define IRQ_NO_SPI4                 84

/* IRQ Numbers for I2C */
#define IRQ_NO_I2C1_EV              31
#define IRQ_NO_I2C1_ER              32
#define IRQ_NO_I2C2_EV              33
#define IRQ_NO_I2C2_ER              34
#define IRQ_NO_I2C3_EV              72
#define IRQ_NO_I2C3_ER              73

/* IRQ Numbers for UART/USART */
#define IRQ_NO_USART1               37
#define IRQ_NO_USART2               38
#define IRQ_NO_USART3               39
#define IRQ_NO_UART4                52
#define IRQ_NO_UART5                53
#define IRQ_NO_USART6               71

/* IRQ Numbers for Timers */
#define IRQ_NO_TIM1_BRK_TIM9        24
#define IRQ_NO_TIM1_UP_TIM10        25
#define IRQ_NO_TIM1_TRG_COM_TIM11   26
#define IRQ_NO_TIM1_CC              27
#define IRQ_NO_TIM2                 28
#define IRQ_NO_TIM3                 29
#define IRQ_NO_TIM4                 30
#define IRQ_NO_TIM5                 50
#define IRQ_NO_TIM6_DAC             54
#define IRQ_NO_TIM7                 55
#define IRQ_NO_TIM8_BRK_TIM12       43
#define IRQ_NO_TIM8_UP_TIM13        44
#define IRQ_NO_TIM8_TRG_COM_TIM14   45
#define IRQ_NO_TIM8_CC              46

/* IRQ Numbers for ADC */
#define IRQ_NO_ADC                  18

/* IRQ Numbers for DMA */
#define IRQ_NO_DMA1_STREAM0         11
#define IRQ_NO_DMA1_STREAM1         12
#define IRQ_NO_DMA1_STREAM2         13
#define IRQ_NO_DMA1_STREAM3         14
#define IRQ_NO_DMA1_STREAM4         15
#define IRQ_NO_DMA1_STREAM5         16
#define IRQ_NO_DMA1_STREAM6         17
#define IRQ_NO_DMA1_STREAM7         47

#define IRQ_NO_DMA2_STREAM0         56
#define IRQ_NO_DMA2_STREAM1         57
#define IRQ_NO_DMA2_STREAM2         58
#define IRQ_NO_DMA2_STREAM3         59
#define IRQ_NO_DMA2_STREAM4         60
#define IRQ_NO_DMA2_STREAM5         68
#define IRQ_NO_DMA2_STREAM6         69
#define IRQ_NO_DMA2_STREAM7         70

/* IRQ Numbers for CAN */
#define IRQ_NO_CAN1_TX              19
#define IRQ_NO_CAN1_RX0             20
#define IRQ_NO_CAN1_RX1             21
#define IRQ_NO_CAN1_SCE             22
#define IRQ_NO_CAN2_TX              63
#define IRQ_NO_CAN2_RX0             64
#define IRQ_NO_CAN2_RX1             65
#define IRQ_NO_CAN2_SCE             66

/* IRQ Numbers for USB */
#define IRQ_NO_OTG_FS               67
#define IRQ_NO_OTG_HS_EP1_OUT       74
#define IRQ_NO_OTG_HS_EP1_IN        75
#define IRQ_NO_OTG_HS_WKUP          76
#define IRQ_NO_OTG_HS               77

/* IRQ Numbers for RTC */
#define IRQ_NO_RTC_ALARM            41
#define IRQ_NO_RTC_WKUP             3

/* IRQ Numbers for System */
#define IRQ_NO_WWDG                 0
#define IRQ_NO_PVD                  1
#define IRQ_NO_TAMP_STAMP           2
#define IRQ_NO_FLASH                4
#define IRQ_NO_RCC                  5

/* IRQ Numbers for FPU */
#define IRQ_NO_FPU                  81

/* IRQ Numbers for DCMI */
#define IRQ_NO_DCMI                 78

/* IRQ Numbers for FMPI2C1 (specific to STM32F446) */
#define IRQ_NO_FMPI2C1_EV           95
#define IRQ_NO_FMPI2C1_ER           96

/* IRQ Numbers for QUADSPI (specific to STM32F446) */
#define IRQ_NO_QUADSPI              91

/* IRQ Numbers for CEC (specific to STM32F446) */
#define IRQ_NO_CEC                  94

/* IRQ Numbers for SAI (specific to STM32F446) */
#define IRQ_NO_SAI1                 87
#define IRQ_NO_SAI2                 91

/* IRQ Numbers for SPDIF-RX (specific to STM32F446) */
#define IRQ_NO_SPDIF_RX             97


/*
 * Some generic macros for common values
 * These provide readable names for commonly used values
 */
#define ENABLE                              							(1)                 /* Generic enable value */
#define DISABLE                             							(0)                 /* Generic disable value */
#define SET                                 								(ENABLE)            /* Generic set value */
#define RESET                               							(DISABLE)           /* Generic reset value */
#define GPIO_PIN_SET                        					(SET)               /* GPIO pin set state */
#define GPIO_PIN_RESET                      				(RESET)             /* GPIO pin reset state */


#include "stm32f446xx_gpio_driver.h"

#endif /* INC_STM32F446XX_H_ */
