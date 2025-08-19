#include "oled_display.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

// Display buffer
static uint8_t display_buffer[SSD1306_WIDTH * SSD1306_PAGES];

// Small 5x8 font (ASCII 32-127)
static const uint8_t font_small[][5] = {
    {0x00,0x00,0x00,0x00,0x00}, // Space (32)
    {0x00,0x00,0x5F,0x00,0x00}, // ! (33)
    {0x00,0x07,0x00,0x07,0x00}, // " (34)
    {0x14,0x7F,0x14,0x7F,0x14}, // # (35)
    {0x24,0x2A,0x7F,0x2A,0x12}, // $ (36)
    {0x23,0x13,0x08,0x64,0x62}, // % (37)
    {0x36,0x49,0x55,0x22,0x50}, // & (38)
    {0x00,0x05,0x03,0x00,0x00}, // ' (39)
    {0x00,0x1C,0x22,0x41,0x00}, // ( (40)
    {0x00,0x41,0x22,0x1C,0x00}, // ) (41)
    {0x14,0x08,0x3E,0x08,0x14}, // * (42)
    {0x08,0x08,0x3E,0x08,0x08}, // + (43)
    {0x00,0x50,0x30,0x00,0x00}, // , (44)
    {0x08,0x08,0x08,0x08,0x08}, // - (45)
    {0x00,0x60,0x60,0x00,0x00}, // . (46)
    {0x20,0x10,0x08,0x04,0x02}, // / (47)
    {0x3E,0x51,0x49,0x45,0x3E}, // 0 (48)
    {0x00,0x42,0x7F,0x40,0x00}, // 1 (49)
    {0x42,0x61,0x51,0x49,0x46}, // 2 (50)
    {0x21,0x41,0x45,0x4B,0x31}, // 3 (51)
    {0x18,0x14,0x12,0x7F,0x10}, // 4 (52)
    {0x27,0x45,0x45,0x45,0x39}, // 5 (53)
    {0x3C,0x4A,0x49,0x49,0x30}, // 6 (54)
    {0x01,0x71,0x09,0x05,0x03}, // 7 (55)
    {0x36,0x49,0x49,0x49,0x36}, // 8 (56)
    {0x06,0x49,0x49,0x29,0x1E}, // 9 (57)
    {0x00,0x36,0x36,0x00,0x00}, // : (58)
    {0x00,0x56,0x36,0x00,0x00}, // ; (59)
    {0x08,0x14,0x22,0x41,0x00}, // < (60)
    {0x14,0x14,0x14,0x14,0x14}, // = (61)
    {0x00,0x41,0x22,0x14,0x08}, // > (62)
    {0x02,0x01,0x51,0x09,0x06}, // ? (63)
    {0x32,0x49,0x79,0x41,0x3E}, // @ (64)
    {0x7E,0x11,0x11,0x11,0x7E}, // A (65)
    {0x7F,0x49,0x49,0x49,0x36}, // B (66)
    {0x3E,0x41,0x41,0x41,0x22}, // C (67)
    {0x7F,0x41,0x41,0x22,0x1C}, // D (68)
    {0x7F,0x49,0x49,0x49,0x41}, // E (69)
    {0x7F,0x09,0x09,0x09,0x01}, // F (70)
    {0x3E,0x41,0x49,0x49,0x7A}, // G (71)
    {0x7F,0x08,0x08,0x08,0x7F}, // H (72)
    {0x00,0x41,0x7F,0x41,0x00}, // I (73)
    {0x20,0x40,0x41,0x3F,0x01}, // J (74)
    {0x7F,0x08,0x14,0x22,0x41}, // K (75)
    {0x7F,0x40,0x40,0x40,0x40}, // L (76)
    {0x7F,0x02,0x0C,0x02,0x7F}, // M (77)
    {0x7F,0x04,0x08,0x10,0x7F}, // N (78)
    {0x3E,0x41,0x41,0x41,0x3E}, // O (79)
    {0x7F,0x09,0x09,0x09,0x06}, // P (80)
    {0x3E,0x41,0x51,0x21,0x5E}, // Q (81)
    {0x7F,0x09,0x19,0x29,0x46}, // R (82)
    {0x46,0x49,0x49,0x49,0x31}, // S (83)
    {0x01,0x01,0x7F,0x01,0x01}, // T (84)
    {0x3F,0x40,0x40,0x40,0x3F}, // U (85)
    {0x1F,0x20,0x40,0x20,0x1F}, // V (86)
    {0x3F,0x40,0x38,0x40,0x3F}, // W (87)
    {0x63,0x14,0x08,0x14,0x63}, // X (88)
    {0x07,0x08,0x70,0x08,0x07}, // Y (89)
    {0x61,0x51,0x49,0x45,0x43}, // Z (90)
    {0x00,0x7F,0x41,0x41,0x00}, // [ (91)
    {0x02,0x04,0x08,0x10,0x20}, // \ (92)
    {0x00,0x41,0x41,0x7F,0x00}, // ] (93)
    {0x04,0x02,0x01,0x02,0x04}, // ^ (94)
    {0x40,0x40,0x40,0x40,0x40}, // _ (95)
    {0x00,0x01,0x02,0x04,0x00}, // ` (96)
    {0x20,0x54,0x54,0x54,0x78}, // a (97)
    {0x7F,0x48,0x44,0x44,0x38}, // b (98)
    {0x38,0x44,0x44,0x44,0x20}, // c (99)
    {0x38,0x44,0x44,0x48,0x7F}, // d (100)
    {0x38,0x54,0x54,0x54,0x18}, // e (101)
    {0x08,0x7E,0x09,0x01,0x02}, // f (102)
    {0x0C,0x52,0x52,0x52,0x3E}, // g (103)
    {0x7F,0x08,0x04,0x04,0x78}, // h (104)
    {0x00,0x44,0x7D,0x40,0x00}, // i (105)
    {0x20,0x40,0x44,0x3D,0x00}, // j (106)
    {0x7F,0x10,0x28,0x44,0x00}, // k (107)
    {0x00,0x41,0x7F,0x40,0x00}, // l (108)
    {0x7C,0x04,0x18,0x04,0x78}, // m (109)
    {0x7C,0x08,0x04,0x04,0x78}, // n (110)
    {0x38,0x44,0x44,0x44,0x38}, // o (111)
    {0x7C,0x14,0x14,0x14,0x08}, // p (112)
    {0x08,0x14,0x14,0x18,0x7C}, // q (113)
    {0x7C,0x08,0x04,0x04,0x08}, // r (114)
    {0x48,0x54,0x54,0x54,0x20}, // s (115)
    {0x04,0x3F,0x44,0x40,0x20}, // t (116)
    {0x3C,0x40,0x40,0x20,0x7C}, // u (117)
    {0x1C,0x20,0x40,0x20,0x1C}, // v (118)
    {0x3C,0x40,0x30,0x40,0x3C}, // w (119)
    {0x44,0x28,0x10,0x28,0x44}, // x (120)
    {0x0C,0x50,0x50,0x50,0x3C}, // y (121)
    {0x44,0x64,0x54,0x4C,0x44}, // z (122)
    {0x00,0x08,0x36,0x41,0x00}, // { (123)
    {0x00,0x00,0x7F,0x00,0x00}, // | (124)
    {0x00,0x41,0x36,0x08,0x00}, // } (125)
    {0x10,0x08,0x08,0x10,0x08}, // ~ (126)
    {0x00,0x00,0x00,0x00,0x00}  // DEL (127)
};

