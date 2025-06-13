/*
 * 006spi_tx_testing.c
 *
 *  Created on: Jun 13, 2025
 *      Author: Rahul B.
 */
#include <string.h>
#include "stm32f446xx.h"

/*
 * SPI2 GPIO Pin Configuration:
 * -----------------------------------------
 * PB12 -> SPI2_NSS   (AF5)
 * PB13 -> SPI2_SCLK  (AF5)
 * PB14 -> SPI2_MISO  (AF5)
 * PB15 -> SPI2_MOSI  (AF5)
 *
 * GPIO Alternate Function Mode: AF5 (SPI2)
 */

void SPI2_GPIOs(void)
{
    GPIO_Handle_t SPIPins;

    SPIPins.pGPIOx = GPIOB;
    SPIPins.GPIO_PinConfig.GPIO_PinMode     = GPIO_MODE_ALTFN;
    SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5; // AF5 for SPI2
    SPIPins.GPIO_PinConfig.GPIO_PinOPType   = GPIO_OP_TYPE_PP;
    SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed    = GPIO_SPEED_FAST;

    // SPI2_NSS -> PB12
    //SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    //GPIO_Init(&SPIPins);

    // SPI2_SCLK -> PB13
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    GPIO_Init(&SPIPins);

    // SPI2_MISO -> PB14
    //SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
    //GPIO_Init(&SPIPins);

    // SPI2_MOSI -> PB15
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
    GPIO_Init(&SPIPins);
}

void SPI2_Inits(void)
{
    SPI_Handle_t SPI2handle;

    SPI2handle.pSPIx = SPI2;

    SPI2handle.SPIConfig.SPI_DeviceMode   = SPI_DEVICE_MODE_MASTER;
    SPI2handle.SPIConfig.SPI_BusConfig    = SPI_BUS_CONFIG_FD;
    SPI2handle.SPIConfig.SPI_SclkSpeed    = SPI_SCLK_SPEED_DIV32;
    SPI2handle.SPIConfig.SPI_DFF          = SPI_DFF_8BITS;
    SPI2handle.SPIConfig.SPI_CPOL         = SPI_CPOL_LOW;
    SPI2handle.SPIConfig.SPI_CPHA         = SPI_CPHA_LOW;
    SPI2handle.SPIConfig.SPI_SSM          = SPI_SSM_EN;  // Using software slave management

    SPI_Init(&SPI2handle);
}

int main(void)
{
    char user_data[] = "Rahul Bari";  // ✅ Proper null-terminated string
    uint8_t dataLen = strlen(user_data);  // ✅ This is OK because user_data is a string

    SPI2_GPIOs();
    SPI2_Inits();

    SPI_SSIConfig(SPI2, ENABLE);
    SPI_PeripheralControl(SPI2, ENABLE);
    // Add delay to ensure SPI is ready
    for(volatile int i = 0; i < 1000; i++);
    // SPI_SendData(SPI2, &dataLen, 1);  // ✅ Send 1-byte length info

    SPI_SendData(SPI2, (uint8_t*)user_data, dataLen);  // ✅ Send string data

    // ✅ Wait for SPI to not be busy
    while(SPI_GetFlagStatus(SPI2, SPI_BSY_FLAG));

    SPI_PeripheralControl(SPI2, DISABLE);

    while(1);
    return 0;
}
