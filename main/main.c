#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#include "./include/uart.h"
#include "./include/ESP_queue.h"


void app_main() {
    xTaskCreate(task_uart, "start uart", 2048, NULL, 5, NULL);
    xTaskCreate(queueTask, "maak en open queue", 5096, NULL, 5, NULL);
}