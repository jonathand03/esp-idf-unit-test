#include "project_uart.h"

uart_init_ret uart_init(uint32_t baud_rate, uint8_t tx, uint8_t rx)
{
    uart_config_t uart_config =
            {
                    .baud_rate = baud_rate,
                    .data_bits = UART_DATA_8_BITS,
                    .parity = UART_PARITY_DISABLE,
                    .stop_bits = UART_STOP_BITS_1,
                    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
                    .source_clk = UART_SCLK_DEFAULT,
            };
    /*!
    *    @brief Crio @p get_ret para fazer as verificações de retorno e 
    *    sair da função caso alguma delas não inicialize com sucesso
    */
    esp_err_t get_ret;

    get_ret = uart_driver_install(UART_NUM_0, 1024, 1024, 0, NULL, 0);
    if(get_ret != ESP_OK)return UART_INIT_ERROR;
    get_ret = uart_param_config(UART_NUM_0, &uart_config);
    if(get_ret != ESP_OK)return UART_INIT_ERROR;
    get_ret = uart_set_pin(UART_NUM_0, tx, rx, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    if(get_ret != ESP_OK)return UART_INIT_ERROR;

    return UART_INIT_SUCESS;
}

uart_write_ret uart_write(const void *data, size_t data_size)
{
    if (data == NULL || data_size == NO_DATA) return UART_WRITE_ERROR;
    int get_ret = uart_write_bytes(UART_NUM_0, (const char *)data, data_size);
    return get_ret != UART_PARAM_ERROR ? UART_WRITE_SUCESS : UART_WRITE_ERROR;
}

uart_read_ret uart_read(uint8_t *storage, size_t data_size)
{
    // Modo bloqueante até que todos os dados sejam lidos
    int get_ret = uart_read_bytes(UART_NUM_0,storage,data_size, portMAX_DELAY);

    if(get_ret == NO_DATA)return UART_READ_NO_DATA;
    if(get_ret > data_size) return UART_READ_DATA_OVERFLOW;
    return get_ret != UART_PARAM_ERROR ? UART_READ_SUCESS : UART_READ_ERROR;
}


communication_t  Uart = {
        .init = uart_init,
        .write = uart_write,
        .read = uart_read
};