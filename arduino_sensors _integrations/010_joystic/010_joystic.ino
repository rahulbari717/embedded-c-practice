/*
 * Joystick Directional LED Control - Accurate & Responsive
 * 
 * Functionality:
 * - Reads analog joystick X and Y values.
 * - Lights up one of four LEDs based on direction:
 *      LEFT  → D8
 *      RIGHT → D9
 *      UP    → D10
 *      DOWN  → D11
 * - Built-in LED (D13) lights up when the joystick switch is pressed.
 * 
 * Hardware Connections:
 * - Joystick X-axis  → A0
 * - Joystick Y-axis  → A1
 * - Joystick Switch  → D6
 * - LEDs             → D8 (LEFT), D9 (RIGHT), D10 (UP), D11 (DOWN)
 * - Built-in LED     → D13 (default onboard LED)
 */

#define BAUD_RATE         9600       // Serial communication baud rate

// Joystick input pins
#define JOYSTICK_X_PIN    A0
#define JOYSTICK_Y_PIN    A1
#define JOYSTICK_SW_PIN   6

// LED output pins
#define LED_LEFT_PIN      8
#define LED_RIGHT_PIN     9
#define LED_UP_PIN        10
#define LED_DOWN_PIN      11
#define LED_BUILTIN_PIN   13         // Onboard built-in LED

// Deadzone to filter out small joystick noise near center
#define JOYSTICK_DEADZONE 100

// Mapping range for joystick movement
#define JOYSTICK_MIN_VAL  0
#define JOYSTICK_MAX_VAL  1023
#define JOYSTICK_MAP_MIN -512
#define JOYSTICK_MAP_MAX  512

void setup() {
  // Initialize serial communication
  Serial.begin(BAUD_RATE);

  // Configure LED pins as outputs
  pinMode(LED_LEFT_PIN, OUTPUT);
  pinMode(LED_RIGHT_PIN, OUTPUT);
  pinMode(LED_UP_PIN, OUTPUT);
  pinMode(LED_DOWN_PIN, OUTPUT);
  pinMode(LED_BUILTIN_PIN, OUTPUT);

  // Configure joystick switch pin as input with pull-up
  pinMode(JOYSTICK_SW_PIN, INPUT_PULLUP);
}

void loop() {
  // Read joystick axis raw values
  int rawX = analogRead(JOYSTICK_X_PIN);
  int rawY = analogRead(JOYSTICK_Y_PIN);

  // Read joystick switch state
  bool isSwitchPressed = (digitalRead(JOYSTICK_SW_PIN) == LOW);

  // Map joystick values to -512 to +512 range
  int x = map(rawX, JOYSTICK_MIN_VAL, JOYSTICK_MAX_VAL, JOYSTICK_MAP_MIN, JOYSTICK_MAP_MAX);
  int y = map(rawY, JOYSTICK_MIN_VAL, JOYSTICK_MAX_VAL, JOYSTICK_MAP_MIN, JOYSTICK_MAP_MAX);

  // Apply deadzone
  if (abs(x) < JOYSTICK_DEADZONE) x = 0;
  if (abs(y) < JOYSTICK_DEADZONE) y = 0;

  // Debugging output (can be removed in production)
  Serial.print("X: "); Serial.print(x);
  Serial.print(" | Y: "); Serial.print(y);
  if (isSwitchPressed) Serial.print(" | Switch Pressed");
  Serial.println();

  // Turn off all LEDs initially
  digitalWrite(LED_LEFT_PIN, LOW);
  digitalWrite(LED_RIGHT_PIN, LOW);
  digitalWrite(LED_UP_PIN, LOW);
  digitalWrite(LED_DOWN_PIN, LOW);

  // Determine dominant direction and light corresponding LED
  if (x < 0 && abs(x) > abs(y)) {
    digitalWrite(LED_LEFT_PIN, HIGH);
  } else if (x > 0 && abs(x) > abs(y)) {
    digitalWrite(LED_RIGHT_PIN, HIGH);
  } else if (y > 0 && abs(y) > abs(x)) {
    digitalWrite(LED_UP_PIN, HIGH);
  } else if (y < 0 && abs(y) > abs(x)) {
    digitalWrite(LED_DOWN_PIN, HIGH);
  }

  // Turn on built-in LED if switch is pressed
  digitalWrite(LED_BUILTIN_PIN, isSwitchPressed ? HIGH : LOW);

  // Small delay for loop stability
  delay(100);
}
