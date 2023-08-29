#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

void app_main ()
{
    xTaskCreate(task_LED1, "task1", 1024*2, NULL, 3, NULL);
    xTaskCreate(task_LED2, "task2", 1024*2, NULL, 3, NULL);
}

//task1
void task_LED1 (void *param)
{

    while (1)
    {
        printf("this is task 1 \n");

    }
    vTaskDelete(NULL);
}


//task2
void task_LED2 (void *param)
{

    while (1)
    {
        printf("this is task 2 \n");

    }
    vTaskDelete(NULL);
    
}