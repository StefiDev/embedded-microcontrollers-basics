int red = 12;
int blue = 7;
int btn = 13;

int pressCount = 0;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(btn, INPUT_PULLUP); 
}


void mode1() {
  digitalWrite(red, HIGH);
  digitalWrite(blue, HIGH);
  delay(1000);
  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  delay(1000);
}

void mode2() {
  digitalWrite(red, HIGH);
  digitalWrite(blue, HIGH);
  delay(200);
  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  delay(200);
  digitalWrite(red, HIGH);
  delay(200);
  digitalWrite(red, LOW);
}

void mode3() {
  digitalWrite(red, HIGH);
  delay(200);
  digitalWrite(red, LOW);
  delay(200);
  digitalWrite(blue, HIGH);
  delay(200);
  digitalWrite(blue, LOW);
  delay(200);
}

void loop() {
  int reading = digitalRead(btn);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW) {
      pressCount++;
      if (pressCount > 3) {
        pressCount = 1;
      }
      while (digitalRead(btn) == LOW);
      delay(50);
    }
  }

  lastButtonState = reading;

  switch (pressCount) {
    case 1:
      mode1();
      break;
    case 2:
      mode2();
      break;
    case 3:
      mode3();
      break;
    default:
      digitalWrite(red, LOW);
      digitalWrite(blue, LOW);
      break;
  }
}