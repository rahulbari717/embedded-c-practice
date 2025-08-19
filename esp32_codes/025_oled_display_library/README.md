# ESP32 OLED Display Library

A comprehensive OLED display library for ESP32 with SSD1306 controller support.

## Features

- 📝 **Multiple Font Sizes**: Small (5x8), Medium (10x16), Large (12x16) fonts
- 🎨 **Graphics Functions**: Lines, rectangles, circles, pixels
- 📐 **Text Alignment**: Left, center, right alignment
- 📊 **Printf Support**: Format strings directly to display
- 🌀 **Scrolling Effects**: Horizontal scrolling with speed control
- 🔆 **Display Control**: Contrast, invert, on/off
- 🎯 **Easy API**: Simple function calls for complex operations

## Hardware Setup

### Connections
| ESP32 Pin | OLED Pin | Description |
|-----------|----------|-------------|
| GPIO 21   | SDA      | I2C Data    |
| GPIO 22   | SCL      | I2C Clock   |
| 3.3V      | VCC      | Power       |
| GND       | GND      | Ground      |

### Supported Displays
- SSD1306 128x64 OLED displays
- I2C interface (0x3C or 0x3D address)

## Project Structure

```
your_project/
├── main/
│   ├── main.c
│   └── CMakeLists.txt
├── components/
│   └── oled_display/
│       ├── include/
│       │   └── oled_display.h
│       ├── oled_display.c
│       └── CMakeLists.txt
├── CMakeLists.txt
└── README.md
```

## Installation

1. **Copy library files** to your ESP32 project:
   ```bash
   mkdir -p components/oled_display/include
   # Copy oled_display.h to components/oled_display/include/
   # Copy oled_display.c to components/oled_display/
   ```

2. **Create component CMakeLists.txt**:
   ```cmake
   # components/oled_display/CMakeLists.txt
   idf_component_register(
       SRCS "oled_display.c"
       INCLUDE_DIRS "include"
       REQUIRES "driver"
   )
   ```

3. **Update main CMakeLists.txt**:
   ```cmake
   # main/CMakeLists.txt
   idf_component_register(
       SRCS "main.c"
       INCLUDE_DIRS "."
       REQUIRES "oled_display"
   )
   ```

## Quick Start

### Basic Usage

```c
#include "oled_display.h"

// Global variables
static oled_handle_t oled;
static i2c_master_dev_handle_t dev_handle;

void app_main(void) {
    // Initialize I2C (your existing I2C setup)
    // ... i2c initialization code ...
    
    // Initialize OLED
    oled_init(&oled, dev_handle);
    
    // Clear display and draw text
    oled_clear(&oled);
    oled_draw_text(&oled, 0, 0, "Hello World!", FONT_SMALL);
    oled_update(&oled);
    
    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
```

## API Reference

### Core Functions

```c
// Initialize OLED display
esp_err_t oled_init(oled_handle_t *oled, i2c_master_dev_handle_t i2c_dev);

// Clear display buffer
void oled_clear(oled_handle_t *oled);

// Update display with buffer content
void oled_update(oled_handle_t *oled);

// Set display contrast (0-255)
void oled_set_contrast(oled_handle_t *oled, uint8_t contrast);

// Turn display on/off
void oled_display_on(oled_handle_t *oled, bool on);
```

### Text Functions

```c
// Draw text at specific position
void oled_draw_text(oled_handle_t *oled, int x, int y, const char *text, oled_font_t font);

// Draw aligned text
void oled_draw_text_aligned(oled_handle_t *oled, int y, const char *text, oled_font_t font, oled_align_t align);

// Printf-style text formatting
void oled_printf(oled_handle_t *oled, int x, int y, oled_font_t font, const char *format, ...);
```

### Graphics Functions

