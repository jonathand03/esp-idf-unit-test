#ifndef PROJECT_GPIO_H
#define PROJECT_GPIO_H

#include "driver/gpio.h"

#define OUTPUT  (GPIO_MODE_OUTPUT)
#define INPUT   (GPIO_MODE_INPUT)

typedef enum
{
    LOW,
    HIGH
}gpio_level_t;

typedef void (*fn_callback_gpio_init)(int gpio_num,gpio_mode_t gpio_set_direction);
typedef void (*fn_callback_gpio_write)(int gpio_num,gpio_level_t gpio_level);
typedef int  (*fn_callback_gpio_read)(int gpio_num);

typedef struct
{
    fn_callback_gpio_init  init;
    fn_callback_gpio_write write;
    fn_callback_gpio_read  read;
}gpio_project_t;

extern gpio_project_t Gpio;

#endif /* PROJECT_GPIO_H */