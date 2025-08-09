/*
 * it.c
 *
 *  Created on: Mar 25, 2025
 *      Author: Rahul B.
 */
#include "main.h"

extern void HT_Complete_callback(void);
extern void FT_Complete_callback(void);
extern void TE_error_callback(void);
extern void DME_error_callback(void);
extern void FE_error_callback(void);

#define is_it_HT() 	DMA1->HISR & ( 1 << 20)
#define is_it_FT() 	DMA1->HISR & ( 1 << 21)
#define is_it_TE() 	DMA1->HISR & ( 1 << 19)
#define is_it_FE() 	DMA1->HISR & ( 1 << 16)
#define is_it_DME() DMA1->HISR & ( 1 << 18)


void clear_exti_pending_bit(void)
{
	EXTI_TypeDef *pEXTI;
	pEXTI = EXTI;

	if( (EXTI->PR & (1 << 13) )  )
	{
		//Clears the Pending bit
		EXTI->PR |= (1 << 13);
	}


}



