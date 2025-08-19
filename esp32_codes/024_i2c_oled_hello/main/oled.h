#pragma once
#include "driver/i2c_master.h"
#include "esp_err.h"

#define SSD1306_I2C_ADDR        (0x3C)
#define SSD1306_WIDTH           (128)
#define SSD1306_HEIGHT          (64)

esp_err_t ssd1306_init(i2c_master_dev_handle_t dev);
void ssd1306_clear(i2c_master_dev_handle_t dev);
void ssd1306_draw_text(i2c_master_dev_handle_t dev, int row, int col, const char *text);