// Large 8x16 font for numbers (0-9)
static const uint8_t font_large_numbers[][16] = {
    // 0
    {0x00,0x7C,0xC6,0xC6,0xC6,0xD6,0xD6,0xD6,0xD6,0xC6,0xC6,0xC6,0x7C,0x00,0x00,0x00},
    // 1  
    {0x00,0x18,0x38,0x78,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x7E,0x00,0x00,0x00},
    // 2
    {0x00,0x7C,0xC6,0x06,0x0C,0x18,0x30,0x60,0xC0,0xC6,0xC6,0xC6,0xFE,0x00,0x00,0x00},
    // 3
    {0x00,0x7C,0xC6,0x06,0x06,0x3C,0x06,0x06,0x06,0x06,0xC6,0xC6,0x7C,0x00,0x00,0x00},
    // 4
    {0x00,0x0C,0x1C,0x3C,0x6C,0xCC,0xFE,0x0C,0x0C,0x0C,0x0C,0x0C,0x1E,0x00,0x00,0x00},
    // 5
    {0x00,0xFE,0xC0,0xC0,0xC0,0xFC,0x06,0x06,0x06,0x06,0xC6,0xC6,0x7C,0x00,0x00,0x00},
    // 6
    {0x00,0x38,0x60,0xC0,0xC0,0xFC,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00,0x00,0x00},
    // 7
    {0x00,0xFE,0xC6,0x06,0x06,0x0C,0x18,0x30,0x30,0x30,0x30,0x30,0x30,0x00,0x00,0x00},
    // 8
    {0x00,0x7C,0xC6,0xC6,0xC6,0x7C,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00,0x00,0x00},
    // 9
    {0x00,0x7C,0xC6,0xC6,0xC6,0xC6,0xC6,0x7E,0x06,0x06,0x0C,0x18,0x70,0x00,0x00,0x00}
};

