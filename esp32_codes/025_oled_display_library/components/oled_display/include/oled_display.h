#pragma once
#include "driver/i2c_master.h"
#include "esp_err.h"

// Display configurations
#define SSD1306_I2C_ADDR        (0x3C)
#define SSD1306_WIDTH           (128)
#define SSD1306_HEIGHT          (64)
#define SSD1306_PAGES           (8)

// Font types
typedef enum {
    FONT_SMALL,     // 5x8 font
    FONT_MEDIUM,    // 8x16 font (double height)
    FONT_LARGE      // 12x16 font
} oled_font_t;

// Text alignment
typedef enum {
    ALIGN_LEFT,
    ALIGN_CENTER,
    ALIGN_RIGHT
} oled_align_t;

// Display handle structure
typedef struct {
    i2c_master_dev_handle_t i2c_dev;
    uint8_t contrast;
    bool display_on;
} oled_handle_t;

// === Core Functions ===
esp_err_t oled_init(oled_handle_t *oled, i2c_master_dev_handle_t i2c_dev);
esp_err_t oled_deinit(oled_handle_t *oled);
void oled_clear(oled_handle_t *oled);
void oled_update(oled_handle_t *oled);
void oled_set_contrast(oled_handle_t *oled, uint8_t contrast);
void oled_display_on(oled_handle_t *oled, bool on);

// === Text Functions ===
void oled_draw_text(oled_handle_t *oled, int x, int y, const char *text, oled_font_t font);
void oled_draw_text_aligned(oled_handle_t *oled, int y, const char *text, oled_font_t font, oled_align_t align);
void oled_printf(oled_handle_t *oled, int x, int y, oled_font_t font, const char *format, ...);

// === Graphics Functions ===
void oled_set_pixel(oled_handle_t *oled, int x, int y, bool on);
void oled_draw_line(oled_handle_t *oled, int x0, int y0, int x1, int y1);
void oled_draw_rectangle(oled_handle_t *oled, int x, int y, int width, int height, bool filled);
void oled_draw_circle(oled_handle_t *oled, int cx, int cy, int radius, bool filled);

// === Special Functions ===
void oled_invert_display(oled_handle_t *oled, bool invert);
void oled_scroll_horizontal(oled_handle_t *oled, bool left, int start_page, int end_page, int speed);
void oled_stop_scroll(oled_handle_t *oled);

// === Utility Functions ===
int oled_get_text_width(const char *text, oled_font_t font);
int oled_get_font_height(oled_font_t font);