#include <SoftwareSerial.h>
#include <Servo.h>

// ===== SOFTWARE SERIAL =====
SoftwareSerial link(5, 6);

// ===== SERVO =====
Servo myServo;
const int servoPin = 10;

// ===== DC MOTOR =====
const int enA = 9;
const int in1 = 8;
const int in2 = 7;

void setup() {
  Serial.begin(9600);
  link.begin(2400);

  myServo.attach(servoPin);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  Serial.println("Executor READY");
}

void loop() {
  if (link.available()) {
    char c = link.read();

    Serial.print("RX char: ");
    Serial.println(c);

    // ===== SERVO =====
	if (c == 'S') {
  	  int angle = link.parseInt();
      myServo.write(angle);
	}

    // ===== MOTOR =====
    if (c == 'M') {
      char colon = link.read();
      int state = link.parseInt();

      Serial.print("Motor state received: ");
      Serial.println(state);

      if (state == 1) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        analogWrite(enA, 0);
        Serial.println("Motor STOPPED");
      }
      else if (state == 2) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(enA, 50);
        Serial.println("Motor RUNNING");
      }
      else {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(enA, 50);
        Serial.println("Motor RUNNING");
      }
    }
  }
}
