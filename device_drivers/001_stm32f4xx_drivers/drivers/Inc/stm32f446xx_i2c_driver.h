/**
 * @file    stm32f446xx_i2c_driver.h
 * @brief   I2C driver header file for STM32F446xx microcontroller
 * @details This file contains all the function prototypes, macros, and data structures
 *          required for I2C (Inter-Integrated Circuit) operations on STM32F446xx.
 *          It provides a hardware abstraction layer for I2C configuration and communication.
 *
 * @author Rahul B.
 * @date   Jun 17, 2025
 * @version 1.0
 *
 * @note    Designed specifically for STM32F446xx series microcontrollers
 * @warning Ensure proper clock configuration before using I2C functions
 */

#ifndef INC_STM32F446XX_I2C_DRIVER_H_
#define INC_STM32F446XX_I2C_DRIVER_H_

#include "stm32f446xx.h"

/**
 * @brief I2C Configuration Structure
 * @details This structure contains all configurable parameters for the I2C peripheral.
 *          It is used to initialize and configure the I2C peripheral settings.
 */
typedef struct
{
    uint32_t I2C_SCLSpeed;       /**< SCL clock speed (Standard/Fast modes) @ref I2C_SCL_SPEED */
    uint8_t  I2C_DeviceAddress;  /**< Own address of the device */
    uint8_t  I2C_ACKControl;     /**< Enable or disable ACKing for received bytes @ref I2C_ACK */
    uint8_t  I2C_FMDutyCycle;    /**< Fast mode duty cycle setting @ref I2C_FM_DUTY */
} I2C_Config_t;

/**
 * @brief I2C Handle Structure
 * @details This structure holds the peripheral base address and the I2C
 *          configuration data for individual I2C instances.
 */
typedef struct
{
    I2C_RegDef_t *pI2Cx;         /**< Pointer to I2C peripheral base address */
    I2C_Config_t I2C_Config;     /**< I2C configuration settings */
    uint8_t *pTxBuffer;          /**< Pointer to transmission buffer */
    uint8_t *pRxBuffer;          /**< Pointer to reception buffer */
    uint32_t TxLen;              /**< Transmission length */
    uint32_t RxLen;              /**< Reception length */
    uint8_t TxRxState;          /**< Current communication state */
} I2C_Handle_t;

/**
 * @defgroup I2C_SCL_SPEED I2C SCL Clock Speed
 * @{
 */
#define I2C_SCL_SPEED_SM      100000  /**< Standard mode 100kHz */
#define I2C_SCL_SPEED_FM2K    200000  /**< Fast mode 200kHz */
#define I2C_SCL_SPEED_FM4K    400000  /**< Fast mode 400kHz */
/** @} */

/**
 * @defgroup I2C_ACK ACK Control
 * @{
 */
#define I2C_ACK_ENABLE        1       /**< Enable ACK */
#define I2C_ACK_DISABLE       0       /**< Disable ACK */
/** @} */

/**
 * @defgroup I2C_FM_DUTY Fast Mode Duty Cycle
 * @{
 */
#define I2C_FM_DUTY_2         0       /**< Duty cycle 2 */
#define I2C_FM_DUTY_16_9      1       /**< Duty cycle 16/9 */
/** @} */


/**
 * @defgroup I2C_STATUS I2C Status Flags
 * @{
 */
#define I2C_FLAG_SB           (1 << I2C_SR1_SB)        /**< Start bit generated */
#define I2C_FLAG_ADDR        (1 << I2C_SR1_ADDR)      /**< Address sent/matched */
#define I2C_FLAG_BTF         (1 << I2C_SR1_BTF)       /**< Byte transfer finished */
#define I2C_FLAG_STOPF       (1 << I2C_SR1_STOPF)     /**< Stop detection */
#define I2C_FLAG_RXNE        (1 << I2C_SR1_RXNE)      /**< Data register not empty */
#define I2C_FLAG_TXE         (1 << I2C_SR1_TXE)       /**< Data register empty */
#define I2C_FLAG_BERR        (1 << I2C_SR1_BERR)      /**< Bus error */
#define I2C_FLAG_ARLO        (1 << I2C_SR1_ARLO)      /**< Arbitration lost */
#define I2C_FLAG_AF          (1 << I2C_SR1_AF)        /**< Acknowledge failure */
#define I2C_FLAG_OVR         (1 << I2C_SR1_OVR)       /**< Overrun/underrun */
#define I2C_FLAG_TIMEOUT     (1 << I2C_SR1_TIMEOUT)   /**< Timeout/Tlow error */


/** @} */

/*******************************************************************************
 *          APIs supported by this driver
 *          For more information about the APIs check the function definitions
 *******************************************************************************/

/*
 * Peripheral Clock Control
*/
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);

/*
 * Init & De-init
*/
void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);

/*
 * Data Send & Receive (Blocking)
*/

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,
                       uint8_t *pTxBuffer, uint32_t Len,
                       uint8_t SlaveAddr, uint8_t RepeatedStart);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle,
                          uint8_t *pRxBuffer, uint32_t Len,
                          uint8_t SlaveAddr, uint8_t RepeatedStart);

/*
 * IRQ Configuration & ISR Handling
*/
                         
// 
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnOrDi);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);

void I2C_EV_IRQHandling(I2C_Handle_t *pI2CHandle);
void I2C_ER_IRQHandling(I2C_Handle_t *pI2CHandle);

/*
 * Other Peripheral Control APIs
*/
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);

void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);
void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);
void I2C_SlaveEnableDisableCallbackEvents(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);


#endif /* INC_STM32F446XX_I2C_DRIVER_H_ */
