#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SLAVE_ADDRESS 8
#define LCD_ADDRESS 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

byte receivedValue = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  lcd.init();
  lcd.backlight();
  
  Serial.println("Master Ready. Reading from slave");
  delay(2000);
}

void loop() {
  Wire.requestFrom(SLAVE_ADDRESS, 1);
  
  if (Wire.available()) {
    receivedValue = Wire.read();
    Serial.print("Received from slave: ");
    Serial.println(receivedValue);
    updateLCD(receivedValue);
  }
  
  delay(200);
}

void updateLCD(byte value) {
  float voltage = (value / 255.0) * 5.0;
  
  lcd.setCursor(0, 0);
  lcd.print("Pot Value: ");
  lcd.print(value);
  lcd.print(" ");
  
  lcd.setCursor(0, 1);
  lcd.print("Volt: ");
  lcd.print(voltage, 2);
  lcd.print("V");
}