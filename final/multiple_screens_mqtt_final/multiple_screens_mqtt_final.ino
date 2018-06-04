#include <SPI.h>
#include <WiFi101.h>
#include <MQTTClient.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

const char *ssid = "HOLDEN_UFFICI";
const char *pass = "2017_storytelling";

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

int arduinoId = 4;

#define PIN            7

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      60

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);


void setup() {
  random (5000);
  Serial.begin(9600);
  initLCD();

  for (int i = 1; i < 9; i++) {
    writeMessageToScreen(i, "...");
  }

  initWiFi();

  initPixels();

  setStripToWhite();
}


long lastScroll = 0;
long scrollDelay = 200;


void loop() {

  if (millis() - lastScroll > scrollDelay) {
    scrollmessage();
    lastScroll = millis();

  }

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

  if (topic == "glow") {
    paparazzi();
    setStripToWhite();

  } else {
    int screenIndex = topic.charAt(topic.length() - 1) - 48;
    //Serial.println(screenIndex);

    writeMessageToScreen(screenIndex, payload);

  }
}

int scrollIndex = 0;
int messagesLegth = 160;

void scrollmessage() {
  if (scrollIndex < messagesLegth) {
    lcd1.scrollDisplayLeft();
    lcd2.scrollDisplayLeft();
    lcd3.scrollDisplayLeft();
    lcd4.scrollDisplayLeft();
    lcd5.scrollDisplayLeft();
    lcd6.scrollDisplayLeft();
    lcd7.scrollDisplayLeft();
    lcd8.scrollDisplayLeft();
    scrollIndex++;
  } else {
    lcd1.home();
    lcd2.home();
    lcd3.home();
    lcd4.home();
    lcd5.home();
    lcd6.home();
    lcd7.home();
    lcd8.home();
    scrollIndex = 0;
  }
}

