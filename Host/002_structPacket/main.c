/*
 * main.c
 *
 *  Created on: Mar 11, 2025
 *      Author: Rahul B.
 */

#include <stdio.h>
#include <stdint.h>

struct Packet {
	uint8_t crc;
	uint8_t status;
	uint16_t payload;
	uint8_t bat;
	uint8_t sensor;
	uint8_t longAddr;
	uint8_t shortAddr;
	uint8_t addrMode;

};

int main(){
	uint32_t packetValue;
	printf("Enter the 32 bit packet value : ");
	scanf("%u", &packetValue);

	struct Packet packet;

	return 0;
}

