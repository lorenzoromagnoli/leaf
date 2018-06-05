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


int n_LCD1 = 0;
int i_LCD1 = 0;
int j_LCD1 = 0;
int x_LCD1 = 0;

int n_LCD2 = 0;
int i_LCD2 = 0;
int j_LCD2 = 0;
int x_LCD2 = 0;

int n_LCD3 = 0;
int i_LCD3 = 0;
int j_LCD3 = 0;
int x_LCD3 = 0;

int n_LCD4 = 0;
int i_LCD4 = 0;
int j_LCD4 = 0;
int x_LCD4 = 0;

int n_LCD5 = 0;
int i_LCD5 = 0;
int j_LCD5 = 0;
int x_LCD5 = 0;

int n_LCD6 = 0;
int i_LCD6 = 0;
int j_LCD6 = 0;
int x_LCD6 = 0;

int n_LCD7 = 0;
int i_LCD7 = 0;
int j_LCD7 = 0;
int x_LCD7 = 0;

int n_LCD8 = 0;
int i_LCD8 = 0;
int j_LCD8 = 0;
int x_LCD8 = 0;


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

  printAllScreen("...");

  initWiFi();

  initPixels();

  setStripToWhite();
}


long lastScroll = 0;
long scrollDelay = 100;

void loop() {


  client.loop();
  delay(10); // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

if (millis() - lastScroll > scrollDelay) {
    udateDisplayScroll(lcd1, n_LCD1, i_LCD1, j_LCD1, x_LCD1, text1);
    udateDisplayScroll(lcd2, n_LCD2, i_LCD2, j_LCD2, x_LCD2, text2);
    udateDisplayScroll(lcd3, n_LCD3, i_LCD3, j_LCD3, x_LCD3, text3);
    udateDisplayScroll(lcd4, n_LCD4, i_LCD4, j_LCD4, x_LCD4, text4);
    udateDisplayScroll(lcd5, n_LCD5, i_LCD5, j_LCD5, x_LCD5, text5);
    udateDisplayScroll(lcd6, n_LCD6, i_LCD6, j_LCD6, x_LCD6, text6);
    udateDisplayScroll(lcd7, n_LCD7, i_LCD7, j_LCD7, x_LCD7, text7);
    udateDisplayScroll(lcd8, n_LCD8, i_LCD8, j_LCD8, x_LCD8, text8);

    lastScroll=millis();
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




