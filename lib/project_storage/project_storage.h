#ifndef PROJECT_STORAGE_H
#define PROJECT_STORAGE_H
#include "esp_spiffs.h"
#include "esp_log.h"

#define ROOT_PATH_NAME      "/root"
#define LOG_PATH_NAME       "/root/log"
#define DEBUG_TAG           "[VERIFICACAO]"

typedef enum
{
    storage_init_sucess,
    storage_init_error,
    storage_write_sucess,
    storage_write_error,
    storage_read_sucess,
    storage_read_error
}storage_ret;

/*! 
*    @brief  Contratos para criação do TAD storage. É preciso ser respeitado 
*            seu retorno e parametros de entrada
*/
typedef storage_ret (*fn_callback_storage_init)(bool verification);
typedef storage_ret (*fn_callback_storage_write)(const void *data, const char *partition_label);
typedef storage_ret (*fn_callback_storage_read)(const char *partition_label, void *buffer, size_t read_size);

/*! @brief  Tipo abstrato de dado para a classe storage
*           onde temos as funções de inicialização, escrita e leitura
*           Lembrando que qualquer função que não respeitar os contratos 
*           não será aceita pelo compilador
*
*  @example Caso você queira criar uma classe baseada nesse tipo  storage_t
*            
*            void app_main(){
*                char read_buffer[30];    
*                storage_t Storage
*
*                // Exemplo de inicialização
*                Storage.init(true);
*                // Exemplo de escrita
*                Storage.write("Hello storage! :D","/root");
*                // Exemplo de leitura 
*                Storage.read("/root",read_buffer,22);
*                // Mostrando dado que foi lido do storage ["Hello storage! :D"]
*                printf("%s\n", read_buffer);
*            }
*/
typedef struct
{
    fn_callback_storage_init init;
    fn_callback_storage_write write;
    fn_callback_storage_read read;
}storage_t;

/*!******************************************************************* 
*   @brief Inicializa o sistema de arquivos para que possa ser usado
*          para armazenar dados cruciais da aplicação / dispositivo.
*   @param[in] verification Se verdadeiro, ao inicializar o sistema,
*              essa função irá fazer um tratamento da memória, 
*              identificando possíveis erros, se Falso, a etapa de 
*              verificação será pulada.
*   @note É importante estar ciente que a verificação demanda uma 
*         quantidade de tempo. Logo, é importante garantir o uso
*         correto do parametro de verificação.
*   @return storage_init_sucess em caso de sucesso  
            ou storage_init_error em caso de falha na inicialização.
**********************************************************************/
storage_ret init_storage(bool verification);

/*!********************************************************************** 
*   @brief Salva no sistema de arquivo o valor atribuido como parametro
*   @param[in] data O dado a ser salvo no sistema de arquivo
*   @param[in] partition_label A partição onde será armazenado o dado
*   @return storage_write_sucess em caso de escrita feita com sucesso ou
            storage_write_error em caso de falha na escrita.
************************************************************************/
storage_ret storage_write(const void *data, const char *partition_label);

/*!**********************************************************************
*   @brief Faz a leitura da partição repassada como parametro
*   @param[in] partition_label O valor a ser salvo no sistema de arquivo
*   @param[in] buffer O local onde será salvo o valor que foi resgatado da partição
*************************************************************************/
storage_ret storage_read(const char *partition_label, void *buffer, size_t read_size);

extern storage_t Storage;

#endif /* PROJECT_STORAGE_H */