#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>  // Needed for bool type

// Struct definition to hold sensor data
typedef struct {
    int id;
    float temperature;
    int status;
} Sensor_t;

// Simulated LED variable (false = OFF, true = ON)
bool LED1 = false;

int main() {
    // Create and initialize a sensor struct instance
    Sensor_t Gas_sensor1 = {.id = 1, .temperature = 20.5, .status = 0}; // default values. 

    // Create a pointer to the sensor struct
    Sensor_t* sensor_ptr = &Gas_sensor1;

    // Debug: Print initial values
    printf("Initial Sensor ID: %d\n", sensor_ptr->id);
    printf("Initial Sensor Temp: %.2f\n", sensor_ptr->temperature);
    printf("Initial Sensor Status: %d\n\n", sensor_ptr->status);

    // Update temperature value (simulate sensor reading)
    sensor_ptr->temperature = 25.0;

    // Check sensor ID and temperature
    if (sensor_ptr->id == 1 && sensor_ptr->temperature >= 25.0) {
        sensor_ptr->status = 1;  // Set status to active
        LED1 = true;             // Turn on the LED (simulated)
        printf("Condition met: ID = 1 and Temp >= 25.0\n");
        printf("Sensor activated. LED1 is ON.\n");
    } else {
        sensor_ptr->status = 0;  // Set status to inactive
        LED1 = false;            // Turn off the LED (simulated)
        printf("Condition not met.\n");
        printf("Sensor deactivated. LED1 is OFF.\n");
    }

    // Final debug: print updated sensor state
    printf("\nFinal Sensor ID: %d\n", sensor_ptr->id);
    printf("Final Sensor Temp: %.2f\n", sensor_ptr->temperature);
    printf("Final Sensor Status: %d\n", sensor_ptr->status);
    printf("LED1 State: %s\n", LED1 ? "ON" : "OFF");

    return 0;
}
