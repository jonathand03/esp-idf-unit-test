//
// Created by johnl on 2/4/2024.
//

#ifndef ESP_NEW_TEST_PROJECT_I2C_H
#define ESP_NEW_TEST_PROJECT_I2C_H
#include "driver/i2c.h"

/*!*********************************************************************************************
 * @brief Essa função tem como objetivo fazer a inicialização do I2C no ESP32
 * Seguindo os padrões de velocidade, foi optado pela velocidade de 100KHz, porem pode ser
 * aumentado para até 400KHz modificando o define SCL_SPEED
 * @param[in] i2c_gpio_sda É o pino referente ao SDA do barramento I2C
 * @param[in] i2c_gpio_scl É o pino referente ao SCL do barramento I2C
 * @param[in] i2c_scl_speed É a velocidade que o SLC vai funcioar
 **********************************************************************************************/
void i2c_init(int i2c_gpio_sda,int i2c_gpio_scl, int i2c_scl_speed);

/*!*********************************************************************************************
 * @brief Essa função tem como objetivo escrever um dado no barramento i2c,
 * para o endereço de dispositivo repassado como parametro
 * @param[in] data é o dado que será enviado para o dispositivo
 * @param[in] device_address é o endereço do dispositivo que irá receber o dado
***********************************************************************************************/
void i2c_write(int *data, int device_address);

/*!*********************************************************************************************
 * @brief Essa função tem como objetivo fazer a leitura de dados  no barramento i2c,
 * do  endereço de dispositivo repassado como parametro para um buffer repassado como parametro
 * @param[in] device_address é o endereço do dispositivo que irá receber o dado
 * @param[in] buffer é o local onde será armazenado o dado capturado (caso exista)
 **********************************************************************************************/
void i2c_read(int device_address, const void *buffer);

#endif //ESP_NEW_TEST_PROJECT_I2C_H
