#include <Wire.h>

#define SLAVE_ADDRESS 8
#define POT_PIN A1

byte potValue = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS); 
  Wire.onRequest(sendData);
  Serial.println("Slave Started - Waiting...");
}

void loop() {
  potValue = map(analogRead(POT_PIN), 0, 1023, 0, 255);
  delay(100);
}

void sendData() {
  Wire.write(potValue);
  Serial.print("Sent to Master: ");
  Serial.println(potValue);
}