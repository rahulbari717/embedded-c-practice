const int led = 9;        // Led positive terminal to the digital pin 9.              
const int sensor = 2;     // signal pin of sensor to digital pin 2.               
int state = LOW;          // Remove 'const' - this needs to change            
int val = 0;              // Remove 'const' - this needs to change                 
void setup() {
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  Serial.begin(9600);        // initialize serial
}

void loop(){
  
  val = digitalRead(sensor);   // read sensor value
  serial.println()
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led, HIGH);   // turn LED ON
    delay(1000);                // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
      digitalWrite(led, LOW); // turn LED OFF
      delay(2000);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }
}
