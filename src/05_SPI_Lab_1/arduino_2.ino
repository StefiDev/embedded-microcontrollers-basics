// --- SLAVE CODE (Temp Sensor) ---
#define MISO_PIN 10
#define MOSI_PIN 12
#define SCK_PIN  11
#define CS_PIN   7
#define TMP36    A0

// Variable to store the latest temp reading
byte tempToSend = 0;

void setup() {
  pinMode(MISO_PIN, OUTPUT);
  pinMode(MOSI_PIN, INPUT);
  pinMode(SCK_PIN, INPUT);
  pinMode(CS_PIN, INPUT);
  pinMode(TMP36, INPUT);

  digitalWrite(MISO_PIN, LOW);
}

// Function to receive (Command)
byte slaveRx() {
  byte data = 0;
  for (int i = 7; i >= 0; i--) {
    // Wait for Rising Edge (Data Read)
    while (digitalRead(SCK_PIN) == LOW) {
      if (digitalRead(CS_PIN) == HIGH) return 0; // Emergency Reset
    }
    if (digitalRead(MOSI_PIN) == HIGH) data |= (1 << i);
    
    // Wait for Falling Edge
    while (digitalRead(SCK_PIN) == HIGH);
  }
  return data;
}

// Function to transmit (Data)
void slaveTx(byte data) {
  for (int i = 7; i >= 0; i--) {
    // Write data bit BEFORE Master raises clock
    if ((data >> i) & 1) digitalWrite(MISO_PIN, HIGH);
    else                 digitalWrite(MISO_PIN, LOW);
    
    // Wait for Rising Edge (Master Reads here)
    while (digitalRead(SCK_PIN) == LOW) {
       if (digitalRead(CS_PIN) == HIGH) {
         digitalWrite(MISO_PIN, LOW); return; // Emergency Reset
       }
    }
    
    // Wait for Falling Edge
    while (digitalRead(SCK_PIN) == HIGH);
  }
  digitalWrite(MISO_PIN, LOW); // Release line
}

void loop() {
  // 1. While CS is HIGH (Master is busy with others), read the sensor continuously
  if (digitalRead(CS_PIN) == HIGH) {
     int raw = analogRead(TMP36);
     // Prepare the byte now, so we don't waste time later
     tempToSend = raw >> 2; 
  }  
  // 2. If CS goes LOW, we are selected
  else {
    // A. Receive the Command (0x01)
    byte cmd = slaveRx();
    
    // B. Send the data IMMEDIATELY (No analogRead here!)
    slaveTx(tempToSend);
    
    // C. Wait for CS to go HIGH to avoid re-triggering
    while (digitalRead(CS_PIN) == LOW);
  }
}