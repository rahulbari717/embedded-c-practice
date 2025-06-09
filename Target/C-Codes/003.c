/*
Q) Write a program to find out whether a user entered number is even or odd.
    print an appropriate message to the console.

*/

#include<stdio.h>
#include <stdint.h>

int main(){

    int32_t num = 0;

    printf("Enter a number: ");
    scanf("%d", &num);
  
    if(num & 1)
    {
        printf("The no. you enter %d is ==> Odd\n", num); 
    }
    else{
        printf("The no. you enter %d is ==> Even\n", num); 
    }
    return 0;   
}