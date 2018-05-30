void initLCD(){
  
 
  Wire.begin();
  Wire.beginTransmission(0x20);
  Wire.beginTransmission(0x21);
  Wire.beginTransmission(0x22);
  Wire.beginTransmission(0x23);
  Wire.beginTransmission(0x24);
  Wire.beginTransmission(0x25);
  Wire.beginTransmission(0x26);
  Wire.beginTransmission(0x27);

  lcd1.begin(16, 2); // initialize the lcd
  lcd2.begin(16, 2); // initialize the lcd
  lcd3.begin(16, 2); // initialize the lcd
  lcd4.begin(16, 2); // initialize the lcd
  lcd5.begin(16, 2); // initialize the lcd
  lcd6.begin(16, 2); // initialize the lcd
  lcd7.begin(16, 2); // initialize the lcd
  lcd8.begin(16, 2); // initialize the lcd
}

void initWiFi(){
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
