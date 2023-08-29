#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define TAG "learnRTOS"
// #define PIN19 GPIO_NUM_19
// #define PIN21 GPIO_NUM_21

void task1_LED1 (void * param)
{
    while (1)
    {
        ESP_LOGI(TAG, "Printing from task1 loop. ");
        gpio_set_level(GPIO_NUM_19, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_19, 0);
    }
}

void task2_LED2 (void * param)
{
    while (1)
    {
        ESP_LOGI(TAG, "Printing from task2 loop. ");
        gpio_set_level(GPIO_NUM_21, 1);
        vTaskDelay(1500 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_21, 0);
    }
}


void app_main(void)
{
    gpio_set_direction (19,GPIO_MODE_OUTPUT);
    gpio_set_direction (21,GPIO_MODE_OUTPUT);
    TaskHandle_t task1_handle = NULL;
    TaskHandle_t task2_handle = NULL;

    xTaskCreate(task1_LED1, "task1", 1024*2, NULL, 1, task1_handle);
    xTaskCreate(task2_LED2, "task2", 1024*2, NULL, 2, task2_handle);

    while (1)
    {
        ESP_LOGI(TAG, "Printing from Main loop. ");
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
    
}
