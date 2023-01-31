
#include <Arduino.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
TFT_eSprite spr = TFT_eSprite(&tft);
// 温湿度处理
#define DHTFeature 1
#define DHTTYPE    DHT11     // DHT 11
#define DHTPIN 0     // 传感器针脚Digital pin connected to the DHT sensor 

const char* ssid     = "MOON-WIFI-511";    	 // WIFI账户
const char* password = "123qazwsxedc456";	 // WIFI密码

// 气压计处理
// #define BMP180 1
// Adafruit_BMP085 bmp;

DHT dht(DHTPIN, DHTTYPE);

void setup4DHT11() {
  #ifdef DHTFeature
  dht.begin();
  #endif
}

void dhtRead() {
  #ifdef DHTFeature
  float hum = dht.readHumidity();
  float tem = dht.readTemperature();
  spr.drawRect(0, 0, 160, 80, TFT_BLACK);
  spr.setCursor(0, 0);

  spr.fillSprite(TFT_BLACK);
  spr.setTextColor(TFT_GREEN, TFT_BLACK); 
  spr.setTextSize(1);
  spr.setCursor(0, 0);
  spr.print("Temperature is\n"); spr.println(tem, 1); //默认是保留两位小数，这里我们保留一位小数
  spr.setCursor(0, 40);
  spr.print("Humidity is\n"); spr.print(hum, 1);spr.println("%");
  spr.pushSprite(0, 0); 
  #endif 
}

void setup()
{
  Serial.begin(115200);
  pinMode(12,OUTPUT);
  setup4DHT11();
  
  tft.init();
  tft.setRotation(3);
  
  // Create a sprite of defined size
  spr.createSprite(160, 80);

  // Clear the TFT screen to black
  spr.setTextFont(2);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK); 
  tft.setTextSize(1);
  tft.setCursor(5, 12);   
  tft.println("Code by");
  tft.setCursor(15, 40); 
  tft.setTextSize(2);
  tft.println("SectionOne");
  delay(2000);

  WiFi.begin(ssid, password);
  tft.fillScreen(TFT_BLACK);//LCD清空
  tft.setCursor(0, 0);
  tft.setTextSize(1);
  tft.print("WIFI Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(12,1);
    delay(100);
    tft.print(".");
    digitalWrite(12,0);
  }

  tft.println();
  tft.println("WiFi connected!");
  delay(2000);
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  Serial.printf("Section-running");
  dhtRead();
  

  // if (digitalRead(12) == 1) {
  //   digitalWrite(12,0);
  // } else {
  //   digitalWrite(12,1);
  // }
  
  delay(1000);
}