// Private functions
static esp_err_t oled_cmd(oled_handle_t *oled, uint8_t cmd) {
    uint8_t buffer[2] = {0x00, cmd};
    return i2c_master_transmit(oled->i2c_dev, buffer, sizeof(buffer), -1);
}

static void oled_send_buffer(oled_handle_t *oled) {
    for (int page = 0; page < SSD1306_PAGES; page++) {
        oled_cmd(oled, 0xB0 + page);  // Set page
        oled_cmd(oled, 0x00);         // Set lower column
        oled_cmd(oled, 0x10);         // Set higher column
        
        uint8_t buffer[SSD1306_WIDTH + 1];
        buffer[0] = 0x40; // Data control byte
        memcpy(&buffer[1], &display_buffer[page * SSD1306_WIDTH], SSD1306_WIDTH);
        
        i2c_master_transmit(oled->i2c_dev, buffer, sizeof(buffer), -1);
    }
}

// Public API Implementation

esp_err_t oled_init(oled_handle_t *oled, i2c_master_dev_handle_t i2c_dev) {
    if (!oled) return ESP_ERR_INVALID_ARG;
    
    oled->i2c_dev = i2c_dev;
    oled->contrast = 0x7F;
    oled->display_on = true;
    
    // Clear buffer
    memset(display_buffer, 0, sizeof(display_buffer));
    
    // Initialize display
    uint8_t init_cmds[] = {
        0xAE,       // Display OFF
        0x20, 0x00, // Memory mode: Horizontal
        0xB0,       // Page 0
        0xC8,       // COM scan direction
        0x00, 0x10, // Column start
        0x40,       // Start line
        0x81, 0x7F, // Contrast
        0xA1,       // Segment remap
        0xA6,       // Normal display
        0xA8, 0x3F, // Multiplex ratio
        0xA4,       // Display follows RAM
        0xD3, 0x00, // Display offset
        0xD5, 0x80, // Clock divide
        0xD9, 0xF1, // Pre-charge
        0xDA, 0x12, // COM pins
        0xDB, 0x40, // VCOM detect
        0x8D, 0x14, // Charge pump
        0xAF        // Display ON
    };
    
    for (int i = 0; i < sizeof(init_cmds); i++) {
        esp_err_t ret = oled_cmd(oled, init_cmds[i]);
        if (ret != ESP_OK) return ret;
    }
    
    return ESP_OK;
}

esp_err_t oled_deinit(oled_handle_t *oled) {
    if (!oled) return ESP_ERR_INVALID_ARG;
    return oled_cmd(oled, 0xAE); // Display OFF
}

void oled_clear(oled_handle_t *oled) {
    if (!oled) return;
    memset(display_buffer, 0, sizeof(display_buffer));
}

