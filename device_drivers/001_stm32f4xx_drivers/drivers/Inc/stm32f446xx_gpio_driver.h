/**
 * @file stm32f446xx_gpio_driver.h
 * @brief GPIO driver header file for STM32F446xx microcontroller
 * @details This file contains all the function prototypes, macros, and data structures
 *          required for GPIO (General Purpose Input/Output) operations on STM32F446xx.
 *          It provides a hardware abstraction layer for GPIO configuration and control.
 *
 * @author Rahul B.
 * @date Jun 9, 2025
 * @version 1.0
 *
 * @note This driver is specifically designed for STM32F446xx series microcontrollers
 * @warning Ensure proper clock configuration before using GPIO functions
 */

#ifndef INC_STM32F446XX_GPIO_DRIVER_H_
#define INC_STM32F446XX_GPIO_DRIVER_H_

#include "stm32f446xx.h"

/**
 * @brief GPIO Pin Configuration Structure
 * @details This structure contains all the configurable parameters for a GPIO pin.
 *          It is used to set up the desired functionality and characteristics of
 *          individual GPIO pins.
 */
typedef struct
{
    uint8_t GPIO_PinNumber;          /**< GPIO pin number (0-15) @ref GPIO_PIN_NUMBERS */
    uint8_t GPIO_PinMode;            /**< GPIO pin mode (Input/Output/Alt/Analog/Interrupt) @ref GPIO_PIN_MODES */
    uint8_t GPIO_PinSpeed;           /**< GPIO output speed configuration @ref GPIO_PIN_SPEED */
    uint8_t GPIO_PinPuPdControl;     /**< Pull-up/Pull-down resistor configuration @ref GPIO_PIN_PUPD */
    uint8_t GPIO_PinOPType;          /**< Output type (Push-Pull/Open-Drain) @ref GPIO_PIN_OUTPUT_TYPES */
    uint8_t GPIO_PinAltFunMode;      /**< Alternate function selection (AF0-AF15) @ref GPIO_PIN_ALT_FUN_MODE */
} GPIO_PinConfig_t;

/**
 * @brief GPIO Handle Structure
 * @details This structure serves as a handle for GPIO operations. It contains
 *          a pointer to the GPIO peripheral register structure and the pin
 *          configuration settings.
 */
typedef struct
{
    GPIO_RegDef_t *pGPIOx;           /**< Pointer to GPIO peripheral base address (GPIOA, GPIOB, etc.) */
    GPIO_PinConfig_t GPIO_PinConfig; /**< GPIO pin configuration settings */
} GPIO_Handle_t;

/*
 * =============================================================================
 * GPIO PIN NUMBER DEFINITIONS
 * =============================================================================
 */

/**
 * @defgroup GPIO_PIN_NUMBERS GPIO Pin Numbers
 * @brief Macros for GPIO pin number selection
 * @details These macros define the available pin numbers (0-15) for each GPIO port.
 *          Each GPIO port has 16 pins numbered from 0 to 15.
 * @{
 */
#define GPIO_PIN_NO_0       0        /**< GPIO Pin 0 */
#define GPIO_PIN_NO_1       1        /**< GPIO Pin 1 */
#define GPIO_PIN_NO_2       2        /**< GPIO Pin 2 */
#define GPIO_PIN_NO_3       3        /**< GPIO Pin 3 */
#define GPIO_PIN_NO_4       4        /**< GPIO Pin 4 */
#define GPIO_PIN_NO_5       5        /**< GPIO Pin 5 */
#define GPIO_PIN_NO_6       6        /**< GPIO Pin 6 */
#define GPIO_PIN_NO_7       7        /**< GPIO Pin 7 */
#define GPIO_PIN_NO_8       8        /**< GPIO Pin 8 */
#define GPIO_PIN_NO_9       9        /**< GPIO Pin 9 */
#define GPIO_PIN_NO_10      10       /**< GPIO Pin 10 */
#define GPIO_PIN_NO_11      11       /**< GPIO Pin 11 */
#define GPIO_PIN_NO_12      12       /**< GPIO Pin 12 */
#define GPIO_PIN_NO_13      13       /**< GPIO Pin 13 */
#define GPIO_PIN_NO_14      14       /**< GPIO Pin 14 */
#define GPIO_PIN_NO_15      15       /**< GPIO Pin 15 */
/** @} */

