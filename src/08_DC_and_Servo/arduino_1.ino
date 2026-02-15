#include <SoftwareSerial.h>

SoftwareSerial link(5, 6);

const int potPin = A0;
const int buttonPin = 2;

bool lastButtonState = HIGH;
int motorState = 1;
int direction = 1;

int lastAngle = -1;
const int threshold = 3;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  link.begin(2400);
}

void loop() {

  // ===== SERVO CONTROL =====
  int potValue = analogRead(potPin);
  int angle = map(potValue, 0, 1023, 0, 180);

  if (abs(angle - lastAngle) > threshold) {

    Serial.print("S:");
    Serial.println(angle);

    link.print("S:");
    link.println(angle);

    lastAngle = angle;
  }

  // ===== BUTTON CONTROL =====
  int buttonState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && buttonState == LOW) {

    motorState += direction;

    if (motorState == 0) {
      direction = 1;
    }
    else if (motorState == 2) {
      direction = -1;
    }

    Serial.print("M:");
    Serial.println(motorState);

    link.print("M:");
    link.println(motorState);

    delay(250);
  }

  lastButtonState = buttonState;
  delay(20);
}
