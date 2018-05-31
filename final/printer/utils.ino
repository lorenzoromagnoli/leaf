void initWiFi() {
  WiFi.begin(ssid, pass);
  client.begin("broker.shiftr.io", net);
  connect();
}

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);

  }

  Serial.print("\nconnecting...");
  while (!client.connect("mkr1000", "ebd3575a", "39bccc93d8b275b1")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/printer/#");
}
