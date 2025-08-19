#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "oled_display.h"
#include "esp_log.h"

#define I2C_MASTER_SCL_IO           (22)
#define I2C_MASTER_SDA_IO           (21)
#define I2C_MASTER_PORT             (0)
#define I2C_MASTER_FREQ_HZ          (400000) // Increased to 400kHz for better performance

static const char *TAG = "OLED_DEMO";
static i2c_master_bus_handle_t bus_handle;
static i2c_master_dev_handle_t dev_handle;
static oled_handle_t oled;

static void i2c_master_init(void)
{
    ESP_LOGI(TAG, "Initializing I2C master...");
    
    i2c_master_bus_config_t bus_cfg = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_MASTER_PORT,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_cfg, &bus_handle));

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = SSD1306_I2C_ADDR,
        .scl_speed_hz = I2C_MASTER_FREQ_HZ,
    };
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle));
    
    ESP_LOGI(TAG, "I2C master initialized successfully");
}

// Demo functions
void demo_basic_text(void) {
    ESP_LOGI(TAG, "Demo: Basic Text");
    
    oled_clear(&oled);
    oled_draw_text(&oled, 0, 0, "Small Font", FONT_SMALL);
    oled_draw_text(&oled, 0, 16, "Medium", FONT_MEDIUM);
    oled_draw_text(&oled, 0, 40, "123", FONT_LARGE);
    oled_update(&oled);
    
    vTaskDelay(pdMS_TO_TICKS(3000));
}

void demo_alignment(void) {
    ESP_LOGI(TAG, "Demo: Text Alignment");
    
    oled_clear(&oled);
    oled_draw_text_aligned(&oled, 0, "LEFT", FONT_SMALL, ALIGN_LEFT);
    oled_draw_text_aligned(&oled, 12, "CENTER", FONT_SMALL, ALIGN_CENTER);
    oled_draw_text_aligned(&oled, 24, "RIGHT", FONT_SMALL, ALIGN_RIGHT);
    
    // Draw alignment guides
    oled_draw_line(&oled, 0, 36, 127, 36);
    oled_draw_line(&oled, 63, 0, 63, 63);
    
    oled_update(&oled);
    vTaskDelay(pdMS_TO_TICKS(3000));
}

void demo_printf(void) {
    ESP_LOGI(TAG, "Demo: Printf functionality");
    
    int counter = 0;
    float temperature = 23.5;
    
    for (int i = 0; i < 10; i++) {
        oled_clear(&oled);
        oled_printf(&oled, 0, 0, FONT_SMALL, "Counter: %d", counter++);
        oled_printf(&oled, 0, 12, FONT_SMALL, "Temp: %.1f C", temperature);
        oled_printf(&oled, 0, 24, FONT_SMALL, "Time: %02d:%02d", i / 60, i % 60);
        
        // Progress bar
        int progress = (i * 100) / 9;
        oled_draw_rectangle(&oled, 0, 40, 128, 8, false);
        oled_draw_rectangle(&oled, 2, 42, (progress * 124) / 100, 4, true);
        oled_printf(&oled, 0, 52, FONT_SMALL, "Progress: %d%%", progress);
        
        oled_update(&oled);
        vTaskDelay(pdMS_TO_TICKS(500));
        
        temperature += 0.1;
    }
}

void demo_graphics(void) {
    ESP_LOGI(TAG, "Demo: Graphics");
    
    oled_clear(&oled);
    
    // Draw shapes
    oled_draw_rectangle(&oled, 10, 10, 20, 15, false);
    oled_draw_rectangle(&oled, 35, 10, 15, 15, true);
    
    oled_draw_circle(&oled, 70, 17, 8, false);
    oled_draw_circle(&oled, 90, 17, 6, true);
    
    // Draw lines
    oled_draw_line(&oled, 0, 35, 127, 35);
    oled_draw_line(&oled, 0, 40, 30, 60);
    oled_draw_line(&oled, 30, 40, 60, 60);
    oled_draw_line(&oled, 60, 40, 90, 60);
    oled_draw_line(&oled, 90, 40, 127, 60);
    
    oled_update(&oled);
    vTaskDelay(pdMS_TO_TICKS(3000));
}

void demo_scroll(void) {
    ESP_LOGI(TAG, "Demo: Scrolling");
    
    oled_clear(&oled);
    oled_draw_text(&oled, 0, 0, "Scrolling Demo", FONT_SMALL);
    oled_draw_text(&oled, 0, 16, "Right to Left", FONT_SMALL);
    oled_draw_text(&oled, 0, 32, "ESP32 OLED", FONT_MEDIUM);
    oled_update(&oled);
    
    vTaskDelay(pdMS_TO_TICKS(1000));
    
    // Start scrolling
    oled_scroll_horizontal(&oled, true, 0, 7, 0); // Left scroll, all pages, fastest
    vTaskDelay(pdMS_TO_TICKS(5000));
    
    oled_stop_scroll(&oled);
    vTaskDelay(pdMS_TO_TICKS(1000));
    
    // Scroll right
    oled_scroll_horizontal(&oled, false, 0, 7, 2); // Right scroll, slower
    vTaskDelay(pdMS_TO_TICKS(3000));
    
    oled_stop_scroll(&oled);
}