/*
 * =============================================================================
 * GPIO PIN MODE DEFINITIONS
 * =============================================================================
 */

/**
 * @defgroup GPIO_PIN_MODES GPIO Pin Modes
 * @brief GPIO pin operating mode configurations
 * @details These macros define the different operating modes available for GPIO pins.
 *          Modes include basic I/O, alternate functions, analog, and interrupt modes.
 * @{
 */
#define GPIO_MODE_IN        0       /**< Input mode - Pin configured as digital input */
#define GPIO_MODE_OUT       1       /**< Output mode - Pin configured as digital output */
#define GPIO_MODE_ALTFN     2       /**< Alternate function mode - Pin used for peripheral functions */
#define GPIO_MODE_ANALOG    3       /**< Analog mode - Pin used for analog operations (ADC/DAC) */

#define GPIO_MODE_IT_FT     4       /**< Interrupt mode - Rising edge trigger */
#define GPIO_MODE_IT_RT     5       /**< Interrupt mode - Falling edge trigger */
#define GPIO_MODE_IT_RFT    6       /**< Interrupt mode - Both rising and falling edge trigger */
/** @} */

/*
 * =============================================================================
 * GPIO OUTPUT TYPE DEFINITIONS
 * =============================================================================
 */

/**
 * @defgroup GPIO_PIN_OUTPUT_TYPES GPIO Pin Output Types
 * @brief GPIO pin output driver configurations
 * @details These macros define the output driver type for GPIO pins in output mode.
 * @{
 */
#define GPIO_OP_TYPE_PP     0       /**< Push-Pull output - Can drive both high and low */
#define GPIO_OP_TYPE_OD     1       /**< Open-Drain output - Can only pull low, needs external pull-up */
/** @} */

/*
 * =============================================================================
 * GPIO OUTPUT SPEED DEFINITIONS
 * =============================================================================
 */

/**
 * @defgroup GPIO_PIN_SPEED GPIO Pin Output Speed
 * @brief GPIO pin output speed configurations
 * @details These macros define the slew rate/speed of GPIO pins in output mode.
 *          Higher speeds consume more power but provide faster switching.
 * @{
 */
#define GPIO_SPEED_LOW      0       /**< Low speed (2 MHz) - Lower power consumption */
#define GPIO_SPEED_MEDIUM   1       /**< Medium speed (25 MHz) - Balanced power and performance */
#define GPIO_SPEED_FAST     2       /**< Fast speed (50 MHz) - Higher performance */
#define GPIO_SPEED_HIGH     3       /**< High speed (100 MHz) - Maximum performance, highest power */
/** @} */

/*
 * =============================================================================
 * GPIO PULL-UP/PULL-DOWN DEFINITIONS
 * =============================================================================
 */

/**
 * @defgroup GPIO_PIN_PUPD GPIO Pin Pull-up/Pull-down Configuration
 * @brief GPIO pin internal resistor configurations
 * @details These macros configure the internal pull-up/pull-down resistors.
 *          Useful for ensuring defined logic levels on input pins.
 * @{
 */
#define GPIO_NO_PUPD        0       /**< No internal pull-up or pull-down resistor */
#define GPIO_PIN_PU         1       /**< Internal pull-up resistor enabled (~40kΩ) */
#define GPIO_PIN_PD         2       /**< Internal pull-down resistor enabled (~40kΩ) */
/** @} */

/*
 * =============================================================================
 * GPIO ALTERNATE FUNCTION DEFINITIONS
 * =============================================================================
 */

<<<<<<< HEAD
/*******************************************************************************
 *          APIs supported by this driver
 *          For more information about the APIs check the function definitions
 *******************************************************************************/
=======
/**
 * @defgroup GPIO_PIN_ALT_FUN_MODE GPIO Pin Alternate Function Modes
 * @brief GPIO pin alternate function selections
 * @details These macros define the alternate function mappings (AF0-AF15).
 *          Each alternate function connects the pin to a specific peripheral.
 *          Refer to STM32F446xx datasheet for specific AF mappings per pin.
 * @{
 */
