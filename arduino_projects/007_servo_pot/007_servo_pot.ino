#include <Servo.h>

// Pin definitions
#define SERVO_PIN       9
#define ENCODER_CLK     2     // CLK pin (interrupt pin)
#define ENCODER_DT      3     // DT pin

// Create servo object
Servo myservo;

// Variables
volatile int encoderPos = 90;  // Start at 90 degrees
int lastEncoderPos = 90;
volatile boolean encoderFlag = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Servo + Rotary Encoder Control");
  
  // Initialize servo
  myservo.attach(SERVO_PIN);
  myservo.write(encoderPos);  // Set initial position
  
  // Initialize encoder pins
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  
  // Attach interrupt to CLK pin
  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), readEncoder, CHANGE);
  
  Serial.print("Initial position: ");
  Serial.println(encoderPos);
  Serial.println("Rotate encoder to control servo (0-180 degrees)");
}

void loop() {
  // Check if encoder position changed
  if (encoderFlag) {
    encoderFlag = false;
    
    // Only update servo if position actually changed
    if (encoderPos != lastEncoderPos) {
      myservo.write(encoderPos);
      
      Serial.print("Encoder: ");
      Serial.print(encoderPos);
      Serial.println(" degrees");
      
      lastEncoderPos = encoderPos;
    }
  }
  
  delay(10);  // Small delay for stability
}

// Interrupt function for reading encoder
void readEncoder() {
  static unsigned long lastTime = 0;
  
  // Simple debouncing
  if (millis() - lastTime > 5) {
    
    // Read both pins
    int clkState = digitalRead(ENCODER_CLK);
    int dtState = digitalRead(ENCODER_DT);
    
    // Determine direction
    if (clkState != dtState) {
      // Clockwise - increase position
      encoderPos++;
      if (encoderPos > 180) encoderPos = 180;  // Limit to 180
    } else {
      // Counter-clockwise - decrease position
      encoderPos--;
      if (encoderPos < 0) encoderPos = 0;  // Limit to 0
    }
    
    encoderFlag = true;  // Signal main loop
    lastTime = millis();
  }
}
