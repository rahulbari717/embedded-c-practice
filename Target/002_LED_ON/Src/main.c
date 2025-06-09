
#include <stdio.h>

#define RCC_AHB1ENR   (*((volatile unsigned int*)0x40023830))
#define GPIOA_MODER   (*((volatile unsigned int*)0x40020000))
#define GPIOA_ODR     (*((volatile unsigned int*)0x40020014))

#define GPIOA_EN      (1 << 0)     // Enable clock to GPIOA
#define PA5_OUTPUT    (1 << 10)    // MODER5[1:0] = 01 for output
#define PA5_MASK      (3 << 10)    // Mask for bits 11:10

void delay(volatile unsigned int t) {
    while(t--); // crude delay
}

int main(void)
{
	printf("Start the code ! \n");

	// 1. Enable clock to GPIOA
	    RCC_AHB1ENR |= GPIOA_EN;

	    // 2. Set PA5 as output
	    GPIOA_MODER &= ~PA5_MASK;   // Clear bits 11:10
	    GPIOA_MODER |= (1 << 10);   // Set bit 10 to make PA5 output

	    // 3. Toggle LED
	    while(1)
	        {
	            // Turn ON LED
	            GPIOA_ODR |= (1 << 5);
	        	printf("LED ON ! \n");
	            delay(50000000);

	            // Turn OFF LED
	            GPIOA_ODR &= ~(1 << 5);
	        	printf("LED OFF ! \n");
	            delay(50000000);
	        }





    /* Loop forever */
	for(;;);
}
