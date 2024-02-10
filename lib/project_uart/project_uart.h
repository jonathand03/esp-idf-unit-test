#ifndef PROJECT_UART_H
#define PROJECT_UART_H

#include "driver/uart.h"

#define UART_PARAM_ERROR            (-1)
#define ESP_DEFAULT_BAUDRATE        (115200)
#define TX_PIN                      (1)
#define RX_PIN                      (3)
#define UART_LED_ON                 ('p')
#define UART_LED_OFF                ('z')
#define MSG_SIZE                    (1)
#define NO_DATA                     (0)
#define FLAG_DATA_RECEIVED_SUCESS   (50)
#define UART_DATA_REQUEST           (60)
typedef enum
{
    UART_INIT_SUCESS,
    UART_INIT_ERROR
}uart_init_ret;

typedef enum
{
    UART_WRITE_SUCESS,
    UART_WRITE_ERROR
}uart_write_ret;

typedef enum
{
    UART_READ_SUCESS,
    UART_READ_ERROR,
    UART_READ_NO_DATA,
    UART_READ_DATA_OVERFLOW
}uart_read_ret;

/*! @brief Criador do tipo abstrato de dado para função de inicialização de uart*/
typedef uart_init_ret  (*fn_callback_uart_init)(uint32_t baud_rate, uint8_t tx, uint8_t rx);
/*! @brief Criador do tipo abstrato de dado para função de escrita de uart*/
typedef uart_write_ret (*fn_callback_write)(const void *data, size_t data_size);
/*! @brief Criador do tipo abstrato de dado para função de leitura de uart*/
typedef uart_read_ret  (*fn_callback_uart_read)(uint8_t *storage, size_t data_size);


/*! @brief  Tipo abstrato de dado para a classe uart
*           onde temos as funções de inicialização, escrita e leitura
*           Lembrando que qualquer função que não respeitar os contratos 
*           não será aceita pelo compilador
*
*  @example Caso você queira criar uma classe baseada nesse tipo @p communication_t
*            
*            void app_main(){
*                char data_buffer[30];    
*                communication_t Uart
*
*                // Exemplo de inicialização
*                Uart.init(115200,TX_PIN,RX_PIN);
*                // Exemplo de escrita
*                Uart.write("Hello UART! :D",15);
*                // Exemplo de leitura 
*                Uart.read(read_buffer,15);
*                // Mostrando dado que foi lido do buffer da uart ["Hello storage! :D"]
*                printf("%s\n", read_buffer);
*            }
*/
typedef struct
{
    fn_callback_uart_init   init;
    fn_callback_write       write;
    fn_callback_uart_read   read;
}communication_t;

/***************************************************************************************
* @brief Essa função tem como objetivo inicializar a uart do modulo em questão,
*        repassando alguns valores de entrada.
* @param[in] baude_rate É a taxa de transmissão de dados
* @param[in] tx O pino referente à transmissão de dados
* @param[in] rx O pino referente ao recebimento de dados
* @return Retorna os valores possíveis em @p uart_init_ret, onde podem ser
*         @p UART_INIT_SUCESS ou @p UART_INIT_ERROR a depender da execução da função
****************************************************************************************/
uart_init_ret uart_init(uint32_t baud_rate, uint8_t tx, uint8_t rx);

/***************************************************************************************
* @brief Essa função tem como objetivo enviar valores através da serial
* @param[in] data é o valor a ser enviado
* @return Retorna os valores possíveis em @p uart_write_ret, onde podem ser
*         @p UART_WRITE_SUCESS ou @p UART_WRITE_ERROR a depender da execução da função
*****************************************************************************************/
uart_write_ret uart_write(const void *data, size_t data_size);

/***************************************************************************************
* @brief Essa função tem como objetivo fazer uma leitra no barramento serial, 
*        onde é necessário passar como parametro uma variável que irá armazenar esse valor recebido
* @param[in] storage é o buffer onde ficará armazenado o valor recebido
* @return Retorna os valores possíveis em @p uart_read_ret, onde podem ser
*         @p UART_READ_SUCESS ou @p UART_READ_ERRROR a depender da execução da função
****************************************************************************************/
uart_read_ret uart_read(uint8_t *storage, size_t data_size);

/*! @brief Tornando o TAD Uart como extern para ser utilizado como classe em qualquer parte do projeto*/
extern communication_t  Uart;

#endif /*UART_H*/