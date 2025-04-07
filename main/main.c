#include <stdio.h>

#include "uart.h"
#include "ESP_queue.h"


void app_main() {
    xTaskCreate(task_uart, "start uart", 2048, NULL, 5, NULL);

}