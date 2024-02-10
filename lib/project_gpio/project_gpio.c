#include "project_gpio.h"

void gpio_init(int gpio_num,gpio_mode_t gpio_direction)
{
    gpio_set_direction(gpio_num,gpio_direction);
    printf("Porta inicializada com sucesso \n");
}

void gpio_write(int gpio_num,gpio_level_t gpio_level)
{
    gpio_set_level(gpio_num,gpio_level);
    printf("Escrevendo na porta %d \n", gpio_num);
}

int gpio_read(int gpio_num)
{
    printf("lendo na porta %d \n", gpio_num);
    return gpio_get_level(gpio_num);
}

gpio_project_t Gpio = 
{
    .init  =  gpio_init,
    .write =  gpio_write,
    .read  =  gpio_read
};