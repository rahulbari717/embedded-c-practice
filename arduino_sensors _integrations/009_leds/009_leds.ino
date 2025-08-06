// Define LED pins
const int ledPins[] = {8, 9, 10, 11};
const int numLeds = 4;

void setup() {
  // Set all LED pins as output
  
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);   // Turn on LED
    delay(1000);                       // Wait for 500ms
    digitalWrite(ledPins[i], LOW);    // Turn off LED
    delay(1000);                       // Small delay before next LED
  }
}
