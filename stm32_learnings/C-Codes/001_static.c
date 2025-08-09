#include <stdio.h>

/* this is function prototype*/
void fun1(void);

int main(){
	fun1(); 
	fun1();
	fun1();
	fun1();
	
	return 0;
} 


void fun1(void){
	static int count = 0;
	count = count+1; 
	printf("This function executed %d times(s) \n", count); 
}
