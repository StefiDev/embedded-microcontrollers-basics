// --- MASTER CODE ---
// Pins: MISO=10, SCK=11, MOSI=12
// CS: Temp=7, Light=6, Display=5

#define MISO_PIN 10
#define SCK_PIN  11
#define MOSI_PIN 12

#define CS_TEMP    7
#define CS_LIGHT   6
#define CS_DISPLAY 5

void setup() {
  Serial.begin(9600);
  
  pinMode(MISO_PIN, INPUT_PULLUP);
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  
  pinMode(CS_TEMP, OUTPUT);
  pinMode(CS_LIGHT, OUTPUT);
  pinMode(CS_DISPLAY, OUTPUT);

  // Initialize all CS to HIGH (Inactive)
  digitalWrite(CS_TEMP, HIGH);
  digitalWrite(CS_LIGHT, HIGH);
  digitalWrite(CS_DISPLAY, HIGH);
  digitalWrite(SCK_PIN, LOW);
  
  Serial.println("System Started: Master");
}

// Function to send 1 byte and receive 1 byte
byte spiTransfer(byte dataOut) {
  byte dataIn = 0;
  for (int i = 7; i >= 0; i--) {
    // 1. Set MOSI
    if ((dataOut >> i) & 1) digitalWrite(MOSI_PIN, HIGH);
    else                    digitalWrite(MOSI_PIN, LOW);
    
    // 2. Clock High
    digitalWrite(SCK_PIN, HIGH);
    delayMicroseconds(100); // Slow for stability

    // 3. Read MISO
    if (digitalRead(MISO_PIN) == HIGH) {
      dataIn |= (1 << i);
    }

    // 4. Clock Low
    digitalWrite(SCK_PIN, LOW);
    delayMicroseconds(100);
  }
  return dataIn;
}

void loop() {
  // --- 1. POLL TEMP SENSOR (CS 7) ---
  digitalWrite(CS_TEMP, LOW);
  delayMicroseconds(200);
  
  spiTransfer(0x01); // Command "Send Data"
  
  // *** CHANGE THIS DELAY ***
  delay(10); // Wait 10 milliseconds (This is HUGE, but guarantees Slave is ready)
  
  byte rawTemp = spiTransfer(0x00); // Read Data
  digitalWrite(CS_TEMP, HIGH);

  // Conversion Logic
  float tempC = ((rawTemp * 4.0) * 0.00488 - 0.5) * 100;
  
  Serial.print("Temp: "); Serial.print(tempC); 
  
  delay(100);

  // --- 2. POLL LIGHT SENSOR (CS 6) ---
  digitalWrite(CS_LIGHT, LOW);
  delayMicroseconds(200);
  spiTransfer(0x01); // Command
  byte rawLight = spiTransfer(0x00); // Read Data
  digitalWrite(CS_LIGHT, HIGH);
  
  Serial.print(" C | Light: ");
  Serial.println(rawLight);
  
  delay(100);

  // --- 3. UPDATE DISPLAY (CS 5) ---
  // Logic: Color based on Temp
  byte colorCode = 2; // Default Green
  if (tempC < 15) colorCode = 1; // Blue
  else if (tempC > 28) colorCode = 3; // Red

  // Logic: Pixels based on Light (Map 0-255 to 1-12)
  byte numPixels = map(rawLight, 0, 242, 1, 12);

  digitalWrite(CS_DISPLAY, LOW);
  delayMicroseconds(200);
  spiTransfer(colorCode); // Send Color
  spiTransfer(numPixels); // Send Amount
  digitalWrite(CS_DISPLAY, HIGH);

  delay(1000); // Loop delay
}