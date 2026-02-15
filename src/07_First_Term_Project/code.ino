#include <ArduinoBLE.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

/* ---------- DHT11 ---------- */
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

/* ---------- LEDs ---------- */
#define BLUE_LED_PIN 4     // Blue LED on D4
#define GREEN_LED_PIN 5    // Green LED on D5
#define RED_LED_PIN 8      // Red LED on D8 (NEW)

/* ---------- LCD ---------- */
LiquidCrystal_I2C lcd(0x27, 16, 2);
char degree = 223;

/* ---------- BLE Nordic UART ---------- */
#define UART_SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define UART_RX_UUID      "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define UART_TX_UUID      "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

BLEService uartService(UART_SERVICE_UUID);

BLEStringCharacteristic rxChar(
  UART_RX_UUID,
  BLEWrite | BLEWriteWithoutResponse,
  40
);

BLEStringCharacteristic txChar(
  UART_TX_UUID,
  BLENotify,
  40
);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  /* LEDs */
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  digitalWrite(BLUE_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);

  /* LCD */
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Starting...");

  /* DHT */
  dht.begin();

  /* BLE */
  if (!BLE.begin()) {
    Serial.println("BLE failed");
    while (1);
  }

  BLE.setLocalName("UNO_R4_BLE");
  BLE.setAdvertisedService(uartService);

  uartService.addCharacteristic(rxChar);
  uartService.addCharacteristic(txChar);
  BLE.addService(uartService);

  txChar.writeValue("Ready");
  BLE.advertise();

  lcd.clear();
  lcd.print("BLE Ready");

  Serial.println("BLE UART ready");
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.println("Phone connected");
    lcd.clear();
    lcd.print("Phone connected");

    while (central.connected()) {
      if (rxChar.written()) {
        String cmd = rxChar.value();
        cmd.trim();
        cmd.toLowerCase();

        Serial.print("Received: ");
        Serial.println(cmd);

        /* ----- TEMPERATURE ----- */
        if (cmd == "what is the temperature") {
          handleTemperatureCommand();
        }

        /* ----- GREEN LED ----- */
        else if (cmd == "turn on green led") {
          digitalWrite(GREEN_LED_PIN, HIGH);
          lcd.clear();
          lcd.print("Green LED ON");
          txChar.writeValue("Green LED ON");
        }
        else if (cmd == "turn off green led") {
          digitalWrite(GREEN_LED_PIN, LOW);
          lcd.clear();
          lcd.print("Green LED OFF");
          txChar.writeValue("Green LED OFF");
        }

        /* ----- BLUE LED ----- */
        else if (cmd == "turn on blue led") {
          digitalWrite(BLUE_LED_PIN, HIGH);
          lcd.clear();
          lcd.print("Blue LED ON");
          txChar.writeValue("Blue LED ON");
        }
        else if (cmd == "turn off blue led") {
          digitalWrite(BLUE_LED_PIN, LOW);
          lcd.clear();
          lcd.print("Blue LED OFF");
          txChar.writeValue("Blue LED OFF");
        }

        /* ----- RED LED (NEW) ----- */
        else if (cmd == "turn on red led") {
          digitalWrite(RED_LED_PIN, HIGH);
          lcd.clear();
          lcd.print("Red LED ON");
          txChar.writeValue("Red LED ON");
        }
        else if (cmd == "turn off red led") {
          digitalWrite(RED_LED_PIN, LOW);
          lcd.clear();
          lcd.print("Red LED OFF");
          txChar.writeValue("Red LED OFF");
        }

        /* ----- ALL LEDs (UPDATED) ----- */
        else if (cmd == "turn on all leds") {
          digitalWrite(GREEN_LED_PIN, HIGH);
          digitalWrite(BLUE_LED_PIN, HIGH);
          digitalWrite(RED_LED_PIN, HIGH);
          lcd.clear();
          lcd.print("All LEDs ON");
          txChar.writeValue("All LEDs ON");
        }
        else if (cmd == "turn off all leds") {
          digitalWrite(GREEN_LED_PIN, LOW);
          digitalWrite(BLUE_LED_PIN, LOW);
          digitalWrite(RED_LED_PIN, LOW);
          lcd.clear();
          lcd.print("All LEDs OFF");
          txChar.writeValue("All LEDs OFF");
        }
        else if (cmd == "disco") {
          discoMode();
        }
        /* ----- UNKNOWN ----- */
        else {
          txChar.writeValue("Unknown command");
          lcd.clear();
          lcd.print("Unknown command");
        }
      }
    }

    Serial.println("Phone disconnected");
    lcd.clear();
    lcd.print("Disconnected");
  }
}

/* ---------- TEMPERATURE HANDLER ---------- */
void handleTemperatureCommand() {
  float temp = dht.readTemperature();

  if (isnan(temp)) {
    lcd.clear();
    lcd.print("Sensor error");
    txChar.writeValue("Sensor error");
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");

  lcd.setCursor(0, 1);
  lcd.print(temp, 1);
  lcd.print((char)223);
  lcd.print("C");

  String response = "Temperature is " + String(temp, 1) + " °C";
  txChar.writeValue(response.c_str());
}
/* Disco command */
void discoMode() {
  lcd.clear();
  lcd.print("DISCO MODE!");
  txChar.writeValue("Disco mode started");

  for (int i = 0; i < 10; i++) {   // number of disco cycles
    digitalWrite(RED_LED_PIN, HIGH);
    delay(150);
    digitalWrite(RED_LED_PIN, LOW);

    digitalWrite(BLUE_LED_PIN, HIGH);
    delay(100);
    digitalWrite(BLUE_LED_PIN, LOW);

    digitalWrite(GREEN_LED_PIN, HIGH);
    delay(200);
    digitalWrite(GREEN_LED_PIN, LOW);

    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, HIGH);
    delay(120);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
  }

  lcd.clear();
  lcd.print("Disco finished");
  txChar.writeValue("Disco finished");

  // Make sure all LEDs are OFF at the end
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
}
