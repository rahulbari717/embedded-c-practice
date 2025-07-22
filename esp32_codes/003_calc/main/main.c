
#include "calc.h"

void app_main(){    // Changed from int to void

    float a = 10.0; 
    float b = 5.15; 

    float result = add(a, b);

    printf("Addition: %f\n", result);
    result = subtract(a, b);
    printf("Subtraction: %f\n", result);
    result = multiply(a, b);
    printf("Multiplication: %f\n", result);
    result = divide(a, b);
    printf("Division: %f\n", result);

}