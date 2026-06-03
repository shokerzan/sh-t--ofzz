#include <Arduino.h>

const int LED1_PIN = 2;
const int LED2_PIN = 4;

bool led1State = false;
bool led2State = false;

void setup()
{
  Serial.begin(9600);

  while (!Serial)
  {
    delay(10);
  }

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);

  Serial.println("ESP32系统启动啦");
  Serial.println("输入指令吧：");
  Serial.println("'1'-LED1变化 (GPIO2)");
  Serial.println("'2'-LED2变化 (GPIO4)");
  Serial.println("----Pray for you----");
}

void loop()
{
  if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil('\n');
    command.trim();

    Serial.print("接受指令：");
    Serial.println(command);

    // 接受命令
    if (command == "1")
    {
      led1State = !led1State;
      digitalWrite(LED1_PIN, led1State ? HIGH : LOW);

      // 反馈命令
      if (led1State)
      {
        Serial.println("LED1亮咯(GPIO2)");
      }
      else
      {
        Serial.println("LED1灭咯(GPIO2)");
      }
    }
    else if (command == "2")
    {
      led2State = !led2State;
      digitalWrite(LED2_PIN, led2State ? HIGH : LOW);

      // 接收命令
      if (led2State)
      {
        Serial.println("LED2亮咯(GPIO4)");
      }
      else
      {
        Serial.println("LED2灭咯(GPIO4)");
      }
    }
    else if (command != "1" && command != "2")
    {
      Serial.println("指令错误咯");
    }
  }
}