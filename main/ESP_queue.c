#include "./include/uart.h"
#include "./include/ESP_queue.h"


QueueHandle_t RXQueue;
QueueHandle_t TXQueue;

uint8_t msg_length = 0;

queue_msg_t rx_msg;

queue_msg_t tx_msg = {
    .msg.start = 's',
    .msg.length = 25,
    .msg.cmd = 'y',
    .msg.data = "ik ben er nog",
    .msg.wie = 'e',
    .msg.stop = 's'
};




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
    xQueueSend(queue, &queue_msg, 100);
}
void queueReceive(QueueHandle_t queue){
    if(queue != NULL){
        if( xQueueReceive(queue, &rx_msg, 100)){        

            printf("Wie: %d\n\r", rx_msg.msg.wie);            
            printf("bericht lengte = %i\n\r", sizeof(rx_msg.msg.data));
        }
    }
}

void uartToQueue(){

}

void queueTask(){
    RXQueue = queueMake();
    TXQueue = queueMake();
    while (1)
    {
        queueReceive(RXQueue);
        vTaskDelay(1000);
    }
}