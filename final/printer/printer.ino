#include <WiFi101.h>
#include <MQTTClient.h>
#include "Adafruit_Thermal.h"

const char *ssid = "HOLDEN_UFFICI";
const char *pass = "2017_storytelling";

//setup the printer connected do serial 1 on MKR1000 13 and 14
Adafruit_Thermal printer(&Serial1);

WiFiClient net;
MQTTClient client;


void setup() {

  Serial.begin(9600);  // Initialize SoftwareSerial
  Serial1.begin(9600); // Use this instead if using hardware serial
  printer.begin();        // Init printer (same regardless of serial type)

  initWiFi();

  printmessage("ready to print!") ;
}

void loop() {

  client.loop();
  delay(10); // <- fixes some issues with WiFi stability
  
  if (!client.connected()) {
    connect();
  }
}

void printmessage(String message) {
  printer.wake();       // MUST wake() before printing again, even if reset

  printer.justify('L');
  printer.setSize('M');        // Set type size, accepts 'S', 'M', 'L'
  printer.feed(5);
  printer.println(message);
  printer.feed(5);

  printer.sleep();      // Tell printer to sleep
  printer.setDefault(); // Restore printer to defaults


}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();

printmessage(payload);
 // int screenIndex = topic.charAt(topic.length() - 1) - 48;
  //Serial.println(screenIndex);

}