```c
// Set individual pixel
void oled_set_pixel(oled_handle_t *oled, int x, int y, bool on);

// Draw line
void oled_draw_line(oled_handle_t *oled, int x0, int y0, int x1, int y1);

// Draw rectangle (filled or outline)
void oled_draw_rectangle(oled_handle_t *oled, int x, int y, int width, int height, bool filled);

// Draw circle (filled or outline)
void oled_draw_circle(oled_handle_t *oled, int cx, int cy, int radius, bool filled);
```

### Special Effects

```c
// Invert display colors
void oled_invert_display(oled_handle_t *oled, bool invert);

// Start horizontal scrolling
void oled_scroll_horizontal(oled_handle_t *oled, bool left, int start_page, int end_page, int speed);

// Stop scrolling
void oled_stop_scroll(oled_handle_t *oled);
```

## Font Types

- **FONT_SMALL**: 5x8 pixels, standard ASCII characters
- **FONT_MEDIUM**: 10x16 pixels, double-height small font
- **FONT_LARGE**: 12x16 pixels, numbers only (0-9)

## Text Alignment

- **ALIGN_LEFT**: Left-aligned text
- **ALIGN_CENTER**: Center-aligned text  
- **ALIGN_RIGHT**: Right-aligned text

## Examples

### Display Sensor Data
```c
float temperature = 25.4;
int humidity = 65;

oled_clear(&oled);
oled_printf(&oled, 0, 0, FONT_SMALL, "Temperature:");
oled_printf(&oled, 0, 12, FONT_MEDIUM, "%.1f C", temperature);
oled_printf(&oled, 0, 32, FONT_SMALL, "Humidity: %d%%", humidity);
oled_update(&oled);
```

### Create Progress Bar
```c
int progress = 75; // 75%
oled_clear(&oled);
oled_draw_text(&oled, 0, 0, "Loading...", FONT_SMALL);
oled_draw_rectangle(&oled, 0, 20, 128, 10, false);  // Border
oled_draw_rectangle(&oled, 2, 22, (progress * 124) / 100, 6, true);  // Fill
oled_printf(&oled, 0, 40, FONT_SMALL, "%d%% Complete", progress);
oled_update(&oled);
```

### Dashboard Display
```c
oled_clear(&oled);
oled_draw_text_aligned(&oled, 0, "ESP32 Status", FONT_SMALL, ALIGN_CENTER);
oled_draw_line(&oled, 0, 10, 127, 10);
oled_printf(&oled, 0, 15, FONT_SMALL, "CPU: %d%%", cpu_usage);
oled_printf(&oled, 0, 25, FONT_SMALL, "Memory: %d KB", memory_free);
oled_printf(&oled, 0, 35, FONT_SMALL, "WiFi: Connected");
oled_update(&oled);
```
## 🚀 How to use in your projects:
```c// Simple usage example
oled_handle_t oled;

// Initialize (after I2C setup)
oled_init(&oled, dev_handle);

// Use anywhere in your code
oled_clear(&oled);
oled_printf(&oled, 0, 0, FONT_SMALL, "Temp: %.1f°C", temperature);
oled_draw_text_aligned(&oled, 20, "ESP32 Project", FONT_MEDIUM, ALIGN_CENTER);
oled_draw_rectangle(&oled, 10, 40, 100, 8, false); // Progress bar border
oled_update(&oled); // Always call this to refresh display
```

## Troubleshooting

### Display not working?
1. Check I2C connections (SDA/SCL)
2. Verify power supply (3.3V, not 5V)
3. Try different I2C address (0x3C or 0x3D)
4. Check I2C pullup resistors

### Text not displaying?
1. Ensure `oled_update()` is called after drawing
2. Check font bounds (characters 32-127 supported)
3. Verify coordinates are within display bounds

### Performance issues?
1. Increase I2C frequency to 400kHz
2. Minimize `oled_update()` calls
3. Use buffered drawing (draw all, then update once)

## License

This library is open source and available under the MIT License.

## Contributing

Feel free to submit issues and pull requests to improve this library!