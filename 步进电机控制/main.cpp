#include <Arduino.h>

const int pin1 = 26;
const int pin2 = 27;
const int pin3 = 14;
const int pin4 = 12;

const int stepsPerRevolution = 2048;

int rotationSpeed = 2;

void setup()
{
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);

  Serial.begin(115200);
  Serial.println("步进电机控制初始化完成");
}

void stepMotor(int step)
{
  switch (step)
  {
  case 0:
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin4, HIGH);
    break;

  case 1:
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin4, LOW);
    break;

  case 2:
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
    break;

  case 3:
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, HIGH);
    break;
  }
}

// 顺时针
void rotateClockwise(int steps)
{
  for (int i = 0; i < steps; i++)
  {
    stepMotor(i % 4);
    delay(rotationSpeed);
  }
}

// 逆时针
void rotateCounterClockwise(int steps)
{
  for (int i = 0; i < steps; i++)
  {
    stepMotor((3 - (i % 4)));
    delay(rotationSpeed);
  }
}

void loop()
{
  Serial.println("步进电机顺时针旋转一周...");
  rotateClockwise(stepsPerRevolution);
  delay(1000);

  Serial.println("步进电机逆时针旋转一周...");
  rotateCounterClockwise(stepsPerRevolution);
  delay(1000);
}
