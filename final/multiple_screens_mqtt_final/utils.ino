void initLCD() {
  Wire.begin();

  Wire.beginTransmission(0x3E);
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

  lcd1.clear();
  lcd2.clear();
  lcd3.clear();
  lcd4.clear();
  lcd5.clear();
  lcd6.clear();
  lcd7.clear();
  lcd8.clear();


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
     
    lcd1.setBacklight(50);
    lcd1.setCursor(0,0);
    lcd1.print("connecting...");

    delay(1000);

  }

  Serial.print("\nconnecting...");
  while (!client.connect( string2char(clientName), "ebd3575a", "39bccc93d8b275b1")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

 lcd1.setCursor(0,0);
 lcd1.print("connected!");
    

  client.subscribe(String("/arduino") + arduinoId + String("/#"));
  client.subscribe("glow");
}



void writeMessageToScreen(int lcdIndex, String msg) {
  switch ( lcdIndex) {
    case 1:
      text1 = msg;
      pinAndScrollText(lcd1, 0, text1, 1, 300);
      break;

    case 2:
      text2 = msg;
      pinAndScrollText(lcd2, 0, text2, 1, 300);
      break;

    case 3:
      text3 = msg;
      pinAndScrollText(lcd3, 0, text3, 1, 300);
      break;

    case 4:
      text4 = msg;
      pinAndScrollText(lcd4, 0, text4, 1, 300);
      break;

    case 5:
      text4 = msg;
      pinAndScrollText(lcd5, 0, text5, 1, 300);
      break;

    case 6:
      text6 = msg;
      pinAndScrollText(lcd6, 0, text6, 1, 300);
      break;

    case 7:
      text7 = msg;
      pinAndScrollText(lcd7, 0, text7, 1, 300);
      break;

    case 8:
      text8 = msg;
      pinAndScrollText(lcd8, 0, text8, 1, 300);
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
  for (int i = 0; i < 500; i++) {
    int randompixel = random(NUMPIXELS);
    pixels.setPixelColor(randompixel, pixels.Color(255, 255, 255));
    pixels.show();
    delay(10);
    pixels.setPixelColor(randompixel, pixels.Color(0, 0, 0));
    pixels.show();
    delay(1);
  }
}


void pinAndScrollText(LiquidCrystal_PCF8574 &lcd, int pinnedRow, const String &scrollingText, int scrollingRow, int v) {
  int x = LCDWIDTH;
  int n = scrollingText.length() + x;

  Serial.print("length: ");
  Serial.println(n-x);
  
  int i = 0;
  int j = 0;
  while (n > 0) {
    if (x > 0) {
      x--;
    }
    lcd.setCursor(x, scrollingRow);
    if (n > LCDWIDTH) {
      j++;
      i = (j > LCDWIDTH) ? i + 1 : 0;
      lcd.print(scrollingText.substring(i, j));
    } else {
      i = i > 0 ? i + 1 : 0;
      if (n == scrollingText.length()) {
        i++;
      }
      lcd.print(scrollingText.substring(i, j));
      lcd.setCursor(n - 1, scrollingRow);
      lcd.print(' ');
    }
    n--;
    if (n > 0) {
      delay((v / 4) * 3);
      lcd.clear();
      delay((v / 4) * 1);
      Serial.print("scroll-");
    }
  }
}

char* string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
}


