#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 10);
int led = 7;
int pot = A0;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(2400);

  Serial.println("Executor ready!");
}

void loop() {

  int adc = analogRead(pot);
  int brightness = map(adc, 0, 1023, 0, 255);
  mySerial.println(brightness);

  if (mySerial.available()) {
    String msg = mySerial.readStringUntil('\n');
    int btnState = msg.toInt();

    digitalWrite(led, btnState);

    Serial.print("Received button state: ");
    Serial.println(btnState);
  }

  delay(50);
}
