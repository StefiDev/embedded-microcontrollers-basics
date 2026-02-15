// --- DISPLAY SLAVE (CS 5) ---
#include <Adafruit_NeoPixel.h>

#define MISO_PIN 10
#define SCK_PIN  11
#define MOSI_PIN 12
#define CS_PIN   5    // UNIQUE PIN

#define PIXEL_PIN 6
#define NUMPIXELS 12

Adafruit_NeoPixel ring(NUMPIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(MOSI_PIN, INPUT);
  pinMode(SCK_PIN, INPUT);
  pinMode(CS_PIN, INPUT);
  // We do not set MISO as output because we only receive data
  
  ring.begin();
  ring.setBrightness(255);
  ring.show();
}

byte slaveRx() {
  byte data = 0;
  for (int i = 7; i >= 0; i--) {
    while (digitalRead(SCK_PIN) == LOW) 
    {
      if (digitalRead(CS_PIN) == HIGH) 
      {
        return 0;
      }
    }
    
    if (digitalRead(MOSI_PIN) == HIGH) data |= (1 << i);
    while (digitalRead(SCK_PIN) == HIGH);
  }
  return data;
}

void loop() {
  if (digitalRead(CS_PIN) == LOW) {
    // Master sends 2 bytes: [Color] then [Pixels]
    byte colorCode = slaveRx();
    byte numPixels = slaveRx();
    
    uint32_t color;
    if (colorCode == 1)      color = ring.Color(0, 0, 255);   // Blue
    else if (colorCode == 2) color = ring.Color(0, 255, 0);   // Green
    else                     color = ring.Color(255, 0, 0);   // Red
    
    ring.clear();
    for(int i=0; i<numPixels; i++) {
      if(i < NUMPIXELS) ring.setPixelColor(i, color);
    }
    ring.show();
    
    while (digitalRead(CS_PIN) == LOW);
  }
}