#include <SPI.h>
#include <WiFi101.h>
#include <MQTTClient.h>

const char *ssid = "CASALUCE";
const char *pass = "robocats";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd1(0x3E);  // set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_PCF8574 lcd2(0x3F);  // set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_PCF8574 lcd3(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_PCF8574 lcd4(0x23);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(9600);

  int error;
  Wire.begin();

  Wire.beginTransmission(0x3E);
  Wire.beginTransmission(0x3F);
  Wire.beginTransmission(0x27);
  Wire.beginTransmission(0x23);

  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);

  if (error == 0) {
    Serial.println(": LCD found.");

  } else {
    Serial.println(": LCD not found.");
  } // if

  lcd1.begin(16, 2); // initialize the lcd
  lcd2.begin(16, 2); // initialize the lcd
  lcd3.begin(16, 2); // initialize the lcd
  lcd4.begin(16, 2); // initialize the lcd

  writeMessageToScreen(0,"...");




  WiFi.begin(ssid, pass);
  client.begin("broker.shiftr.io", net);

  connect();



}

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    writeMessageToScreen(0, "Connecting...");
    delay(1000);
  }
  Serial.print("\nconnecting...");
  while (!client.connect("mkr1000", "ebd3575a", "39bccc93d8b275b1")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");
  writeMessageToScreen(0, "Connected!");

  client.subscribe("/arduino0/#");
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


