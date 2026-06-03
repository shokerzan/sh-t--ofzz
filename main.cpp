#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 22, 21);

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("开始初始化128x32 OLED...");
  
  Wire.begin(21, 22);
  u8g2.begin();
  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(10, 20, "damn!");
  u8g2.sendBuffer();
  
  Serial.println("显示完成");
}

void loop() {
}