#define GPIO_AF0            0       /**< Alternate Function 0 - System functions */
#define GPIO_AF1            1       /**< Alternate Function 1 - TIM1/TIM2 */
#define GPIO_AF2            2       /**< Alternate Function 2 - TIM3/TIM4/TIM5 */
#define GPIO_AF3            3       /**< Alternate Function 3 - TIM8/TIM9/TIM10/TIM11 */
#define GPIO_AF4            4       /**< Alternate Function 4 - I2C1/I2C2/I2C3 */
#define GPIO_AF5            5       /**< Alternate Function 5 - SPI1/SPI2/SPI3/SPI4 */
#define GPIO_AF6            6       /**< Alternate Function 6 - SPI2/SPI3/SAI1 */
#define GPIO_AF7            7       /**< Alternate Function 7 - UART/USART */
#define GPIO_AF8            8       /**< Alternate Function 8 - UART4/UART5/USART6 */
#define GPIO_AF9            9       /**< Alternate Function 9 - CAN1/CAN2/TIM12/TIM13/TIM14 */
#define GPIO_AF10           10      /**< Alternate Function 10 - OTG_FS/OTG_HS */
#define GPIO_AF11           11      /**< Alternate Function 11 - ETH */
#define GPIO_AF12           12      /**< Alternate Function 12 - FMC/SDIO/OTG_HS */
#define GPIO_AF13           13      /**< Alternate Function 13 - DCMI */
#define GPIO_AF14           14      /**< Alternate Function 14 - LCD-TFT */
#define GPIO_AF15           15      /**< Alternate Function 15 - EVENTOUT */
/** @} */
>>>>>>> 79afe4b (Proper format and commets added to the code ...)

/*
 * =============================================================================
 * GPIO DRIVER API DECLARATIONS
 * =============================================================================
 */

/**
 * @defgroup GPIO_Driver_APIs GPIO Driver APIs
 * @brief Complete set of APIs for GPIO operations
 * @details This section contains all the function prototypes for GPIO driver operations
 *          including initialization, configuration, data manipulation, and interrupt handling.
 * @{
 */

/*
 * =============================================================================
 * PERIPHERAL CLOCK CONTROL
 * =============================================================================
 */

/**
 * @brief Enable or disable peripheral clock for GPIO port
 * @details This function controls the clock supply to the specified GPIO peripheral.
 *          The peripheral clock must be enabled before any GPIO operations.
 *
 * @param[in] pGPIOx Pointer to GPIO peripheral base address (GPIOA, GPIOB, etc.)
 * @param[in] EnorDi Enable (ENABLE) or Disable (DISABLE) the peripheral clock
 *
 * @return None
 *
 * @note Must be called before any GPIO configuration or operation
 * @warning Disabling clock while GPIO is in use may cause unexpected behavior
 *
 * @code
 * // Enable clock for GPIOA
 * GPIO_PeriClockControl(GPIOA, ENABLE);
 * @endcode
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/*
 * =============================================================================
 * INITIALIZATION AND DE-INITIALIZATION
 * =============================================================================
 */

/**
 * @brief Initialize GPIO pin with specified configuration
 * @details This function configures a GPIO pin according to the settings provided
 *          in the GPIO handle structure. It sets up mode, speed, output type,
 *          pull-up/pull-down, and alternate function as specified.
 *
 * @param[in] pGPIOHandle Pointer to GPIO handle containing port and pin configuration
 *
 * @return None
 *
 * @note Peripheral clock must be enabled before calling this function
 * @warning Invalid configuration parameters may cause malfunction
 *
 * @code
 * GPIO_Handle_t gpio_led;
 * gpio_led.pGPIOx = GPIOA;
 * gpio_led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
 * gpio_led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
 * gpio_led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
 * gpio_led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
 * gpio_led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
 * GPIO_Init(&gpio_led);
 * @endcode
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);

/**
 * @brief Reset GPIO port to default state
 * @details This function resets all registers of the specified GPIO port to their
 *          default reset values. All pins of the port will be reconfigured to
 *          their default state.
 *
 * @param[in] pGPIOx Pointer to GPIO peripheral base address (GPIOA, GPIOB, etc.)
 *
 * @return None
 *
 * @warning This will affect all 16 pins of the specified GPIO port
 * @note Use with caution in systems where other pins of the same port are in use
 *
 * @code
 * // Reset entire GPIOA port
 * GPIO_DeInit(GPIOA);
 * @endcode
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/*
 * =============================================================================
 * DATA READ AND WRITE OPERATIONS
 * =============================================================================
 */

