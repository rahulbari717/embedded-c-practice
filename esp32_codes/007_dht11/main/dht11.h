#ifndef DHT11_H
#define DHT11_H

#include "driver/gpio.h"
#include "esp_err.h"

void dht11_init(gpio_num_t gpio);

esp_err_t dht11_read(gpio_num_t pin, int *humidity, int *temperature);

#endif // DHT11_H
