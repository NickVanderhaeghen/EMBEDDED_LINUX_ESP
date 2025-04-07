#include "uart.h"




void config_uart(){
    gpio_set_direction(47, GPIO_MODE_OUTPUT);
    gpio_set_direction(48, GPIO_MODE_OUTPUT);

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

void task_uart(){
    config_uart();
    char data[BUF_SIZE];
    while (1) {
        int len = uart_read_bytes(UART_NUM, &data, BUF_SIZE, 20 / portTICK_PERIOD_MS);
        if (len > 0) {
            data[len] = '\0';  // Null-terminate de string
            gpio_set_level(47, 1);
            uart_write_bytes(UART_NUM, (const char *) data, len); // Echo terug
        }
    }
}
