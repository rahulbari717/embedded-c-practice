/*
 * stm32f446xx_i2c_driver.h
 *
 *  Created on: Apr 4, 2025
 *      Author: Rahul Bari
 */

#ifndef INC_STM32F446XX_I2C_DRIVER_H_
#define INC_STM32F446XX_I2C_DRIVER_H_

#include "stm32f446xx.h"

/*
 * Configuration structure for I2Cx peripheral
 * This structure holds various configuration settings for the I2C peripheral
 * including speed mode, device address, ACK control, and clock speed
*/
typedef struct
{
    uint32_t I2C_SCLSpeed;          /* Configures the serial clock speed */
    uint8_t  I2C_DeviceAddress;     /* Slave/Device address when in slave mode */
    uint8_t  I2C_AckControl;        /* Enables or disables ACK bit control */
    uint16_t I2C_FMDutyCycle;       /* Duty cycle in fast mode */
}I2C_Config_t;

/*
 * Handle structure for I2Cx peripheral
 * This structure holds the configuration settings and state information
 * for an I2C peripheral instance, including base address, configuration
 * and current transfer state
*/
typedef struct
{
    I2C_RegDef_t *pI2Cx;           /* Base address of I2Cx peripheral */
    I2C_Config_t I2C_Config;       /* I2C peripheral configuration settings */

}I2C_Handle_t;


/*
 * @defgroup I2C_Speed_Modes
*/
#define I2C_SCL_SPEED_SM     100000
#define I2C_SCL_SPEED_FM2K   200000
#define I2C_SCL_SPEED_FM4K   4000000

/*
 * @defgroup I2C_AckControl
*/
#define I2C_ACK_ENABLE        1
#define I2C_ACK_DISABLE       0

/*
 * @defgroup I2C_FMDutyCycle
*/
#define I2C_FM_DUTY_2        0
#define I2C_FM_DUTY_16_9     1

/*
 * @defgroup I2C_Status_Flags
*/
#define I2C_FLAG_TXE         (1 << I2C_SR1_TXE)
#define I2C_FLAG_RXNE        (1 << I2C_SR1_RXNE)
#define I2C_FLAG_SB          (1 << I2C_SR1_SB)
#define I2C_FLAG_ADDR        (1 << I2C_SR1_ADDR)
#define I2C_FLAG_BTF         (1 << I2C_SR1_BTF)
#define I2C_FLAG_STOPF       (1 << I2C_SR1_STOPF)
#define I2C_FLAG_BERR        (1 << I2C_SR1_BERR)
#define I2C_FLAG_ARLO        (1 << I2C_SR1_ARLO)
#define I2C_FLAG_AF          (1 << I2C_SR1_AF)
#define I2C_FLAG_OVR         (1 << I2C_SR1_OVR)
#define I2C_FLAG_TIMEOUT     (1 << I2C_SR1_TIMEOUT)

/*
 * @defgroup I2C_Application_States
*/
#define I2C_READY           0
#define I2C_BUSY_IN_RX      1
#define I2C_BUSY_IN_TX      2

/*
 * Peripheral Clock setup
 */
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);

/*
 * Init and De-init
 */
void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);

/*
 * Data Send and Receive
 */
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);
uint8_t I2C_MasterSendDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);
uint8_t I2C_MasterReceiveDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);

void I2C_SlaveSendData(I2C_RegDef_t *pI2C, uint8_t data);
uint8_t I2C_SlaveReceiveData(I2C_RegDef_t *pI2C);

/*
 * IRQ Configuration and ISR handling
 */
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void I2C_EV_IRQHandling(I2C_Handle_t *pI2CHandle);
void I2C_ER_IRQHandling(I2C_Handle_t *pI2CHandle);

/*
 * Other Peripheral Control APIs
 */
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName);
void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);
void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);

/*
 * Application callback
 */
void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEv);



#endif /* INC_STM32F446XX_I2C_DRIVER_H_ */
