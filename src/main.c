#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "project_uart.h"
#include "project_storage.h"
#include "project_gpio.h"

uint8_t buffer[10];

void app_main() 
{
    Storage.init(true);
    Gpio.init(GPIO_NUM_2,GPIO_MODE_OUTPUT);
    Uart.init(ESP_DEFAULT_BAUDRATE,TX_PIN,RX_PIN);

    while(1)
    {
        if(Uart.read(buffer,10) == UART_READ_SUCESS)
        {
            for(int i = 0 ; i < 10; i++) printf("%d ", buffer[i]);
        }
    }
    
}