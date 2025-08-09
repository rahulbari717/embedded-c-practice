/* Include the POSIX header file.  */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// === Task States (FreeRTOS-like concept) ===
typedef enum {
    TASK_READY,
    TASK_RUNNING,
    TASK_BLOCKED,
    TASK_SUSPENDED,
    TASK_DELETED
} task_state_e;

// === Task Priority Levels ===
typedef enum {
    PRIORITY_IDLE = 0,
    PRIORITY_LOW = 1,
    PRIORITY_NORMAL = 2,
    PRIORITY_HIGH = 3,
    PRIORITY_CRITICAL = 4
} task_priority_e;

// === Task Control Block (TCB) Structure ===
typedef struct task_control_block {
    uint32_t task_id;
    char task_name[16];
    task_state_e state;
    task_priority_e priority;
    uint32_t stack_size;
    void (*task_function)(void*);
    void* parameters;
    uint32_t wake_time;
    struct task_control_block* next;
} tcb_t;

// === Sensor Structure ===
typedef struct {
    int id;
    float temperature;
    int status;
    bool initialized;
    uint32_t read_count;
} Sensor_t;

// === System Configuration Structure ===
typedef struct {
    uint32_t system_tick;
    uint32_t max_tasks;
    tcb_t* ready_queue;
    tcb_t* current_task;
    bool scheduler_running;
} system_config_t;

// === Global Variables ===
static system_config_t system_cfg = {0};
static bool LED1 = false;
static Sensor_t Gas_sensor1;
static tcb_t sensor_tcb;

// === Function Prototypes ===
void initialize_sensor(void);
void sensor_task(void* pvParameters);
void delay_sec(const uint32_t sec);
void task_create(const char* name, void (*task_func)(void*), uint32_t stack_size, 
                 void* parameters, task_priority_e priority, tcb_t* tcb);
void task_delay(uint32_t ticks);
void system_init(void);
void scheduler_start(void);
void task_yield(void);
uint32_t get_tick_count(void);

// === System Initialization ===
void system_init(void) {
    system_cfg.system_tick = 0;
    system_cfg.max_tasks = 10;
    system_cfg.ready_queue = NULL;
    system_cfg.current_task = NULL;
    system_cfg.scheduler_running = false;
    
    printf("[SYSTEM] OS Kernel initialized successfully ...\n");
}

// === Task Creation Function (FreeRTOS-like xTaskCreate) ===
void task_create(const char* name, void (*task_func)(void*), uint32_t stack_size, 
                 void* parameters, task_priority_e priority, tcb_t* tcb) {
    
    static uint32_t task_id_counter = 1;
    
    tcb->task_id = task_id_counter++;
    strncpy(tcb->task_name, name, sizeof(tcb->task_name) - 1);
    tcb->task_name[sizeof(tcb->task_name) - 1] = '\0';
    tcb->state = TASK_READY;
    tcb->priority = priority;
    tcb->stack_size = stack_size;
    tcb->task_function = task_func;
    tcb->parameters = parameters;
    tcb->wake_time = 0;
    tcb->next = NULL;
    
    // Add to ready queue (simple linked list)
    if (system_cfg.ready_queue == NULL) {
        system_cfg.ready_queue = tcb;
    } else {
        tcb_t* current = system_cfg.ready_queue;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = tcb;
    }
    
    printf("[TASK] Created: %s (ID: %u, Priority: %d)\n", 
           tcb->task_name, tcb->task_id, tcb->priority);
}

// === Task Delay Function (FreeRTOS-like vTaskDelay) ===
void task_delay(uint32_t ticks) {
    if (system_cfg.current_task != NULL) {
        system_cfg.current_task->state = TASK_BLOCKED;
        system_cfg.current_task->wake_time = system_cfg.system_tick + ticks;
    }
    // Simulate blocking by actual sleep
    sleep(ticks);
}

// === Get System Tick Count ===
uint32_t get_tick_count(void) {
    return system_cfg.system_tick;
}

// === Task Yield Function ===
void task_yield(void) {
    // Simple yield implementation
    system_cfg.system_tick++;
}

