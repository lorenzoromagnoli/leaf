#include <SPI.h>
#include <WiFi101.h>
#include <MQTTClient.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

/////////////////////////////////////
///////////VERY IMPORTANT////////////
/////////////////////////////////////
//////////CHANGE ARDUINO ID/////////
/////////////////////////////////////

int arduinoId = 4; //plese use 1,2,3,4 or 5 accordingly. 
String clientName=String("arduino") + arduinoId;

/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////

//WIFI
const char *ssid = "HOLDEN_UFFICI";
const char *pass = "2017_storytelling";
WiFiClient net;
MQTTClient client;

//LCD
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

 // Constant for my lcd size, adjust to your lcd
#define LCDWIDTH 16
#define LCDHEIGHT 2


//NEOPIXEL 
#define PIN            7
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      60
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);


void setup() {
  delay(random (5000));
  Serial.begin(9600);
  Serial.println();
  Serial.print("initializing ");
  Serial.println(clientName);

  initLCD();

  lcd1.setCursor(0,0);
  lcd1.print("...");

  initWiFi();

  initPixels();

  setStripToWhite();
}



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

