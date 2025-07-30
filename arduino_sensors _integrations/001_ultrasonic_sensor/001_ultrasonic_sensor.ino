/*
  HC-SR04 Basic Demonstration
  HC-SR04-Basic-Demo.ino
  Demonstrates functions of HC-SR04 Ultrasonic Range Finder
  Displays results on Serial Monitor

  ✅ Features Implemented:
Only 1 LED on at a time, based on distance.

Uses 4 LEDs: White (≤10 cm), Yellow (≤20 cm), Blue (≤50 cm), Green (≤100 cm).

Serial debug messages show which LED is ON or "No LED ON".

*/

// This uses Serial Monitor to display Range Finder distance readings

// Hook up HC-SR04 with Trig to Arduino Pin 10, Echo to Arduino pin 13

#define trigPin     10
#define echoPin     13

#define WHITE_LED   7
#define YELLOW_LED  6
#define BLUE_LED    5
#define GREEN_LED   4

float duration, distance;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(WHITE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  // Turn all LEDs off at startup
  digitalWrite(WHITE_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  Serial.println("System Ready: Starting Ultrasonic Sensor...");

  
}
void loop() {
  // Trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo duration
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  distance = (duration / 2.0) * 0.0343;

  Serial.print("Measured Distance: ");
  if (distance >= 400 || distance <= 2) {
    Serial.println("Out of range");
    turnOffAllLEDs();
  } else {
    Serial.print(distance);
    Serial.println(" cm");

    // LED Logic - Only one LED ON at a time
    if (distance <= 5) {
      turnOnLED(WHITE_LED, "White");
    } else if (distance <= 10) {
      turnOnLED(YELLOW_LED, "Yellow");
    } else if (distance <= 15) {
      turnOnLED(BLUE_LED, "Blue");
    } else if (distance <= 20) {
      turnOnLED(GREEN_LED, "Green");
    } else {
      Serial.println("No LED condition met");
      turnOffAllLEDs();
    }
  }

  delay(500);  // Wait before next measurement
}

void turnOnLED(int ledPin, const char* color) {
  turnOffAllLEDs();  // Ensure only one LED is ON
  digitalWrite(ledPin, HIGH);
  Serial.print(color);
  Serial.println(" LED ON");
}

void turnOffAllLEDs() {
  digitalWrite(WHITE_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
}
