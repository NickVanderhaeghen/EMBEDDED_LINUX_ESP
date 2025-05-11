#include "./include/uart.h"



char data[BUF_SIZE];
int lengte = 25;

queue_msg_t message;
my_msg_t queue_msg;

queue_msg_t tx_msg = {
    .msg.cmd = 'y',
    .msg.data = "ik ben er nog",
    .msg.wie = 'e'
};


void config_uart(){
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    uart_driver_install(UART_NUM, BUF_SIZE, 0, 0, NULL, 0);
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}


void uart_send(){
    uart_write_bytes(UART_NUM, &tx_msg, sizeof(queue_msg_t)); // Echo terug
    printf("data is teruggestuurd. berichtje is %s\n\r", tx_msg.msg.data);
}

void uart_receive(){
    int len = uart_read_bytes(UART_NUM, &data, sizeof(queue_msg_t), 20 / portTICK_PERIOD_MS);
    if (len > 0) {
        // printf("Ontvangen bericht van %d bytes:\n", len);
        // for (int i = 0; i < len; i++) {
        //     printf("Byte %d: %02X\n\r", i, data[i]);
        //     printf("is de letter %c\n\r", data[i]);
    
        // }
        uart_send();
        data_to_typedef();
        queueSend(RXQueue, &message);
    }
}

void data_to_typedef(){
    message.msg.cmd = data[8];
    memcpy(message.msg.data, &data[9], 17);
    message.msg.wie = data[29];
}


void task_uart(){
    config_uart();
    while (1) {
        uart_receive();

            //uart_write_bytes(UART_NUM, (const char *) data, len); // Echo terug
        }
}