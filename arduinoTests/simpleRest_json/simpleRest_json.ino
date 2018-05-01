#include <SPI.h>
#include <WiFi101.h>
#include <ArduinoJson.h>


char ssid[] = "CASALUCE"; //  your network SSID (name)
char pass[] = "robocats";    // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
IPAddress server(192, 168, 1, 102); // numeric IP for Google (no DNS)
//char server[] = "www.google.com";    // name address for Google (using DNS)

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds

WiFiClient client;


void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
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
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  //  while (client.available()) {
  //    char c = client.read();
  //    Serial.write(c);
  //  }

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


