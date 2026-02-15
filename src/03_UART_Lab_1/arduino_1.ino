#include <SoftwareSerial.h>

SoftwareSerial link(2, 3);

unsigned long lastSend = 0;

void setup() {
  Serial.begin(9600);
  link.begin(2400);
  Serial.println("Ready");
}

void loop() {
  if (millis() - lastSend > 2000) {
    lastSend = millis();
    link.println("HELLO");
    Serial.println("[Controller] Sent: HELLO");
  }

  if (link.available()) {
    String msg = link.readStringUntil('\n');
    Serial.print("[Controller] Received: ");
    Serial.println(msg);
  }
}