/**
 * @brief Read the state of a specific GPIO input pin
 * @details This function reads the current logic level of the specified GPIO pin.
 *          The pin should be configured in input mode before calling this function.
 *
 * @param[in] pGPIOx Pointer to GPIO peripheral base address (GPIOA, GPIOB, etc.)
 * @param[in] PinNumber Pin number to read (0-15)
 *
 * @return uint8_t Current pin state (0 for LOW, 1 for HIGH)
 *
 * @note Pin should be configured in input mode for reliable reading
 *
 * @code
 * // Read state of GPIOA pin 0
 * uint8_t pin_state = GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0);
 * if(pin_state == GPIO_PIN_SET) {
 *     // Pin is high
 * }
 * @endcode
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/**
 * @brief Read the state of entire GPIO port
 * @details This function reads the current state of all 16 pins of the specified
 *          GPIO port and returns it as a 16-bit value.
 *
 * @param[in] pGPIOx Pointer to GPIO peripheral base address (GPIOA, GPIOB, etc.)
 *
 * @return uint16_t 16-bit value representing the state of all port pins
 *                  (bit 0 = pin 0, bit 1 = pin 1, ... bit 15 = pin 15)
 *
 * @code
 * // Read entire GPIOA port
 * uint16_t port_state = GPIO_ReadFromInputPort(GPIOA);
 * // Check if pin 3 is high
 * if(port_state & (1 << 3)) {
 *     // Pin 3 is high
 * }
 * @endcode
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);

/**
 * @brief Write a value to a specific GPIO output pin
 * @details This function sets the output state of the specified GPIO pin.
 *          The pin should be configured in output mode before calling this function.
 *
 * @param[in] pGPIOx Pointer to GPIO peripheral base address (GPIOA, GPIOB, etc.)
 * @param[in] PinNumber Pin number to write (0-15)
 * @param[in] Value Value to write (GPIO_PIN_SET for HIGH, GPIO_PIN_RESET for LOW)
 *
 * @return None
 *
 * @note Pin should be configured in output mode
 *
 * @code
 * // Set GPIOA pin 5 to HIGH
 * GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, GPIO_PIN_SET);
 * // Set GPIOA pin 5 to LOW
 * GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, GPIO_PIN_RESET);
 * @endcode
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);

/**
 * @brief Write a 16-bit value to entire GPIO port
 * @details This function sets the output state of all 16 pins of the specified
 *          GPIO port simultaneously using a 16-bit value.
 *
 * @param[in] pGPIOx Pointer to GPIO peripheral base address (GPIOA, GPIOB, etc.)
 * @param[in] Value 16-bit value to write to the port
 *                  (bit 0 = pin 0, bit 1 = pin 1, ... bit 15 = pin 15)
 *
 * @return None
 *
 * @note Only affects pins configured as outputs
 * @warning This will modify all output pins of the port simultaneously
 *
 * @code
 * // Set pins 0, 2, 4 to HIGH and others to LOW
 * GPIO_WriteToOutputPort(GPIOA, 0x0015);  // Binary: 0000000000010101
 * @endcode
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);

/**
 * @brief Toggle the state of a specific GPIO output pin
 * @details This function inverts the current output state of the specified GPIO pin.
 *          If the pin is currently HIGH, it will be set to LOW and vice versa.
 *
 * @param[in] pGPIOx Pointer to GPIO peripheral base address (GPIOA, GPIOB, etc.)
 * @param[in] PinNumber Pin number to toggle (0-15)
 *
 * @return None
 *
 * @note Pin should be configured in output mode
 * @note This operation is atomic and more efficient than read-modify-write
 *
 * @code
 * // Toggle GPIOA pin 13 (typically connected to LED)
 * GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_13);
 * @endcode
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/*
 * =============================================================================
 * INTERRUPT CONFIGURATION AND HANDLING
 * =============================================================================
 */

