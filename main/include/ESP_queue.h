#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#pragma once

extern QueueHandle_t RXQueue;
extern QueueHandle_t TXQueue;

typedef struct //pakketjes hebben een lengte van 25, uint8_t = 1 
{
    uint8_t start;
    uint8_t length;
    uint8_t cmd;
    char data[20];
    uint8_t wie;
    uint8_t stop;
}my_msg_t;


typedef struct
{
    my_msg_t msg;
}queue_msg_t;



QueueHandle_t queueMake();
void queueRemove();

void queueSend(QueueHandle_t queue, queue_msg_t* queue_msg);
void queueReceive(QueueHandle_t queue);

void uartToQueue();

void queueTask();