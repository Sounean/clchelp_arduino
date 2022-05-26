#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

int irSensorPin=7;  // 连接红外传感器引脚
bool irSensorOutput;  // 红外传感器输出信号

void setup() {
  pinMode(irSensorPin,INPUT); // 把第七个引脚做输入模式,这样可以读取连接在它上面的红外传感器的信号
  Serial.begin(9600); // 启动红外通讯
  Serial.println("Welcome");
}

void loop() {
  irSensorOutput = digitalRead(irSensorPin);  // 读取红外传感器的输出
  if(irSensorOutput == HIGH){ // 如果红外传感器输出高电平
      Serial.println("HIGH");
    } else{
      Serial.println("LOW"); 
      }
    delay(2000); // wait 2s for next reading
}
