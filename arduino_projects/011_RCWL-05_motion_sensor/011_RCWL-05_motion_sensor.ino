/*
  RCWL-0516 Motion Detection with Onboard LED
  Author: Rahul B.
  Version: 1.0
*/

const int sensorPin = 2;       // Sensor output connected to digital pin 2
const int ledPin = 13;         // Onboard LED pin

void setup() {
  pinMode(sensorPin, INPUT);   // Set sensor pin as input
  pinMode(ledPin, OUTPUT);     // Set LED pin as output
  Serial.begin(9600);          // Start serial communication for debugging
  Serial.println("RCWL-0516 Motion Sensor Initialized");
}

void loop() {
  int motion = digitalRead(sensorPin);  // Read sensor state

  if (motion == HIGH) {
    digitalWrite(ledPin, HIGH);         // Motion detected: Turn LED ON
    Serial.println("Motion detected");
    delay(2000); 
  } 
  else {
    digitalWrite(ledPin, LOW);          // No motion: Turn LED OFF
    Serial.println("No motion");
  }

  delay(100);  // Small delay to avoid flooding serial monitor
}
