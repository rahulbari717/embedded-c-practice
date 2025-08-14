/*

🏠 Shared Resource (writeToBus function) 
🔑 Mutex (mutexBus) - mutex key shared resource in our case writetobus
if anybudy want to used resource semaphoretake 
and then used this resource after work done semaphore give to return mutex key to rtos sheduler person

Task 1: "FreeRTOS, give me the key to writeToBus!" 
        (xSemaphoreTake)

FreeRTOS: "Here's the key 🔑, use writeToBus"

Task 1: Uses writeToBus function safely

Task 1: "I'm done, here's your key back 🔑" 
        (xSemaphoreGive)

FreeRTOS: "Thanks! Now Task 2 can have the key"



*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

// IDF 4 / 5
SemaphoreHandle_t mutexBus;

// IDF 4
// xSemaphoreHandle mutexBus;

void writeToBus(char *message)
{
  printf(message);
}

void task1(void *params)
{
  while (true)
  {
    printf("reading temperature \n");
    if (xSemaphoreTake(mutexBus, 1000 / portTICK_PERIOD_MS))
    {
      writeToBus("tempratrue is 25c\n");
      xSemaphoreGive(mutexBus);
    }
    else
    {
      printf("writing temperature timed out \n");
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void task2(void *params)
{
  while (true)
  {
    printf("reading humidity\n");
    if (xSemaphoreTake(mutexBus, 1000 / portTICK_PERIOD_MS))
    {
      writeToBus("humidity is 50 \n");
      xSemaphoreGive(mutexBus);
    }
    else
    {
      printf("writing humidity timed out \n");
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void app_main(void)
{
  mutexBus = xSemaphoreCreateMutex();
  xTaskCreate(&task1, "temperature reading", 2048, NULL, 2, NULL);
  xTaskCreate(&task2, "humidity reading", 2048, NULL, 2, NULL);
}
