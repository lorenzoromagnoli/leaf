void initLCD() {
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

  Wire.endTransmission();
}

void initPixels() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
}

void initWiFi() {
  WiFi.begin(ssid, pass);
  client.begin("broker.shiftr.io", net);
  connect();
}

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    for (int i = 1; i < 9; i++) {
      writeMessageToScreen(i, "connecting...");
    }

    delay(1000);

  }

  Serial.print("\nconnecting...");
  while (!client.connect("mkr1000", "ebd3575a", "39bccc93d8b275b1")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  for (int i = 1; i < 9; i++) {
    writeMessageToScreen(i, "Connected!");
  }

  client.subscribe(String("/arduino")+arduinoId+String("/#"));
  client.subscribe("glow");
}



void writeMessageToScreen(int lcdIndex, String msg) {
  switch ( lcdIndex) {
    case 1:
      lcd1.setBacklight(255);
      lcd1.home();
      lcd1.autoscroll();
      lcd1.clear();
      lcd1.print(msg);
      break;

    case 2:
      lcd2.setBacklight(255);
      lcd2.home();
      lcd2.clear();
      lcd2.print(msg);
      break;

    case 3:
      lcd3.setBacklight(255);
      lcd3.home();
      lcd3.clear();
      lcd3.print(msg);
      break;

    case 4:
      lcd4.setBacklight(255);
      lcd4.home();
      lcd4.clear();
      lcd4.print(msg);
      break;

    case 5:
      lcd5.setBacklight(255);
      lcd5.home();
      lcd5.clear();
      lcd5.print(msg);
      break;

    case 6:
      lcd6.setBacklight(255);
      lcd6.home();
      lcd6.clear();
      lcd6.print(msg);
      break;

    case 7:
      lcd7.setBacklight(255);
      lcd7.home();
      lcd7.clear();
      lcd7.print(msg);
      break;

    case 8:
      lcd8.setBacklight(255);
      lcd8.home();
      lcd8.clear();
      lcd8.print(msg);
      break;
  }
}

void setStripToWhite() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(20, 20, 20)); // Moderately bright green color.
  }
  pixels.show(); // This sends the updated pixel color to the hardware.

}

void setStripToBlack() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Moderately bright green color.
  }
  pixels.show(); // This sends the updated pixel color to the hardware.

}

void blink() {
  for (int i = 0; i < 10000; i++) {
    if (random(2) > 0) {
      int brightness = random (50, 100);
      pixels.setPixelColor(random(NUMPIXELS), pixels.Color(brightness, brightness, brightness)); // Moderately bright green color.
      Serial.println("on");
    } else {
      pixels.setPixelColor(random(NUMPIXELS), pixels.Color(0, 0, 0)); // Moderately bright green color.
    }
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
}


void glow() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(10);
  }
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(50, 100, 80)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(10);
  }

  delay(2000);
}

void paparazzi() {
  for (int i = 0; i < 1000; i++) {
    int randompixel = random(NUMPIXELS);
    pixels.setPixelColor(randompixel, pixels.Color(255, 255, 255)); 
    pixels.show(); 
    delay(10);
    pixels.setPixelColor(randompixel, pixels.Color(0, 0, 0));
    pixels.show();
    delay(1);
  }
}


