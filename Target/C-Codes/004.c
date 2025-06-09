/*
Q) WAP to set (make bit state to 1) 4th and 7th bit
position of a given number and print the result.
*/

/*

    7 6 5 4 3 2 1 0
    1 0 0 1 0 0 0 0 mask value in hex is 0x90



*/

#include<stdio.h>
#include <stdint.h>

int main(){
    int32_t num ;

    printf("Enter a number: ");
    scanf("%d", &num);

    num = num | 0x90;
    printf("The number after setting 4th and 7th bit is %d\n", num);


    return 0;
}