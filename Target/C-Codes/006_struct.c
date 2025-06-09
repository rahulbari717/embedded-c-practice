#include <stdio.h>  
#include <stdint.h> 

struct car{
    uint32_t carNumber;
    uint32_t carPrice;
    uint16_t carMaxSpeed;
    float carWeight;

}; 


typedef struct 
{
    uint32_t BikeNumber;
    uint32_t BikePrice;

}Bike_t;

int main(){

    struct car carBMW = {.carWeight = 60, .carMaxSpeed = 200, .carNumber = 5, .carPrice = 5000 }; 

    printf("Details of car BMW is as follows "); 
    printf("Car Number is %d\n", carBMW.carNumber);
    printf("Car Price is %d\n", carBMW.carPrice);
    printf("Car Max Speed is %d\n", carBMW.carMaxSpeed);
    printf("Car Weight is %f\n", carBMW.carWeight);

    printf("Size of struct car is %ld\n", sizeof(struct car));


    return 0;
}