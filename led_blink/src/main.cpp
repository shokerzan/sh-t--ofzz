#include <Arduino.h>
int ledPins[] = {13, 12, 14, 27, 26 };

void setup()
{
  for (int i = 0; i <= 4; i++)
  {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void loop()
{
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(ledPins[i], HIGH);
    delay(150);
    digitalWrite(ledPins[i], LOW);
  }
}
