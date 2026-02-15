#include <SoftwareSerial.h>

SoftwareSerial link(2, 3);
String suffix = "-No26";

void setup() {
  Serial.begin(9600);
  link.begin(2400);
  Serial.println("Ready");
}

void loop() {
  if (link.available()) {
    String msg = link.readStringUntil('\n');
    Serial.print("[Executor] Received: ");
    Serial.println(msg);
    link.println(msg + suffix);
    Serial.print("[Executor] Sent back: ");
    Serial.println(msg + suffix);
  }
}
