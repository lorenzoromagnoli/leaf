#include <SPI.h>
#include <WiFi101.h>
#include <MQTTClient.h>

#include <ArduinoJson.h>


char ssid[] = "CASALUCE"; //  your network SSID (name)
char pass[] = "robocats";    // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
IPAddress server(192, 168, 1, 102); // numeric IP for Google (no DNS)
//char server[] = "www.google.com";    // name address for Google (using DNS)

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 1L * 1000L; // delay between updates, in milliseconds

WiFiClient client;

#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd1(0x3E);  // set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_PCF8574 lcd2(0x3F);  // set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_PCF8574 lcd3(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_PCF8574 lcd4(0x23);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int screenToUpdateIndex=0;
int nScreens=4;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);


    // wait 10 seconds for connection:
    delay(10000);
  }
  // you're connected now, so print out the status:
  printWifiStatus();

 
  
  Serial.println("\nconnected!");


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
}

void loop() {


  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line[0] == '[' || line[0] == '{') { //usually a json starts with this two signs.
      Serial.println("got response");
      Serial.println(line);
      
      Serial.println("parsingValues");
      //create a json buffer where to store the json data
      DynamicJsonBuffer jsonBuffer;
      JsonArray& array = jsonBuffer.parseArray(line);
      String message = array[0]["message"];

      Serial.println(message);

      writeMessageToScreen(screenToUpdateIndex,message );
      screenToUpdateIndex++;

      if(screenToUpdateIndex==nScreens){
        screenToUpdateIndex=0;
      }
      
      //JsonObject& root = jsonBuffer.parseObject(line);
      if (!array.success()) {
        Serial.println("parseObject() failed");
        return;
      }
    }

  }


  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }

}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 3000)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET /getRandomMsg HTTP/1.1");
    client.println("Connection: close");
    client.println();
    // note the time that the connection was made:
    lastConnectionTime = millis();
  }
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
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

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();
}

