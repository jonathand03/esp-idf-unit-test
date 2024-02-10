#include <stdio.h>
#include "unity.h"
#include "project_uart.h"


void test_case_uart_init_sucess(void)
{
    uart_init_ret ret = Uart.init(ESP_DEFAULT_BAUDRATE,TX_PIN,RX_PIN);
    TEST_ASSERT(ret == UART_INIT_SUCESS);
}


int app_main()
{
    UNITY_BEGIN();
    RUN_TEST(test_case_uart_init_sucess);
    return UNITY_END();
}
