// 引入 wifi 模块，并实例化，不同的芯片这里的依赖可能不同
#include <ESP8266WiFi.h>
static WiFiClient espClient;

// 引入阿里云 IoT SDK
#include <AliyunIoTSDK.h>

#define HS_DETEC_PIN  D2  // 接受红外传感器的引脚
#define MQ_DETEC_PIN  D3  // 接受烟雾传感器的引脚

// 设置产品和设备的信息，从阿里云设备信息里查看
#define PRODUCT_KEY "gr5q2y2KNNb"
#define DEVICE_NAME "A615"
#define DEVICE_SECRET "54aec33cb27cbd76f4efc06c99aebb53"
#define REGION_ID "cn-shanghai"

// 设置 wifi 信息
#define WIFI_SSID "WJY"
#define WIFI_PASSWD "123456789"

bool irSensorOutput;  // 红外传感器输出信号
bool mqSensorOutput;  // 烟雾传感器输出信号

void setup()
{
    Serial.begin(9600);
    pinMode(HS_DETEC_PIN,INPUT); // 把D2引脚做输入模式,这样可以读取连接在它上面的红外传感器的信号
    pinMode(MQ_DETEC_PIN,INPUT); // 把D2引脚做输入模式,这样可以读取连接在它上面的烟雾传感器的信号

    WiFi.mode(WIFI_STA);
    // 初始化 wifi
    //wifiInit(WIFI_SSID, WIFI_PASSWD);
    connectWifi();
    
    // 初始化 iot，需传入 wifi 的 client，和设备产品信息
    AliyunIoTSDK::begin(espClient, PRODUCT_KEY, DEVICE_NAME, DEVICE_SECRET, REGION_ID);
    
    // 绑定一个设备属性回调，当远程修改此属性，会触发 powerCallback
    // PowerSwitch 是在设备产品中定义的物联网模型的 id
    //AliyunIoTSDK::bindData("PowerSwitch", powerCallback);
    AliyunIoTSDK::bindData("SmokeDetection", smokeCallback);
    
    // 发送一个数据到云平台，LightLuminance 是在设备产品中定义的物联网模型的 id
    //AliyunIoTSDK::send("SmokeDetection", 0);
}

void loop()
{
    AliyunIoTSDK::loop();
    //关于红外传感器的操作
    irSensorOutput = digitalRead(HS_DETEC_PIN);  // 读取红外传感器的输出
    if(irSensorOutput == HIGH){ // 如果红外传感器输出高电平
      Serial.println("HIGH");
      AliyunIoTSDK::send("InfraredSwitch", 1);
    } else{
      Serial.println("LOW"); 
      AliyunIoTSDK::send("InfraredSwitch", 0);
      }
     //关于烟雾传感器的操作
    mqSensorOutput = digitalRead(MQ_DETEC_PIN);  // 读取烟雾传感器的输出
    if(mqSensorOutput == HIGH){ // 如果红烟雾感器输出高电平
      Serial.println("有烟雾");
      AliyunIoTSDK::send("SmokeDetection", 1);
    } else{
      Serial.println("无烟雾"); 
      AliyunIoTSDK::send("SmokeDetection", 0);
      } 
      
      delay(2000);
}

// ESP8266连接wifi
void connectWifi(){
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
 
  //等待WiFi连接,成功连接后输出成功信息
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected!");  
  Serial.println(""); 
}

// 初始化 wifi 连接
void wifiInit(const char *ssid, const char *passphrase)
{
    //WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, passphrase);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("WiFi not Connect");
    }
    Serial.println("Connected to AP");
}

// 烟雾属性修改的回调函数
void smokeCallback(JsonVariant p)
{
    int SmokeDetection = p["SmokeDetection"];
    if (SmokeDetection ==1)
    {
        Serial.println("smoke1！");
    } else{
      Serial.println("smoke0");
      }
}

// 电源属性修改的回调函数
void powerCallback(JsonVariant p)
{
    int PowerSwitch = p["PowerSwitch"];
    if (PowerSwitch == 1)
    {
        // 启动设备
    } 
}
