#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

// ===== HOTEL SYSTEM - ALL FreeRTOS CONCEPTS =====

// 🏨 SHARED RESOURCES (Protected by MUTEX)
SemaphoreHandle_t kitchenMutex;      // Only 1 chef can use kitchen equipment
SemaphoreHandle_t printerMutex;     // Only 1 person can use receipt printer

// 📢 NOTIFICATIONS (Binary Semaphore)
SemaphoreHandle_t orderReady;       // Kitchen → Waiter notification
SemaphoreHandle_t customerArrived;  // Reception → Waiter notification

// 🎫 RESOURCE COUNTING (Counting Semaphore)
SemaphoreHandle_t availableTables;  // 5 tables in restaurant

// 📬 DATA COMMUNICATION (Queue)
QueueHandle_t orderQueue;           // Customer → Kitchen orders
QueueHandle_t billQueue;            // Waiter → Cashier bills

// 🎯 MULTIPLE CONDITIONS (Event Groups)
EventGroupHandle_t hotelStatus;     // Hotel operational status

// Event Group Bits
#define KITCHEN_READY    (1 << 0)   // Bit 0: Kitchen is ready
#define WAITER_READY     (1 << 1)   // Bit 1: Waiter is ready  
#define CASHIER_READY    (1 << 2)   // Bit 2: Cashier is ready
#define CLEANER_READY    (1 << 3)   // Bit 3: Cleaner is ready
#define HOTEL_OPEN       (KITCHEN_READY | WAITER_READY | CASHIER_READY | CLEANER_READY)

// Data Structures for Queue Communication
typedef struct {
    int customerID;
    char dish[30];
    int tableNumber;
} Order;

typedef struct {
    int customerID;
    int amount;
    int tableNumber;
} Bill;

// Global variables
int customerCounter = 1;

// ===== TASK 1: RECEPTION (Customer arrival notifications) =====
void reception_task(void *params) {
    printf("🏨 Reception: Hotel reception started\n");
    
    while(1) {
        // Customer arrives every 8 seconds
        vTaskDelay(8000 / portTICK_PERIOD_MS);
        
        printf("🚶 Reception: Customer %d arrived!\n", customerCounter++);
        
        // Notify waiter about new customer (Binary Semaphore)
        xSemaphoreGive(customerArrived);
    }
}

