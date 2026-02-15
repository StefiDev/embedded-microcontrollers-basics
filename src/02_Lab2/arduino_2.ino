// C++ code
//
int led_pin = 9;
int potPin = A0;
void setup()
{
  pinMode(led_pin, OUTPUT);

}

void loop()
{
  int potValue = analogRead(potPin);
   
  int brightness = map(potValue, 0, 1023, 0, 255);
  
  analogWrite(led_pin, brightness);
  delay(10);
}