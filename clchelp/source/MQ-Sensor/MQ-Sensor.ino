int MQ2=A1;

int val=0;  // 声明临时变量
int buzzer=8;

void setup() {
  pinMode(MQ2,INPUT);
  Serial.begin(9600); //设置串口波特率为9600
 // pinMode(buzzer,OUTPUT); // 设置数字IO脚模式，OUTPUT为输出

}

void loop() {
  val=analogRead(MQ2);  // 读取A0口的电压值并赋值到val
  Serial.println("val");  //串口发送val值
  if(val>70){
      Serial.println("HIGH"); // 说明是高浓度
    }else{
      Serial.println("LOW");  // 说明是低浓度
      }
    delay(100);

}
