#include <stdio.h>

float add(float a, float b) {    // Changed from int to float
    return a + b;
}

float subtract(float a, float b) {  // Changed from int to float
    return a - b;
}

float multiply(float a, float b) {  // Changed from int to float
    return a * b;
}

float divide(float a, float b) {    // Changed from int to float
    if (b != 0) {
        return a / b;               // No need to cast anymore
    }
    return 0;
}