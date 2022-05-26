#define MQ2pin (0)
float sensorValue;  //定义变量来存储烟雾传感器值
void setup() {//我们初始化与PC的串行通信，并等待20秒以允许传感器预热
 Serial.begin(9600); // sets the serial port to 9600
  Serial.println("Gas sensor warming up!");
  delay(20000); // allow the MQ-6 to warm up
}

void loop() {
  sensorValue = analogRead(MQ2pin); // 烟雾传感器值由analogRead（）函数读取并显示在串行监视器上 
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);

  if(sensorValue > 700) //阈值 根据实际情况判断 大于300 还是小于300 ，300也是变量
   {
     Serial.print(" | Smoke detected!  探测到烟雾 ");
   }
   if(sensorValue <700){
    Serial.print(" | Smoke detected!  烟雾浓度低 ");
   }
   
   Serial.println("");
   delay(2000); // wait 2s for next reading
}
