/*
Q) Write a program which takes 2 integers from the user, 
   computes bitwise &, |, ^, ~ and prints the result.

*/

#include <stdio.h>
#include <stdint.h>

int main(){

int32_t a, b; 

printf("Enter 2 no. for bitwise opration \n");
scanf("%d %d", &a, &b);

printf ("YOu enter no. are ==> %d %d \n", a, b);   

printf("& bitwise opration %d \n", (a&b));
printf("| bitwise opration %d \n", (a|b));
printf("^ bitwise opration %d \n", (a^b));
printf("~ bitwise opration %d \n", (~b));

return 0;

}
