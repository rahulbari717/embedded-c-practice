// v1.1 - Rahul B.
// LDR with Relay Control
// Relay turns ON when below threshold AND LDR detects darkness

// --- Pin Definitions ---
#define LDR_PIN     A0        // Analog pin connected to LDR
#define RELAY1      2         // Relay control pin

const int LDR_DARK_THRESHOLD = 15;         // Lower values = darker (adjust as needed)

void setup() {
  Serial.begin(9600);
  
  // Setup pins
  pinMode(LDR_PIN, INPUT);
  pinMode(RELAY1, OUTPUT);
  
  // Ensure relay is off initially
  digitalWrite(RELAY1, LOW);

  Serial.println("🔧 System Initialized - Rahul B. v1.1");
}

void loop() {
  // --- Read LDR value ---
  int ldrValue = analogRead(LDR_PIN);

  // --- Debugging Output ---
  Serial.print("🌑 LDR: ");
  Serial.println(ldrValue);

  if (ldrValue < LDR_DARK_THRESHOLD) {
      digitalWrite(RELAY1, HIGH);
      Serial.println("✅ Object detected & Dark: Relay ON");
      Serial.println("✅ wait for 5 secs");
      delay(5000); 
    } 
    else {
      digitalWrite(RELAY1, LOW);
      Serial.println("ℹ️ Condition not met: Relay OFF");
    }

  delay(500);  // Wait 1 second
}