void demo_contrast_brightness(void) {
    ESP_LOGI(TAG, "Demo: Contrast Control");
    
    oled_clear(&oled);
    oled_draw_text_aligned(&oled, 20, "Contrast Demo", FONT_SMALL, ALIGN_CENTER);
    oled_update(&oled);
    
    // Fade out
    for (int contrast = 255; contrast >= 0; contrast -= 15) {
        oled_set_contrast(&oled, contrast);
        oled_printf(&oled, 0, 40, FONT_SMALL, "Level: %d  ", contrast);
        oled_update(&oled);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
    
    vTaskDelay(pdMS_TO_TICKS(500));
    
    // Fade in
    for (int contrast = 0; contrast <= 255; contrast += 15) {
        oled_set_contrast(&oled, contrast);
        oled_printf(&oled, 0, 40, FONT_SMALL, "Level: %d  ", contrast);
        oled_update(&oled);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void demo_invert(void) {
    ESP_LOGI(TAG, "Demo: Display Invert");
    
    oled_clear(&oled);
    oled_draw_text_aligned(&oled, 20, "Normal Display", FONT_SMALL, ALIGN_CENTER);
    oled_update(&oled);
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    oled_invert_display(&oled, true);
    oled_clear(&oled);
    oled_draw_text_aligned(&oled, 20, "Inverted Display", FONT_SMALL, ALIGN_CENTER);
    oled_update(&oled);
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    oled_invert_display(&oled, false);
}

void demo_dashboard(void) {
    ESP_LOGI(TAG, "Demo: Dashboard");
    
    for (int i = 0; i < 20; i++) {
        oled_clear(&oled);
        
        // Title
        oled_draw_text_aligned(&oled, 0, "ESP32 Dashboard", FONT_SMALL, ALIGN_CENTER);
        oled_draw_line(&oled, 0, 10, 127, 10);
        
        // Simulated sensor data
        int cpu_usage = 45 + (i * 2) % 40;
        int memory_free = 75 - (i % 30);
        int wifi_strength = 80 + (i % 20);
        
        // CPU Usage bar
        oled_draw_text(&oled, 0, 14, "CPU:", FONT_SMALL);
        oled_draw_rectangle(&oled, 30, 14, 80, 6, false);
        oled_draw_rectangle(&oled, 32, 16, (cpu_usage * 76) / 100, 2, true);
        oled_printf(&oled, 112, 14, FONT_SMALL, "%d%%", cpu_usage);
        
        // Memory bar
        oled_draw_text(&oled, 0, 24, "MEM:", FONT_SMALL);
        oled_draw_rectangle(&oled, 30, 24, 80, 6, false);
        oled_draw_rectangle(&oled, 32, 26, (memory_free * 76) / 100, 2, true);
        oled_printf(&oled, 112, 24, FONT_SMALL, "%d%%", memory_free);
        
        // WiFi strength
        oled_draw_text(&oled, 0, 34, "WiFi:", FONT_SMALL);
        for (int bar = 0; bar < 5; bar++) {
            if ((wifi_strength * 5) / 100 > bar) {
                oled_draw_rectangle(&oled, 35 + bar * 8, 34 + (4 - bar) * 2, 4, 6 - (4 - bar) * 2, true);
            } else {
                oled_draw_rectangle(&oled, 35 + bar * 8, 34 + (4 - bar) * 2, 4, 6 - (4 - bar) * 2, false);
            }
        }
        oled_printf(&oled, 80, 34, FONT_SMALL, "%d dBm", -20 - (100 - wifi_strength) / 2);
        
        // Status
        oled_draw_text(&oled, 0, 44, "Status: Running", FONT_SMALL);
        oled_printf(&oled, 0, 54, FONT_SMALL, "Uptime: %02d:%02d:%02d", i/3600, (i%3600)/60, i%60);
        
        oled_update(&oled);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "Starting OLED Display Library Demo");
    
    // Initialize I2C
    i2c_master_init();
    
    // Initialize OLED
    esp_err_t ret = oled_init(&oled, dev_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize OLED: %s", esp_err_to_name(ret));
        return;
    }
    
    ESP_LOGI(TAG, "OLED initialized successfully");
    
    // Welcome message
    oled_clear(&oled);
    oled_draw_text_aligned(&oled, 20, "OLED Library", FONT_MEDIUM, ALIGN_CENTER);
    oled_draw_text_aligned(&oled, 40, "Demo Ready!", FONT_SMALL, ALIGN_CENTER);
    oled_update(&oled);
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    // Run demos in loop
    while (1) {
        demo_basic_text();
        demo_alignment();
        demo_printf();
        demo_graphics();
        demo_scroll();
        demo_contrast_brightness();
        demo_invert();
        demo_dashboard();
        
        // Short pause before restarting
        oled_clear(&oled);
        oled_draw_text_aligned(&oled, 20, "Demo Complete", FONT_SMALL, ALIGN_CENTER);
        oled_draw_text_aligned(&oled, 35, "Restarting...", FONT_SMALL, ALIGN_CENTER);
        oled_update(&oled);
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}