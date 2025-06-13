/*
 * stm32f446xx_spi_driver.h
 *
 *  Created on: Jun 13, 2025
 *      Author: Rahul B.
 */

#ifndef INC_STM32F446XX_SPI_DRIVER_H_
#define INC_STM32F446XX_SPI_DRIVER_H_

#include "stm32f446xx.h"
/*
 * 	Configuration structure for SPIx peripheral
 *
 * */
typedef struct
{
   uint8_t SPI_DeviceMode;          // Master or Slave mode			@SPI_DeviceMode
   uint8_t SPI_BusConfig;           // Full duplex, Half duplex, or Simplex
   uint8_t SPI_SclkSpeed;           // Serial clock speed
   uint8_t SPI_DFF;                 // Data frame format (8-bit or 16-bit)
   uint8_t SPI_CPOL;                // Clock polarity
   uint8_t SPI_CPHA;                // Clock phase
   uint8_t SPI_SSM;                 // Software slave management
} SPI_Config_t;

/*
* Handle Structure for SPIx peripheral
*/
typedef struct
{
   SPI_RegDef_t *pSPIx;             // Base address of SPIx peripheral
   SPI_Config_t SPIConfig;          // SPI configuration settings
//   uint8_t *pTxBuffer;              // Pointer to Tx buffer
//   uint8_t *pRxBuffer;              // Pointer to Rx buffer
//   uint32_t TxLen;                  // Length of Tx data
//   uint32_t RxLen;                  // Length of Rx data
//   uint8_t TxState;                 // Tx state
//   uint8_t RxState;                 // Rx state
} SPI_Handle_t;

/*
 * @SPI_DeviceMode
 * */

#define SPI_DEVICE_MODE_MASTER      1
#define SPI_DEVICE_MODE_SLAVE          0
/*
* @SPI bus configuration
*/
#define SPI_BUS_CONFIG_FD           						1   // Full duplex
#define SPI_BUS_CONFIG_HD           						2   // Half duplex
#define SPI_BUS_CONFIG_SIMPLEX_RX   				3   // Simplex RX only
/*
* SPI serial clock speed
*/
#define SPI_SCLK_SPEED_DIV2         					0   // fPCLK/2
#define SPI_SCLK_SPEED_DIV4         					1   // fPCLK/4
#define SPI_SCLK_SPEED_DIV8         					2   // fPCLK/8
#define SPI_SCLK_SPEED_DIV16        					3   // fPCLK/16
#define SPI_SCLK_SPEED_DIV32        					4   // fPCLK/32
#define SPI_SCLK_SPEED_DIV64        					5   // fPCLK/64
#define SPI_SCLK_SPEED_DIV128      					6   // fPCLK/128
#define SPI_SCLK_SPEED_DIV256       					7   // fPCLK/256
/*
* SPI data frame format
*/
#define SPI_DFF_8BITS               						0
#define SPI_DFF_16BITS              						1
/*
* SPI clock polarity
*/
#define SPI_CPOL_HIGH               1
#define SPI_CPOL_LOW                0
/*
* SPI clock phase
*/
#define SPI_CPHA_HIGH               1
#define SPI_CPHA_LOW                0
/*
* SPI software slave management
*/
#define SPI_SSM_EN                    1   // Software slave management enabled
#define SPI_SSM_DI               		0   // Software slave management disabled
/*
* SPI application states
*/
#define SPI_READY                   0
#define SPI_BUSY_IN_RX              1
#define SPI_BUSY_IN_TX              2
/*
* SPI status flags
*/
#define SPI_TXE_FLAG                (1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG               (1 << SPI_SR_RXNE)
#define SPI_BSY_FLAG                (1 << SPI_SR_BSY)
/*
* SPI related status flags definitions
*/
#define SPI_SR_TXE                  1
#define SPI_SR_RXNE                 0
#define SPI_SR_BSY                  7


/*
* APIs supported by this driver
*/
/*
* Peripheral Clock setup
*/
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
/*
* Init and De-init
*/
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);
/*
* Data Send and Receive
*/
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);
//
///*
// * Data Send and Receive with Interrupt
// */
//uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len);
//uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len);

/*
 * IRQ Configuration and ISR handling
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);
//
/*
 * Other Peripheral Control APIs
 */
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName);
//void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx);
//void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle);
//void SPI_CloseReception(SPI_Handle_t *pSPIHandle);

/*
 * Application callback
 */
//void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEv);

#endif /* INC_STM32F446XX_SPI_DRIVER_H_ */
