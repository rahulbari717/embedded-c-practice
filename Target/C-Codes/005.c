/*
Q) WAP to clear (make bit state to 0) 4th, 5th, 6th bit
position of a given number and print the result.
*/

/*

    7 6 5 4 3 2 1 0
    1 0 0 0 1 1 1 1  mask value in hex is 0x8F

*/

#include<stdio.h>
#include <stdint.h>

int main(){
    int32_t num ;

    printf("Enter a number: ");
    scanf("%d", &num);

    num = num & 0x8F;
    printf("The number after resetting 4th 5th 6th bit position is %d\n", num);

    return 0;
}