// v1.1 - Rahul B.
// HC-SR04 Ultrasonic Sensor with Relay Control
// Relay turns ON when distance is below threshold AND LDR detects darkness

// --- Pin Definitions ---
#define trigPin     10        // Trigger pin of HC-SR04
#define echoPin     13        // Echo pin of HC-SR04
#define LDR_PIN     A0        // Analog pin connected to LDR
#define RELAY1      2         // Relay control pin

// --- Distance & Thresholds ---
float duration, distance;
const float DISTANCE_THRESHOLD_CM = 100.0;  // Trigger if object is closer than this
const int LDR_DARK_THRESHOLD = 15;         // Lower values = darker (adjust as needed)

void setup() {
  Serial.begin(9600);
  
  // Setup pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(RELAY1, OUTPUT);
  
  // Ensure relay is off initially
  digitalWrite(RELAY1, LOW);

  Serial.println("🔧 System Initialized - Rahul B. v1.1");
}

void loop() {
  // --- Trigger ultrasonic pulse ---
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // --- Read echo time ---
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2.0) * 0.0343;

  // --- Read LDR value ---
  int ldrValue = analogRead(LDR_PIN);

  // --- Debugging Output ---
  Serial.print("📏 Distance: ");
  Serial.print(distance);
  Serial.print(" cm\t");

  Serial.print(" LDR: ");
  Serial.println(ldrValue);

  // --- Check range validity ---
  if (distance >= 400 || distance <= 2) {
    Serial.println("⚠️ Distance out of range. Relay OFF");
    digitalWrite(RELAY1, LOW);
  } 
  else {
    // --- Decision: Turn relay ON if close and dark ---
    if (distance <= DISTANCE_THRESHOLD_CM && ldrValue < LDR_DARK_THRESHOLD) {
      digitalWrite(RELAY1, HIGH);
      Serial.println("✅ Object detected & Dark: Relay ON");
    } 
    else {
      digitalWrite(RELAY1, LOW);
      Serial.println("ℹ️ Condition not met: Relay OFF");
    }
  }

  delay(1000);  // Wait 1 second
}