// === Scheduler Start Function ===
void scheduler_start(void) {
    system_cfg.scheduler_running = true;
    printf("[SCHEDULER] Starting task scheduler...\n");
    
    // Simple round-robin scheduler
    tcb_t* current = system_cfg.ready_queue;
    while (current != NULL && system_cfg.scheduler_running) {
        if (current->state == TASK_READY) {
            system_cfg.current_task = current;
            current->state = TASK_RUNNING;
            
            printf("[SCHEDULER] Running task: %s\n", current->task_name);
            
            // Execute task function
            if (current->task_function != NULL) {
                current->task_function(current->parameters);
            }
            
            current->state = TASK_DELETED;
        }
        current = current->next;
    }
    
    printf("[SCHEDULER] All tasks completed\n");
}

// === Sensor Initialization Function ===
void initialize_sensor(void) {
    printf("[INIT] Initializing all sensor subsystem...\n");
    
    // Initialize system
    system_init();
    
    // Initialize sensor structure
    Gas_sensor1.id = 1;
    Gas_sensor1.temperature = 20.5f;
    Gas_sensor1.status = 0;
    Gas_sensor1.initialized = true;
    Gas_sensor1.read_count = 0;
    
    // Initialize LED
    LED1 = false;
    
    // Create sensor task
    task_create("SensorTask", sensor_task, 2048, NULL, PRIORITY_NORMAL, &sensor_tcb);
    
    printf("[INIT] Sensor ID: %d initialized\n", Gas_sensor1.id);
    printf("[INIT] Initial temperature: %.2f°C\n", Gas_sensor1.temperature);
    printf("[INIT] LED1 state: %s\n", LED1 ? "ON" : "OFF");
    printf("[INIT] Initialization complete!\n\n");
}

// === Delay Function ===
void delay_sec(const uint32_t sec) {
    task_delay(sec);
}

// === Sensor Task Function ===
void sensor_task(void* pvParameters) {
    Sensor_t* sensor_ptr = &Gas_sensor1;
    
    printf("[TASK] Sensor task started (Task ID: %u)\n", 
           system_cfg.current_task ? system_cfg.current_task->task_id : 0);
    
    if (!sensor_ptr->initialized) {
        printf("[ERROR] Sensor not initialized!\n");
        return;
    }
    
    // Main sensor loop
    for (int temp = 1; temp <= 30; temp++) {
        sensor_ptr->temperature = (float)temp;
        sensor_ptr->read_count++;
        
        // Yield to scheduler (simulate multitasking)
        task_yield();
        
        // Debug Output: Simulating temperature change
        printf("\n[READING #%u] Temp: %.2f°C | ID: %d | Tick: %u\n", 
               sensor_ptr->read_count, sensor_ptr->temperature, 
               sensor_ptr->id, get_tick_count());
        
        // Condition Check with hysteresis
        if (sensor_ptr->id == 1 && sensor_ptr->temperature >= 25.0f) {
            sensor_ptr->status = 1;
            LED1 = true;
            printf("✔ [ALERT] Temperature threshold exceeded → Status: %d | LED1: ON\n", 
                   sensor_ptr->status);
        } else {
            sensor_ptr->status = 0;
            LED1 = false;
            printf("✖ [NORMAL] Temperature within range → Status: %d | LED1: OFF\n", 
                   sensor_ptr->status);
        }
        
        // Display system status
        printf("[STATUS] System Tick: %u | Task State: RUNNING\n", get_tick_count());
        
        // Wait before next reading
        delay_sec(2);
    }
    
    printf("\n[TASK] Sensor task completed after %u readings\n", sensor_ptr->read_count);
    printf("[TASK] Final sensor status: %d\n", sensor_ptr->status);
}

// === Main Function ===
int main(void) {
    printf("=== Sensor Management System ===\n\n");
    
    // Initialize sensor subsystem
    initialize_sensor();
    
    // Start the scheduler (runs sensor task)
    scheduler_start();
    
    printf("\n=== System Shutdown ===\n");
    return 0;
}