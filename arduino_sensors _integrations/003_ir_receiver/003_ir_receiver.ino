#include <IRremote.h>

const int RECV_PIN = 2;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR Receiver Ready");
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("Protocol: ");
    Serial.println(IrReceiver.decodedIRData.protocol);
    Serial.print("Command: ");
    Serial.println(IrReceiver.decodedIRData.command, HEX);
    IrReceiver.resume(); // ready to receive next
  }
}
