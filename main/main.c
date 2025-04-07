#include <stdio.h>

#include "uart.h"
#include "queue.h"
#pragma once



void app_main() {
    xTaskCreate(task_uart, "start uart", 2048, NULL, 5, NULL);

}