void oled_update(oled_handle_t *oled) {
    if (!oled) return;
    oled_send_buffer(oled);
}

void oled_set_contrast(oled_handle_t *oled, uint8_t contrast) {
    if (!oled) return;
    oled->contrast = contrast;
    oled_cmd(oled, 0x81);
    oled_cmd(oled, contrast);
}

void oled_display_on(oled_handle_t *oled, bool on) {
    if (!oled) return;
    oled->display_on = on;
    oled_cmd(oled, on ? 0xAF : 0xAE);
}

void oled_set_pixel(oled_handle_t *oled, int x, int y, bool on) {
    if (!oled || x < 0 || x >= SSD1306_WIDTH || y < 0 || y >= SSD1306_HEIGHT) return;
    
    int page = y / 8;
    int bit = y % 8;
    int index = page * SSD1306_WIDTH + x;
    
    if (on) {
        display_buffer[index] |= (1 << bit);
    } else {
        display_buffer[index] &= ~(1 << bit);
    }
}

void oled_draw_text(oled_handle_t *oled, int x, int y, const char *text, oled_font_t font) {
    if (!oled || !text) return;
    
    int cursor_x = x;
    
    switch (font) {
        case FONT_SMALL:
            while (*text && cursor_x < SSD1306_WIDTH - 5) {
                char c = *text;
                if (c < 32 || c > 127) c = 32;
                
                for (int col = 0; col < 5; col++) {
                    uint8_t column_data = font_small[c - 32][col];
                    for (int row = 0; row < 8; row++) {
                        if (column_data & (1 << row)) {
                            oled_set_pixel(oled, cursor_x + col, y + row, true);
                        }
                    }
                }
                cursor_x += 6; // 5 pixels + 1 space
                text++;
            }
            break;
            
        case FONT_MEDIUM:
            // Double height small font
            while (*text && cursor_x < SSD1306_WIDTH - 5) {
                char c = *text;
                if (c < 32 || c > 127) c = 32;
                
                for (int col = 0; col < 5; col++) {
                    uint8_t column_data = font_small[c - 32][col];
                    for (int row = 0; row < 8; row++) {
                        if (column_data & (1 << row)) {
                            oled_set_pixel(oled, cursor_x + col, y + row * 2, true);
                            oled_set_pixel(oled, cursor_x + col, y + row * 2 + 1, true);
                        }
                    }
                }
                cursor_x += 6;
                text++;
            }
            break;
            
        case FONT_LARGE:
            // Large numbers only
            while (*text && cursor_x < SSD1306_WIDTH - 8) {
                char c = *text;
                if (c >= '0' && c <= '9') {
                    int digit = c - '0';
                    for (int col = 0; col < 8; col++) {
                        for (int row = 0; row < 16; row++) {
                            if (font_large_numbers[digit][row] & (1 << (7 - col))) {
                                oled_set_pixel(oled, cursor_x + col, y + row, true);
                            }
                        }
                    }
                }
                cursor_x += 10;
                text++;
            }
            break;
    }
}

void oled_draw_text_aligned(oled_handle_t *oled, int y, const char *text, oled_font_t font, oled_align_t align) {
    if (!oled || !text) return;
    
    int text_width = oled_get_text_width(text, font);
    int x = 0;
    
    switch (align) {
        case ALIGN_LEFT:
            x = 0;
            break;
        case ALIGN_CENTER:
            x = (SSD1306_WIDTH - text_width) / 2;
            break;
        case ALIGN_RIGHT:
            x = SSD1306_WIDTH - text_width;
            break;
    }
    
    oled_draw_text(oled, x, y, text, font);
}

void oled_printf(oled_handle_t *oled, int x, int y, oled_font_t font, const char *format, ...) {
    if (!oled || !format) return;
    
    char buffer[128];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    oled_draw_text(oled, x, y, buffer, font);
}

