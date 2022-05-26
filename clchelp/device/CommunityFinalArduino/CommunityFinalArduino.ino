#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#define MQ2pin (0)

int mqSensorPin=7;  // 用来输出烟雾传感器最终高低电平的引脚
bool mqSensorOutput;  // 读取红外传感器输出信号

float sensorValue;  //定义变量来存储烟雾传感器值
void setup() {//我们初始化与PC的串行通信，并等待20秒以允许传感器预热
  pinMode(mqSensorPin,OUTPUT); // 把第七个引脚做输入模式,通过判断烟雾传感器的有无烟雾传输到esp8266
  Serial.begin(9600); // sets the serial port to 9600
  Serial.println("Gas sensor warming up!");
  delay(20000); // allow the MQ-6 to warm up
}

void loop() {
  // 关于烟雾传感器的读取
  sensorValue = analogRead(MQ2pin); // 烟雾传感器值由analogRead（）函数读取并显示在串行监视器上 
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  if(sensorValue > 300) //阈值 根据实际情况判断 大于300 还是小于300 ，300也是变量
   {
     Serial.print(" | Smoke detected!  探测到烟雾 ");
     digitalWrite(mqSensorPin,HIGH);
   }
   if(sensorValue <300){
    Serial.print(" | Smoke detected!  烟雾浓度低 ");
    digitalWrite(mqSensorPin,LOW);
   }
   
   Serial.println("");
   delay(2000); // wait 2s for next reading
}
