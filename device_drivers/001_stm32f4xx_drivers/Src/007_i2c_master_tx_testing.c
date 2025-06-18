/*
 * 007_i2c_master_tx_testing.c
 *
 * Created on: Jun 18, 2025
 * Author: Rahul B. 
 *
 * @brief : STM32F446xx I2C Master Transmission Test Application
 * 			This file contains a test application for verifying I2C master transmission
 * 			functionality on the STM32F446xx microcontroller. It demonstrates the usage
 * 			of I2C peripheral APIs for sending data to an I2C slave device.
 */

#include <string.h>
#include "stm32f446xx.h"

#define MY_ADDR         0x61
#define SLAVE_ADDR      0x68

I2C_Handle_t I2C1Handle;

void delay(void)
{
	for(uint32_t i = 0; i < 500000 / 2 ; i++);
}

/*
 * PB6 -> SCL
 * PB9 -> SDA
*/

void I2C1_GPIOInits(void) 
{
    GPIO_Handle_t I2CPins,Gpio_Button;
    // I2c pins configuration
    I2CPins.pGPIOx = GPIOB;
    I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
    I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
    I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    
    //SCL
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
    GPIO_Init(&I2CPins);
    
    //SDA
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
    GPIO_Init(&I2CPins);

    // Button Configurations
    Gpio_Button.pGPIOx = GPIOC;
    Gpio_Button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    Gpio_Button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;  
    Gpio_Button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    Gpio_Button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;   // Enable pull-up resistor

    GPIO_PeriClockControl(GPIOC, ENABLE);
    GPIO_Init(&Gpio_Button);
}

void I2C1_Inits(void)
{
    
    I2C1Handle.pI2Cx = I2C1;
    I2C1Handle.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
    I2C1Handle.I2C_Config.I2C_DeviceAddress = MY_ADDR;
    I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
    I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;
    
    I2C_Init(&I2C1Handle);
}

int main(void)
{
    uint8_t some_data[] = "Hello World\r\n";
    
    //Initialize GPIO pins for I2C1
    I2C1_GPIOInits();
    
    //Initialize I2C1 peripheral
    I2C1_Inits();
    
    //Enable I2C1 peripheral
    I2C_PeripheralControl(I2C1, ENABLE);
    
    //Enable ACKing
    I2C_ManageAcking(I2C1, I2C_ACK_ENABLE);
    

    while(1){
    	// wait for button press
    	while( GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13) );
    	
    	//delay for button debouncing
    	delay();
        GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, GPIO_PIN_SET);  // Turn on LED (for example)

		//Send data to slave
		I2C_MasterSendData(&I2C1Handle, some_data, strlen((char*)some_data), SLAVE_ADDR, 0);
    }
    
    return 0;
}
