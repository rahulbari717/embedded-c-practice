#include <stdio.h>
#include <string.h>

// =============================================================================
// 1. STRUCT POINTERS WITH ARROW OPERATOR (->)
// =============================================================================

/*
THEORY:
- Arrow operator (->) is used to access struct members through a pointer
- ptr->member is same as (*ptr).member
- Very commonly used in embedded systems and drivers
*/

struct device {
    char name[20];
    int id;
    int status;    // 0=off, 1=on
};

void example1_struct_pointers() {
    printf("=== 1. STRUCT POINTERS WITH ARROW OPERATOR ===\n");
    
    // Create a struct
    struct device led = {"Red_LED", 1, 0};
    
    // Create pointer to struct
    struct device *dev_ptr = &led;
    
    printf("Before: Device %s (ID:%d) Status:%d\n", 
           dev_ptr->name, dev_ptr->id, dev_ptr->status);
    
    // Use arrow operator to modify
    dev_ptr->status = 1;  // Turn on LED
    
    printf("After:  Device %s (ID:%d) Status:%d\n", 
           dev_ptr->name, dev_ptr->id, dev_ptr->status);
    
    // Show it's same as (*ptr).member
    printf("Using (*ptr).member: Status = %d\n", (*dev_ptr).status);
    printf("\n");
}

// =============================================================================
// 2. FUNCTION POINTERS IN DETAIL
// =============================================================================

/*
THEORY:
- Function pointer is a variable that stores address of a function
- Syntax: return_type (*pointer_name)(parameter_types)
- Can point to different functions with same signature
- Very useful for creating flexible, reusable code
*/

// Different operation functions
int add_numbers(int a, int b) {
    printf("Adding: %d + %d = %d\n", a, b, a + b);
    return a + b;
}

int multiply_numbers(int a, int b) {
    printf("Multiplying: %d * %d = %d\n", a, b, a * b);
    return a * b;
}

int subtract_numbers(int a, int b) {
    printf("Subtracting: %d - %d = %d\n", a, b, a - b);
    return a - b;
}

void example2_function_pointers() {
    printf("=== 2. FUNCTION POINTERS IN DETAIL ===\n");
    
    // Declare function pointer
    // This pointer can point to any function that:
    // - Returns int
    // - Takes two int parameters
    int (*math_operation)(int, int);
    
    printf("Function pointer size: %zu bytes\n", sizeof(math_operation));
    
    // Point to different functions
    printf("\n--- Pointing to add_numbers ---\n");
    math_operation = add_numbers;  // or &add_numbers (both work)
    int result1 = math_operation(5, 3);
    
    printf("\n--- Pointing to multiply_numbers ---\n");
    math_operation = multiply_numbers;
    int result2 = math_operation(5, 3);
    
    printf("\n--- Pointing to subtract_numbers ---\n");
    math_operation = subtract_numbers;
    int result3 = math_operation(5, 3);
    
    printf("Results: %d, %d, %d\n\n", result1, result2, result3);
}

// =============================================================================
// 3. CALLBACK FUNCTIONS
// =============================================================================

/*
THEORY:
- Callback is a function passed as parameter to another function
- The receiving function can "call back" (invoke) the passed function
- Very common in embedded systems for event handling, timers, etc.
*/

// Different callback functions
void led_blink_callback() {
    printf("  -> LED is blinking!\n");
}

void buzzer_beep_callback() {
    printf("  -> Buzzer is beeping!\n");
}

void motor_rotate_callback() {
    printf("  -> Motor is rotating!\n");
}

// Timer function that accepts callback
void timer_expired(int timer_id, void (*callback_function)()) {
    printf("Timer %d expired! Executing callback...\n", timer_id);
    
    // Call the callback function
    if (callback_function != NULL) {
        callback_function();  // This is the callback!
    }
}

// Advanced callback with parameters
void sensor_data_callback(int sensor_value) {
    printf("  -> Sensor reading: %d (Processing data...)\n", sensor_value);
}

void process_sensor_data(int data, void (*callback)(int)) {
    printf("Processing sensor data: %d\n", data);
    
    // Do some processing...
    data = data * 2;  // Simple processing
    
    // Call callback with processed data
    if (callback != NULL) {
        callback(data);
    }
}

void example3_callback_functions() {
    printf("=== 3. CALLBACK FUNCTIONS ===\n");
    
    printf("--- Simple Callbacks ---\n");
    timer_expired(1, led_blink_callback);
    timer_expired(2, buzzer_beep_callback);
    timer_expired(3, motor_rotate_callback);
    
    printf("\n--- Callbacks with Parameters ---\n");
    process_sensor_data(25, sensor_data_callback);
    process_sensor_data(40, sensor_data_callback);
    printf("\n");
}

