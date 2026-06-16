#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

// OLED配置 
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// 步进电机引脚 
const int pin1 = 32;
const int pin2 = 33;
const int pin3 = 25;
const int pin4 = 26;

//步进电机参数
const int stepsPerRevolution = 2048;
const float anglePerStep = 360.0 / stepsPerRevolution;
const float targetAngle = 36;
const int stepsPerMove = (int)(targetAngle / anglePerStep);
int rotationSpeed = 2;

//计数器
int moveCount = 0; 
int totalAngle = 0; 

void updateOLED();
void stepMotor(int step);
void rotateClockwise(int steps);
void doFlip();

void setup()
{
  // 步进电机
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);

  Serial.begin(115200);
  Serial.println("步进电机控制初始化完成");

  // OLED
  Serial.begin(115200);
  Serial.println("程序启动");
  delay(1000);
  Wire.begin(23,22);
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.sendBuffer();

  updateOLED();  
  delay(2000);

  Serial.println("显示完成");
}

//步进电机控制
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

void rotateClockwise(int steps)
{
  for (int i = 0; i < steps; i++)
  {
    stepMotor(i % 4);
    delay(rotationSpeed);
  }
}

// OLED
void updateOLED()
{
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_logisoso20_tf);
  u8g2.setCursor(20, 14);
  u8g2.print("TIMER");

  u8g2.setFont(u8g2_font_logisoso20_tf);
  u8g2.setCursor(25, 32);
  u8g2.print(moveCount);

  u8g2.setFont(u8g2_font_logisoso20_tf);
  u8g2.setCursor(70, 32);
  u8g2.print("s");

  u8g2.sendBuffer();
}

void doFlip()
{
  moveCount++;
  totalAngle += targetAngle;

  updateOLED();

  rotateClockwise(stepsPerMove);

  delay(1000);
}


void loop()
{
  doFlip();
}