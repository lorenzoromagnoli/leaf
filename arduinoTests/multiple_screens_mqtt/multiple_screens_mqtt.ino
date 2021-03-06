#include <SPI.h>
#include <WiFi101.h>
#include <MQTTClient.h>

const char *ssid = "HOLDEN_UFFICI";
const char *pass = "2017_storytelling";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd1(0x20);  
LiquidCrystal_PCF8574 lcd2(0x21);  
LiquidCrystal_PCF8574 lcd3(0x22);  
LiquidCrystal_PCF8574 lcd4(0x23);  
LiquidCrystal_PCF8574 lcd5(0x24);  
LiquidCrystal_PCF8574 lcd6(0x25);  
LiquidCrystal_PCF8574 lcd7(0x26);  
LiquidCrystal_PCF8574 lcd8(0x27);  

void setup() {
  Serial.begin(9600);
  initLCD();

  writeMessageToScreen(0,"...");

  initWiFi();
  connect();
}




void loop() {
  client.loop();
  delay(10); // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();

  int screenIndex=topic.charAt(topic.length()-1)-48;
  //Serial.println(screenIndex);
  
  writeMessageToScreen(screenIndex,payload);
}

void writeMessageToScreen(int lcdIndex, String msg) {
  switch ( lcdIndex) {
    case 0:
      lcd1.setBacklight(255);
      lcd1.home();
      lcd1.clear();
      lcd1.print(msg);
      break;

    case 1:
      lcd2.setBacklight(255);
      lcd2.home();
      lcd2.clear();
      lcd2.print(msg);
      break;

    case 2:
      lcd3.setBacklight(255);
      lcd3.home();
      lcd3.clear();
      lcd3.print(msg);
      break;

    case 3:
      lcd4.setBacklight(255);
      lcd4.home();
      lcd4.clear();
      lcd4.print(msg);
      break;
  }
}


