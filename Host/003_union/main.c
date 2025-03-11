/*
 * main.c
 *
 *  Created on: Mar 11, 2025
 *      Author: Rahul B.
 */

#include <stdio.h>
#include <stdint.h>

union Address{
	uint16_t shortAddr;
	uint32_t longAddr;
};

int main(){
	union Address addr;
	addr.shortAddr = 0xABCD;
	addr.longAddr = 0xEEEEFFFF;

	printf("Short address is ==> %#X \n",addr.shortAddr);
	printf("Long address is ==> %#X \n",addr.longAddr);

	return 0;
}