// ===== TASK 2: WAITER (Handles customers, takes orders) =====
void waiter_task(void *params) {
    printf("👨‍💼 Waiter: Getting ready...\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    
    // Signal waiter is ready
    xEventGroupSetBits(hotelStatus, WAITER_READY);
    printf("👨‍💼 Waiter: Ready to serve!\n");
    
    Order newOrder;
    Bill newBill;
    
    while(1) {
        // Wait for customer arrival notification
        if (xSemaphoreTake(customerArrived, portMAX_DELAY)) {
            
            // Try to get a table (Counting Semaphore)
            if (xSemaphoreTake(availableTables, 2000 / portTICK_PERIOD_MS)) {
                
                printf("👨‍💼 Waiter: Seating customer at table, taking order\n");
                
                // Create order
                newOrder.customerID = customerCounter - 1;
                strcpy(newOrder.dish, "Pasta");
                newOrder.tableNumber = 5 - uxSemaphoreGetCount(availableTables); // Table number
                
                // Send order to kitchen (Queue)
                if (xQueueSend(orderQueue, &newOrder, 1000 / portTICK_PERIOD_MS)) {
                    printf("👨‍💼 Waiter: Order sent to kitchen for Customer %d\n", newOrder.customerID);
                }
                
                // Wait for order ready notification
                if (xSemaphoreTake(orderReady, 15000 / portTICK_PERIOD_MS)) {
                    printf("👨‍💼 Waiter: Order ready! Serving customer %d\n", newOrder.customerID);
                    
                    // Create bill
                    newBill.customerID = newOrder.customerID;
                    newBill.amount = 250; // ₹250
                    newBill.tableNumber = newOrder.tableNumber;
                    
                    // Send bill to cashier (Queue)
                    xQueueSend(billQueue, &newBill, 1000 / portTICK_PERIOD_MS);
                    
                    // Customer leaves - free the table
                    vTaskDelay(3000 / portTICK_PERIOD_MS); // Customer eats for 3 seconds
                    printf("👨‍💼 Waiter: Customer %d finished, table %d is free\n", 
                           newBill.customerID, newBill.tableNumber);
                    xSemaphoreGive(availableTables); // Free the table
                }
                
            } else {
                printf("👨‍💼 Waiter: Sorry, all tables occupied! Customer left\n");
            }
        }
    }
}

// ===== TASK 3: CHEF (Cooks food in kitchen) =====
void chef_task(void *params) {
    printf("👨‍🍳 Chef: Kitchen setup starting...\n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    
    // Signal kitchen is ready
    xEventGroupSetBits(hotelStatus, KITCHEN_READY);
    printf("👨‍🍳 Chef: Kitchen ready!\n");
    
    Order receivedOrder;
    
    while(1) {
        // Wait for orders from waiter (Queue)
        if (xQueueReceive(orderQueue, &receivedOrder, portMAX_DELAY)) {
            
            printf("👨‍🍳 Chef: Received order - %s for Customer %d\n", 
                   receivedOrder.dish, receivedOrder.customerID);
            
            // Use kitchen equipment (Mutex protection)
            if (xSemaphoreTake(kitchenMutex, 3000 / portTICK_PERIOD_MS)) {
                
                printf("👨‍🍳 Chef: Using stove and equipment to cook %s\n", receivedOrder.dish);
                vTaskDelay(5000 / portTICK_PERIOD_MS); // Cooking takes 5 seconds
                printf("👨‍🍳 Chef: %s ready for Customer %d!\n", 
                       receivedOrder.dish, receivedOrder.customerID);
                
                xSemaphoreGive(kitchenMutex); // Release kitchen equipment
                
                // Notify waiter that order is ready (Binary Semaphore)
                xSemaphoreGive(orderReady);
                
            } else {
                printf("👨‍🍳 Chef: Kitchen busy! Order delayed\n");
            }
        }
    }
}

// ===== TASK 4: CASHIER (Handles payments and bills) =====
void cashier_task(void *params) {
    printf("💰 Cashier: Cash register setup...\n");
    vTaskDelay(1500 / portTICK_PERIOD_MS);
    
    // Signal cashier is ready
    xEventGroupSetBits(hotelStatus, CASHIER_READY);
    printf("💰 Cashier: Ready to handle payments!\n");
    
    Bill receivedBill;
    
    while(1) {
        // Wait for bills from waiter (Queue)
        if (xQueueReceive(billQueue, &receivedBill, portMAX_DELAY)) {
            
            printf("💰 Cashier: Processing payment for Customer %d - ₹%d\n", 
                   receivedBill.customerID, receivedBill.amount);
            
            // Use receipt printer (Mutex protection)
            if (xSemaphoreTake(printerMutex, 2000 / portTICK_PERIOD_MS)) {
                
                printf("💰 Cashier: Printing receipt for Customer %d\n", receivedBill.customerID);
                vTaskDelay(2000 / portTICK_PERIOD_MS); // Printing takes 2 seconds
                printf("💰 Cashier: Payment complete for Customer %d ✅\n", receivedBill.customerID);
                
                xSemaphoreGive(printerMutex); // Release printer
            }
        }
    }
}

// ===== TASK 5: CLEANER (Cleans hotel) =====
void cleaner_task(void *params) {
    printf("🧹 Cleaner: Getting cleaning supplies...\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    
    // Signal cleaner is ready
    xEventGroupSetBits(hotelStatus, CLEANER_READY);
    printf("🧹 Cleaner: Ready to clean!\n");
    
    while(1) {
        // Clean every 10 seconds
        vTaskDelay(10000 / portTICK_PERIOD_MS);
        
        printf("🧹 Cleaner: Cleaning floors and tables\n");
        vTaskDelay(3000 / portTICK_PERIOD_MS); // Cleaning takes 3 seconds
        printf("🧹 Cleaner: Cleaning completed ✨\n");
    }
}

// ===== TASK 6: HOTEL MANAGER (Monitors hotel status) =====
void manager_task(void *params) {
    printf("👨‍💼 Manager: Waiting for all staff to be ready...\n");
    
    // Wait for all staff to be ready (Event Group)
    EventBits_t bits = xEventGroupWaitBits(
        hotelStatus,
        HOTEL_OPEN,     // Wait for all bits
        pdFALSE,        // Don't clear bits
        pdTRUE,         // Wait for ALL bits (AND condition)
        portMAX_DELAY   // Wait forever
    );
    
    if ((bits & HOTEL_OPEN) == HOTEL_OPEN) {
        printf("\n🎉 Manager: ALL STAFF READY! HOTEL IS NOW OPEN! 🎉\n");
        printf("🏨 Manager: Kitchen✅ Waiter✅ Cashier✅ Cleaner✅\n\n");
    }
    
    // Monitor hotel operations
    while(1) {
        vTaskDelay(15000 / portTICK_PERIOD_MS);
        printf("📊 Manager: Checking hotel operations... All good! 👍\n");
        printf("📊 Manager: Available tables: %d/5\n", uxSemaphoreGetCount(availableTables));
    }
}

// ===== MAIN APPLICATION =====
void app_main(void) {
    printf("\n🏨 ===== HOTEL MANAGEMENT SYSTEM ===== 🏨\n");
    printf("🎯 Demonstrating ALL FreeRTOS concepts!\n\n");
    
    // ===== CREATE ALL SYNCHRONIZATION OBJECTS =====
    
    // MUTEX - Shared resource protection
    kitchenMutex = xSemaphoreCreateMutex();
    printerMutex = xSemaphoreCreateMutex();
    
    // BINARY SEMAPHORE - Notifications
    orderReady = xSemaphoreCreateBinary();
    customerArrived = xSemaphoreCreateBinary();
    
    // COUNTING SEMAPHORE - Resource counting (5 tables)
    availableTables = xSemaphoreCreateCounting(5, 5);
    
    // QUEUE - Data communication
    orderQueue = xQueueCreate(10, sizeof(Order));  // Max 10 orders
    billQueue = xQueueCreate(10, sizeof(Bill));    // Max 10 bills
    
    // EVENT GROUP - Multiple condition monitoring
    hotelStatus = xEventGroupCreate();
    
    // ===== CREATE ALL TASKS =====
    
    xTaskCreate(reception_task, "Reception", 2048, NULL, 2, NULL);
    xTaskCreate(waiter_task, "Waiter", 2048, NULL, 3, NULL);
    xTaskCreate(chef_task, "Chef", 2048, NULL, 3, NULL);
    xTaskCreate(cashier_task, "Cashier", 2048, NULL, 2, NULL);
    xTaskCreate(cleaner_task, "Cleaner", 2048, NULL, 1, NULL);
    xTaskCreate(manager_task, "Manager", 2048, NULL, 4, NULL);
    
    printf("🚀 Hotel system starting...\n\n");
}

/*
===== WHAT THIS PROGRAM DEMONSTRATES =====

1. TASKS (6 different workers):
   - Reception, Waiter, Chef, Cashier, Cleaner, Manager

2. MUTEX (Shared resource protection):
   - kitchenMutex: Only 1 chef can use kitchen equipment
   - printerMutex: Only 1 person can use receipt printer

3. BINARY SEMAPHORE (Notifications):
   - orderReady: Kitchen notifies waiter when food is ready
   - customerArrived: Reception notifies waiter about new customer

4. COUNTING SEMAPHORE (Resource counting):
   - availableTables: Track 5 restaurant tables

5. QUEUE (Data transfer):
   - orderQueue: Send order details from waiter to chef
   - billQueue: Send bill details from waiter to cashier

6. EVENT GROUPS (Multiple conditions):
   - hotelStatus: Wait for all staff to be ready before opening

===== OUTPUT WILL SHOW =====
- Hotel opening sequence (Event Group)
- Customer arrivals and table allocation (Counting Semaphore)
- Order processing pipeline (Queue + Binary Semaphore)
- Resource protection (Mutex for kitchen/printer)
- All tasks working together in harmony!

===== FLOW =====
Reception → Waiter → Chef → Waiter → Cashier
     ↓         ↓      ↓       ↓        ↓
  Customer  Table   Kitchen  Order   Payment
  Arrives  (Count) (Mutex)  (Queue) (Printer)
*/