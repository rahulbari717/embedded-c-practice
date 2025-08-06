#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH      128   // OLED display width, in pixels
#define SCREEN_HEIGHT     64    // OLED display height, in pixels
#define OLED_RESET        -1    // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS    0x3C  // I2C address for 128x64 OLED
#define BAUDRATE          9600

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(BAUDRATE);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 initialization failed"));
    while (true); // Infinite loop on error
  }

  display.clearDisplay();               // Clear the buffer
  display.setTextSize(2);               // Set font size (2x scale)
  display.setTextColor(SSD1306_WHITE);  // Set text color to white

  display.setCursor(0, 0);              // Top-left corner
  display.println(F("Hello"));          // First line

  display.setCursor(0, 20);             // Y = 20 for second line with size 2 font
  display.println(F("Rahul"));          // Second line

  display.display();                    // Display the content
}

void loop() {
  // Nothing to do here
}
