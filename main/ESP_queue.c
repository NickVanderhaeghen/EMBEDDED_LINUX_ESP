#include "./include/ESP_queue.h"
#include "./include/uart.h"

#pragma once

QueueHandle_t RXQueue;
QueueHandle_t TXQueue;

uint8_t msg_length = 0;

queue_msg_t rx_msg;


QueueHandle_t queueMake(){
    QueueHandle_t Queue = xQueueCreate(20, sizeof(my_msg_t)); //maakt een queue aan waar 20 berichtjes in kunnen
    if(Queue == NULL){
        printf("Queue is niet aangemaakt omdat het geheugen niet toegewezen kon worden\n\r");
    }
    else{printf("Queue aangemaakt!\n\r");}
    return Queue;
}

void queueRemove(){
    vQueueDelete(RXQueue);
    vQueueDelete(TXQueue);
}

void queueSend(QueueHandle_t queue, queue_msg_t* queue_msg){
    xQueueSend(queue, queue_msg, 100);
}  

void queueReceive(QueueHandle_t queue){
    if(queue != NULL){
        if(xQueueReceive(queue, &rx_msg, 100)){
            afhandeling();
        }
    }
}

void afhandeling(){

    int lengte_data = 0; // wat is de lengte van de data voordat we een \0 krijgen
    for(int i = 0; i < 20; i++){ //hier wordt de lengte berekend voor een \0
        if(rx_msg.msg.data[i] != 0x00){
            lengte_data++;
        }
        else{break;}
    }

    char tekst[lengte_data]; //Wat is de effectieve tekst die in data zit?
    for(int i = 0; i < lengte_data; i++){ //hier steken we de tekst in een char[lengte_data]
        tekst[i] = rx_msg.msg.data[i];
    }

    printf("cmd =  %c\n\r", rx_msg.msg.cmd);
    printf("data =  %s\n\r", rx_msg.msg.data);
    printf("wie =  0X%X\n\r", rx_msg.msg.wie);

    if(rx_msg.msg.cmd == 'l'){
        
        if(strcmp(rx_msg.msg.data, "blink") == 0){
            led_blink();
        }
        else if(strcmp(rx_msg.msg.data, "test") == 0){
            led_test();
        }
        else if(strcmp(rx_msg.msg.data, "on") == 0){
            led_all_on();
        }
        else if(strcmp(rx_msg.msg.data, "off") == 0){
            led_all_off();
        }
        else if(strcmp(rx_msg.msg.data, "benjeernog") == 0){
            uart_send();
        }
    }


}

void queueTask(){
    RXQueue = queueMake();
    TXQueue = queueMake();
    while (1)
    {
        queueReceive(RXQueue);
        vTaskDelay(100);
    }
}