// =============================================================================
// 4. COMBINING ALL CONCEPTS - SIMPLE DEVICE DRIVER
// =============================================================================

/*
THEORY:
- Real embedded systems combine all these concepts
- Struct contains device data + function pointers
- Function pointers act as device operations
- Callbacks handle events/interrupts
*/

struct simple_device {
    char name[20];
    int state;
    
    // Function pointers for device operations
    void (*turn_on)(struct simple_device *dev);
    void (*turn_off)(struct simple_device *dev);
    void (*set_callback)(struct simple_device *dev, void (*callback)());
    
    // Callback function pointer
    void (*event_callback)();
};

// LED device operations
void led_turn_on(struct simple_device *dev) {
    printf("[%s] LED turned ON\n", dev->name);
    dev->state = 1;
    
    // Trigger callback if set
    if (dev->event_callback != NULL) {
        printf("[%s] Triggering event callback...\n", dev->name);
        dev->event_callback();
    }
}

void led_turn_off(struct simple_device *dev) {
    printf("[%s] LED turned OFF\n", dev->name);
    dev->state = 0;
}

void led_set_callback(struct simple_device *dev, void (*callback)()) {
    printf("[%s] Setting event callback\n", dev->name);
    dev->event_callback = callback;
}

// Motor device operations
void motor_turn_on(struct simple_device *dev) {
    printf("[%s] Motor started\n", dev->name);
    dev->state = 1;
    
    if (dev->event_callback != NULL) {
        printf("[%s] Triggering event callback...\n", dev->name);
        dev->event_callback();
    }
}

void motor_turn_off(struct simple_device *dev) {
    printf("[%s] Motor stopped\n", dev->name);
    dev->state = 0;
}

void motor_set_callback(struct simple_device *dev, void (*callback)()) {
    printf("[%s] Setting event callback\n", dev->name);
    dev->event_callback = callback;
}

// Event callback functions
void led_event_handler() {
    printf("    EVENT: LED state changed - updating display\n");
}

void motor_event_handler() {
    printf("    EVENT: Motor state changed - checking temperature\n");
}

// Device creation function
void create_device(struct simple_device *dev, const char *name,
                  void (*on_func)(struct simple_device *),
                  void (*off_func)(struct simple_device *),
                  void (*callback_func)(struct simple_device *, void (*)()) ) {
    
    strcpy(dev->name, name);
    dev->state = 0;
    dev->event_callback = NULL;
    
    // Set function pointers
    dev->turn_on = on_func;
    dev->turn_off = off_func;
    dev->set_callback = callback_func;
}

void example4_complete_driver() {
    printf("=== 4. COMPLETE DEVICE DRIVER EXAMPLE ===\n");
    
    // Create devices
    struct simple_device led_device, motor_device;
    
    create_device(&led_device, "Red_LED", led_turn_on, led_turn_off, led_set_callback);
    create_device(&motor_device, "DC_Motor", motor_turn_on, motor_turn_off, motor_set_callback);
    
    // Create pointers to devices
    struct simple_device *dev1 = &led_device;
    struct simple_device *dev2 = &motor_device;
    
    printf("\n--- Setting up callbacks ---\n");
    // Set callbacks using function pointers and arrow operator
    dev1->set_callback(dev1, led_event_handler);
    dev2->set_callback(dev2, motor_event_handler);
    
    printf("\n--- Controlling devices ---\n");
    // Control devices using function pointers through arrow operator
    dev1->turn_on(dev1);    // LED on (triggers callback)
    dev2->turn_on(dev2);    // Motor on (triggers callback)
    
    printf("\n--- Device states ---\n");
    printf("%s state: %d\n", dev1->name, dev1->state);
    printf("%s state: %d\n", dev2->name, dev2->state);
    
    printf("\n--- Turning off ---\n");
    dev1->turn_off(dev1);   // LED off
    dev2->turn_off(dev2);   // Motor off
    printf("\n");
}

// =============================================================================
// MAIN FUNCTION
// =============================================================================

int main() {
    printf("Function Pointers, Struct Pointers & Callbacks Tutorial\n");
    printf("=======================================================\n\n");
    
    example1_struct_pointers();
    example2_function_pointers();
    example3_callback_functions();
    example4_complete_driver();
    
    printf("=== SUMMARY ===\n");
    printf("1. Arrow operator (->): Access struct members through pointer\n");
    printf("2. Function pointers: Variables that store function addresses\n");
    printf("3. Callbacks: Functions passed as parameters to other functions\n");
    printf("4. Real usage: Device drivers use all these concepts together\n");
    
    return 0;
}