/**
 * @brief Configure GPIO interrupt in NVIC
 * @details This function enables or disables the specified GPIO interrupt line
 *          in the Nested Vectored Interrupt Controller (NVIC).
 *
 * @param[in] IRQNumber IRQ number of the GPIO interrupt line (EXTI0_IRQn, EXTI1_IRQn, etc.)
 * @param[in] EnorDi Enable (ENABLE) or Disable (DISABLE) the interrupt
 *
 * @return None
 *
 * @note The corresponding EXTI line must also be configured
 * @note IRQ numbers are defined in the CMSIS header files
 *
 * @code
 * // Enable EXTI0 interrupt (for GPIO pins connected to EXTI0)
 * GPIO_IRQInterruptConfig(EXTI0_IRQn, ENABLE);
 * @endcode
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber,  uint8_t EnorDi);

/**
 * @brief Set the priority of GPIO interrupt
 * @details This function configures the priority level of the specified GPIO
 *          interrupt in the NVIC. Lower values indicate higher priority.
 *
 * @param[in] IRQNumber IRQ number of the GPIO interrupt line
 * @param[in] IRQPriority Priority level (0-15, where 0 is highest priority)
 *
 * @return None
 *
 * @note Priority values depend on the number of priority bits implemented
 * @note For STM32F446xx, typically 4 bits are used (16 priority levels)
 *
 * @code
 * // Set EXTI0 interrupt priority to level 5
 * GPIO_IRQPriorityConfig(EXTI0_IRQn, 5);
 * @endcode
 */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);

/**
 * @brief Handle GPIO interrupt service routine
 * @details This function should be called from the interrupt service routine
 *          to clear the pending interrupt flag for the specified pin.
 *
 * @param[in] PinNumber Pin number that triggered the interrupt (0-15)
 *
 * @return None
 *
 * @note This function must be called to clear the interrupt flag
 * @warning Failing to clear the flag will cause continuous interrupts
 *
 * @code
 * // In the EXTI0_IRQHandler function
 * void EXTI0_IRQHandler(void) {
 *     GPIO_IRQHandling(GPIO_PIN_NO_0);
 *     // User interrupt handling code here
 * }
 * @endcode
 */
void GPIO_IRQHandling(uint8_t PinNumber);

/** @} */ // End of GPIO_Driver_APIs group

#endif /* INC_STM32F446XX_GPIO_DRIVER_H_ */

/**
 * @page gpio_usage GPIO Driver Usage Examples
 *
 * @section basic_io Basic Input/Output Operations
 *
 * @subsection led_control LED Control Example
 * @code
 * // Initialize GPIO for LED control
 * GPIO_Handle_t gpio_led;
 *
 * // Enable GPIO clock
 * GPIO_PeriClockControl(GPIOA, ENABLE);
 *
 * // Configure LED pin
 * gpio_led.pGPIOx = GPIOA;
 * gpio_led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
 * gpio_led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
 * gpio_led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
 * gpio_led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
 * gpio_led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
 *
 * GPIO_Init(&gpio_led);
 *
 * // Control LED
 * GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, GPIO_PIN_SET);   // Turn ON
 * GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, GPIO_PIN_RESET); // Turn OFF
 * GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);                  // Toggle
 * @endcode
 *
 * @subsection button_input Button Input Example
 * @code
 * // Initialize GPIO for button input
 * GPIO_Handle_t gpio_btn;
 *
 * // Enable GPIO clock
 * GPIO_PeriClockControl(GPIOC, ENABLE);
 *
 * // Configure button pin
 * gpio_btn.pGPIOx = GPIOC;
 * gpio_btn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
 * gpio_btn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
 * gpio_btn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
 * gpio_btn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
 *
 * GPIO_Init(&gpio_btn);
 *
 * // Read button state
 * if(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13) == GPIO_PIN_RESET) {
 *     // Button pressed (assuming active low)
 * }
 * @endcode
 *
 * @section interrupt_example Interrupt Example
 * @code
 * // Configure GPIO interrupt
 * GPIO_Handle_t gpio_int;
 *
 * // Enable GPIO clock
 * GPIO_PeriClockControl(GPIOA, ENABLE);
 *
 * // Configure interrupt pin
 * gpio_int.pGPIOx = GPIOA;
 * gpio_int.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
 * gpio_int.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;  // Falling edge trigger
 * gpio_int.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
 * gpio_int.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
 *
 * GPIO_Init(&gpio_int);
 *
 * // Configure NVIC
 * GPIO_IRQPriorityConfig(EXTI0_IRQn, 15);
 * GPIO_IRQInterruptConfig(EXTI0_IRQn, ENABLE);
 *
 * // Interrupt handler
 * void EXTI0_IRQHandler(void) {
 *     GPIO_IRQHandling(GPIO_PIN_NO_0);
 *     // User code here
 * }
 * @endcode
 */
