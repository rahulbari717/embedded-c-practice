#include "stm32f446xx_spi_driver.h"
#include "stm32f446xx.h"

/******************************************************************************
*@fn      - SPI_PeripheralControl

*@brief   - This function enables or disables the specified SPI peripheral

*@param[in]  - EnOrDi: ENABLE or DISABLE macro
*@param[in]  - SPI_Periph: SPI peripheral number

*@return    - None

*@note      - None
********************************************************************************/


void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDI)
{
    if(EnorDI == ENABLE)
    {
        if(pSPIx == SPI1)
        {
            SPI1_PCLK_EN();
        }
        else if(pSPIx == SPI2)
        {
            SPI2_PCLK_EN();
        }
        else if(pSPIx == SPI3)
        {
            SPI3_PCLK_EN();
        }
        
    }
    else
    {

    }
}

void SPI_Init (SPI_Handle_t *pSPIHandle)
{
    //1. Configure the SPCR register
    //2. Configure the SPDR register
    //3. Enable the SPI in the SPI_CR1 register
}

