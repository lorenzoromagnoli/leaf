void initLCD() {

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

  lcd1.setBacklight(50);
  lcd2.setBacklight(50);
  lcd3.setBacklight(50);
  lcd4.setBacklight(50);
  lcd5.setBacklight(50);
  lcd6.setBacklight(50);
  lcd7.setBacklight(50);
  lcd8.setBacklight(50);

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

       printAllScreen("connecting...");


    delay(1000);

  }

  Serial.print("\nconnecting...");
  while (!client.connect("wemos", "ebd3575a", "39bccc93d8b275b1")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

   Serial.println("\nconnected!");



  client.subscribe(String("/arduino") + arduinoId + String("/#"));
  client.subscribe("glow");
}





void writeMessageToScreen(int lcdIndex, String msg) {
  switch ( lcdIndex) {
    case 1:
      text1 = msg;
      lcd1.clear();
      pinAndScrollText(lcd1, n_LCD1, i_LCD1, j_LCD1, x_LCD1, 0, text1, 1, 300);
      break;

    case 2:
      text2 = msg;
      lcd2.clear();
      pinAndScrollText(lcd2, n_LCD2, i_LCD2, j_LCD2, x_LCD2, 0, text2, 1, 300);
      break;

    case 3:
      text3 = msg;
      lcd3.clear();
      pinAndScrollText(lcd3, n_LCD3, i_LCD3, j_LCD3, x_LCD3, 0, text3, 1, 300);
      break;

    case 4:
      text4 = msg;
      lcd4.clear();
      pinAndScrollText(lcd4, n_LCD4, i_LCD4, j_LCD4, x_LCD4, 0, text4, 1, 300);
      break;

    case 5:
      text5 = msg;
      lcd5.clear();
      pinAndScrollText(lcd5, n_LCD5, i_LCD5, j_LCD5, x_LCD5, 0, text5, 1, 300);
      break;

    case 6:
      text6 = msg;
      lcd6.clear();
      pinAndScrollText(lcd6, n_LCD6, i_LCD6, j_LCD6, x_LCD6, 0, text6, 1, 300);
      break;

    case 7:
      text7 = msg;
            lcd7.clear();

      pinAndScrollText(lcd7, n_LCD7, i_LCD7, j_LCD7, x_LCD7, 0, text7, 1, 300);
      break;

    case 8:
      text8 = msg;
       lcd8.clear();

      pinAndScrollText(lcd8, n_LCD8, i_LCD8, j_LCD8, x_LCD8, 0, text8, 1, 300);
      break;
  }
}



void udateDisplayScroll(LiquidCrystal_PCF8574 &lcd, int &n_LCD, int &i_LCD, int &j_LCD, int &x_LCD, const String &scrollingText ){
  if (n_LCD > 0) {
    if (x_LCD > 0) {
      x_LCD--;
    }
    lcd.setCursor(x_LCD, 1);
    if (n_LCD > LCDWIDTH) {
      j_LCD++;
      i_LCD = (j_LCD > LCDWIDTH) ? i_LCD + 1 : 0;
      lcd.print(scrollingText.substring(i_LCD, j_LCD));
    } else {
      i_LCD = i_LCD > 0 ? i_LCD + 1 : 0;
      if (n_LCD == scrollingText.length()) {
        i_LCD++;
      }
      lcd.print(scrollingText.substring(i_LCD, j_LCD));
      lcd.setCursor(n_LCD - 1, 1);
      lcd.print(' ');
    }
    n_LCD--;
 
    
    if (n_LCD > 0){
    lcd.clear();
    delay(50);
    }else{
     x_LCD = LCDWIDTH;
     n_LCD = scrollingText.length() + x_LCD;
     
     i_LCD = 0;
     j_LCD = 0;
       
//      delay((v / 4) * 3);
//      lcd.clear();
//      delay((v / 4) * 1);
      Serial.print("scroll-");
    }
  }
}

void pinAndScrollText(LiquidCrystal_PCF8574 &lcd, int &n_LCD , int &i_LCD, int &j_LCD, int &x_LCD, int pinnedRow, const String &scrollingText, int scrollingRow, int v) {
  int x = LCDWIDTH;
  n_LCD = scrollingText.length() + x;

  Serial.print("length: ");
  Serial.println(n_LCD-x_LCD);
  
  i_LCD = 0;
  j_LCD = 0;
}




void printAllScreen(String msg){
  
  lcd1.clear();
  lcd2.clear();
  lcd3.clear();
  lcd4.clear();
  lcd5.clear();
  lcd6.clear();
  lcd7.clear();
  lcd8.clear();

  lcd1.setCursor(0,0);
  lcd2.setCursor(0,0);
  lcd3.setCursor(0,0);
  lcd4.setCursor(0,0);
  lcd5.setCursor(0,0);
  lcd6.setCursor(0,0);
  lcd7.setCursor(0,0);
  lcd8.setCursor(0,0);
  
  lcd1.print(msg);
  lcd2.print(msg);
  lcd3.print(msg);
  lcd4.print(msg);
  lcd5.print(msg);
  lcd6.print(msg);
  lcd7.print(msg);
  lcd8.print(msg);

}

char* string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
}

