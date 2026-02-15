#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 10);
int btn = 2;
int led = 9;

bool lastBtn = HIGH;   
bool ledState = false;

void setup() {
  pinMode(btn, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(2400);

  Serial.println("Controller ready!");
}

void loop() {

  int btnState = digitalRead(btn);

  if (btnState == LOW && lastBtn == HIGH) {
    ledState = !ledState;
    mySerial.println(ledState);

    delay(200);
  }
  lastBtn = btnState;


  if (mySerial.available()) {
    int brightness = mySerial.parseInt();
    analogWrite(led, brightness);
    Serial.print("Potentiometer: ");
    Serial.println(brightness);
  }
}
