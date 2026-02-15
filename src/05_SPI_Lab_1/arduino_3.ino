// --- LIGHT SLAVE (CS 6) ---
#define MISO_PIN 10
#define SCK_PIN  11
#define MOSI_PIN 12
#define CS_PIN   6    // UNIQUE PIN
#define PHOTO    A0

void setup() {
  pinMode(MISO_PIN, OUTPUT);
  pinMode(MOSI_PIN, INPUT);
  pinMode(SCK_PIN, INPUT);
  pinMode(CS_PIN, INPUT);
  digitalWrite(MISO_PIN, LOW);
}

// Minimal RX function
byte slaveRx() {
  byte data = 0;
  for (int i = 7; i >= 0; i--) {
    while (digitalRead(SCK_PIN) == LOW) if(digitalRead(CS_PIN)==HIGH) return 0;
    if (digitalRead(MOSI_PIN) == HIGH) data |= (1 << i);
    while (digitalRead(SCK_PIN) == HIGH);
  }
  return data;
}

// Minimal TX function
void slaveTx(byte data) {
  for (int i = 7; i >= 0; i--) {
    if ((data >> i) & 1) digitalWrite(MISO_PIN, HIGH);
    else                 digitalWrite(MISO_PIN, LOW);
    while (digitalRead(SCK_PIN) == LOW) if(digitalRead(CS_PIN)==HIGH){digitalWrite(MISO_PIN,LOW);return;}
    while (digitalRead(SCK_PIN) == HIGH);
  }
  digitalWrite(MISO_PIN, LOW);
}

void loop() {
  if (digitalRead(CS_PIN) == LOW) {
    byte cmd = slaveRx(); // Wait for command
    
    int raw = analogRead(PHOTO);
    byte lightByte = map(raw, 0, 1023, 0, 255); // Map to byte
    
    slaveTx(lightByte);
    
    while (digitalRead(CS_PIN) == LOW);
  }
}