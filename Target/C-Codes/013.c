#include <stdio.h>

void func1(void){
    printf("function 1 () \n");
}

void func2(int a){
    printf("function 2 () a = %d \n", a);
}

typedef void (*funcptr)();
typedef void (*funcptr1)(int);

int main(){

    funcptr pf; 
    funcptr1 pf1;

    pf = func1;
    pf();
    
    pf1 = func2;
    pf1(10);

    return 0;   
}