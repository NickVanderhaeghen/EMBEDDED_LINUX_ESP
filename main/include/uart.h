#include <string.h>
#include <driver/uart.h>
#include <esp_log.h>
#include <driver/gpio.h>
#include "ESP_queue.h"

#pragma once


#define UART_NUM UART_NUM_2
#define TX_PIN 43
#define RX_PIN 44
#define BUF_SIZE 1024




void config_uart();

void uart_read();

void uart_receive();

void test();

void task_uart();