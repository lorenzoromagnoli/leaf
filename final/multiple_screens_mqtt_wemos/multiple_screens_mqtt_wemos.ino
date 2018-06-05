#include <ESP8266WiFi.h>
#include <MQTTClient.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

const char *ssid = "TMNL-129315";
const char *pass = "YNS7HQEWWWUBFZ";

WiFiClient net;
MQTTClient client;

LiquidCrystal_PCF8574 lcd1(0x20);
LiquidCrystal_PCF8574 lcd2(0x21);
LiquidCrystal_PCF8574 lcd3(0x22);
LiquidCrystal_PCF8574 lcd4(0x23);
LiquidCrystal_PCF8574 lcd5(0x24);
LiquidCrystal_PCF8574 lcd6(0x25);
LiquidCrystal_PCF8574 lcd7(0x26);
LiquidCrystal_PCF8574 lcd8(0x27);

String text1;
String text2;
String text3;
String text4;
String text5;
String text6;
String text7;
String text8; 

int arduinoId = 4;


// Constant for my lcd size, adjust to your lcd
#define LCDWIDTH 16
#define LCDHEIGHT 2



void setup() {
  random (5000);
  Serial.begin(9600);
  initLCD();

  lcd1.setCursor(0,0);
  lcd1.print("...");

  
  initWiFi();
}


long lastScroll = 0;
long scrollDelay = 200;


void loop() {

  client.loop();
  delay(10); // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }


}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.println();
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();

  if (topic == "glow") {

  } else {
    int screenIndex = topic.charAt(topic.length() - 1) - 48;
    //Serial.println(screenIndex);
    writeMessageToScreen(screenIndex, payload);

  }
}


