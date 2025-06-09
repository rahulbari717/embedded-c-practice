#include <stdio.h>
#include <stdint.h>

// Clean way with struct:
typedef struct  {
    int id;
    float temperature;
    int status;
}Sensor_t;

bool LED1  = false;  // (LED1 is off)


int main(){

    Sensor_t Gas_sensor1 = {.id = 1, .temperature = 20.5, .status = 1};

    struct Sensor* sensor_ptr = &gas_sensor;  // Point to the sensor

    // Two ways to access data:
    my_sensor.temperature = 25.0;        // Direct access
    sensor_ptr->temperature = 25.0;

    printf("Sensor ID: %d\n", sensor_ptr->id);
    printf("Sensor Temp: %.2f\n", sensor_ptr->temperature);
    printf("Sensor Status: %d\n", sensor_ptr->status);















































    // char * name_ptr = "RAHUL";
    // char name_array[] = "rahul";

    // printf("name_ptr =  %s, name_ptr = %p, * name_ptr = %c \n ", name_ptr, name_ptr, *name_ptr);

    // printf("name_array =  %s, name_array = %p, * name_array = %c \n ", name_array, name_array, *name_array);














/* 
    char c = 'A';
    char *c_ptr = &c;

    printf("Value store at c = %c \n", c);
    printf("Address of c (&c) = %p \n", &c);

    printf("Value store at c = %d \n", c);

    printf("Value store at *c_ptr = %c \n", *c_ptr);
    printf("Address of c_ptr (&c_ptr) = %p \n", &c_ptr); */


    // int i = 0xAA;
    // char c = 3;

    // int x;
    // char *cptr;

    printf("\n");
    
    // printf("&c = %p \n", &c);
    // printf("(garbage) x = %d \n",x);
    
    // printf("(garbage) cptr = %p \n", cptr); 
    // printf("(garbage) cptr = 0x%llx \n\n", (long long unsigned int) cptr);

    /* 1. Used of & before the variable in non pointer assingment */

    // x = i & c;          // i = 0xAA, c = 3  ; 1010 1010 & 0000 0011 = 0000 0010 = 2
    // printf("x = (i&c) ==> %d \n", x);

    /* 2. Used of & before the variable in non-pointer assingment */
    // cptr = &c;          // address of c is stored in cptr
    // x = i & cptr;       // 
    // printf("x = i& &c; ==> %d \n\n", x);
    
    // x = i & &c; 
    // printf("x = i& &c; ==> %d \n\n", x);

    // i = 0xFF;
    // x = i & (int) (&c);
    // printf("&c %p \n==> ", &c); 
    // printf("x = i & &c; ==> %d \n\n", x);


    return 0;
}