void oled_draw_line(oled_handle_t *oled, int x0, int y0, int x1, int y1) {
    if (!oled) return;
    
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    
    while (true) {
        oled_set_pixel(oled, x0, y0, true);
        
        if (x0 == x1 && y0 == y1) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void oled_draw_rectangle(oled_handle_t *oled, int x, int y, int width, int height, bool filled) {
    if (!oled) return;
    
    if (filled) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                oled_set_pixel(oled, x + i, y + j, true);
            }
        }
    } else {
        // Top and bottom lines
        for (int i = 0; i < width; i++) {
            oled_set_pixel(oled, x + i, y, true);
            oled_set_pixel(oled, x + i, y + height - 1, true);
        }
        // Left and right lines
        for (int j = 0; j < height; j++) {
            oled_set_pixel(oled, x, y + j, true);
            oled_set_pixel(oled, x + width - 1, y + j, true);
        }
    }
}

void oled_draw_circle(oled_handle_t *oled, int cx, int cy, int radius, bool filled) {
    if (!oled) return;
    
    int x = 0;
    int y = radius;
    int d = 1 - radius;
    
    while (x <= y) {
        if (filled) {
            for (int i = cx - x; i <= cx + x; i++) {
                oled_set_pixel(oled, i, cy + y, true);
                oled_set_pixel(oled, i, cy - y, true);
            }
            for (int i = cx - y; i <= cx + y; i++) {
                oled_set_pixel(oled, i, cy + x, true);
                oled_set_pixel(oled, i, cy - x, true);
            }
        } else {
            oled_set_pixel(oled, cx + x, cy + y, true);
            oled_set_pixel(oled, cx - x, cy + y, true);
            oled_set_pixel(oled, cx + x, cy - y, true);
            oled_set_pixel(oled, cx - x, cy - y, true);
            oled_set_pixel(oled, cx + y, cy + x, true);
            oled_set_pixel(oled, cx - y, cy + x, true);
            oled_set_pixel(oled, cx + y, cy - x, true);
            oled_set_pixel(oled, cx - y, cy - x, true);
        }
        
        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

void oled_invert_display(oled_handle_t *oled, bool invert) {
    if (!oled) return;
    oled_cmd(oled, invert ? 0xA7 : 0xA6);
}

void oled_scroll_horizontal(oled_handle_t *oled, bool left, int start_page, int end_page, int speed) {
    if (!oled) return;
    
    // Speed values: 0-7 (0=5 frames, 1=64 frames, 2=128 frames, 3=256 frames, 4=3 frames, 5=4 frames, 6=25 frames, 7=2 frames)
    uint8_t speed_table[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    uint8_t actual_speed = (speed < 8) ? speed_table[speed] : 0x00;
    
    if (left) {
        oled_cmd(oled, 0x27); // Left horizontal scroll
    } else {
        oled_cmd(oled, 0x26); // Right horizontal scroll
    }
    oled_cmd(oled, 0x00);           // Dummy byte
    oled_cmd(oled, start_page);     // Start page
    oled_cmd(oled, actual_speed);   // Time interval
    oled_cmd(oled, end_page);       // End page
    oled_cmd(oled, 0x00);           // Dummy byte
    oled_cmd(oled, 0xFF);           // Dummy byte
    oled_cmd(oled, 0x2F);           // Activate scroll
}

void oled_stop_scroll(oled_handle_t *oled) {
    if (!oled) return;
    oled_cmd(oled, 0x2E); // Deactivate scroll
}

int oled_get_text_width(const char *text, oled_font_t font) {
    if (!text) return 0;
    
    int width = 0;
    int len = strlen(text);
    
    switch (font) {
        case FONT_SMALL:
        case FONT_MEDIUM:
            width = len * 6; // 5 pixels + 1 space per character
            break;
        case FONT_LARGE:
            width = len * 10; // 8 pixels + 2 space per character
            break;
    }
    
    return width;
}

int oled_get_font_height(oled_font_t font) {
    switch (font) {
        case FONT_SMALL:
            return 8;
        case FONT_MEDIUM:
            return 16;
        case FONT_LARGE:
            return 16;
        default:
            return 8;
    }
}