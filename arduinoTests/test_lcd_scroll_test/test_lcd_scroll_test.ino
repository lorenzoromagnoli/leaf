#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>


// Constant for my lcd size, adjust to your lcd
#define LCDWIDTH 16
#define LCDHEIGHT 2

// Used lcd: mine is 0x27 type
LiquidCrystal_PCF8574 lcd(0x3E);

void setup() {
  lcd.begin(LCDWIDTH, LCDHEIGHT); // initialize with your correct lcd size here
  lcd.clear();

  String pinnedString = "by Goet";
  String scrollingString = "I don't like being long-winded type of guy, so I think i'll go straight to the point: this is a very long, long text scrolling on your lcd display :)";

  int pinnedRow = LCDHEIGHT / 2;
  int scrollingRow =  LCDHEIGHT / 2 - 1;
  int scrollingSpeed = 300;
      lcd.setBacklight(50);

  //pinAndScrollText(pinnedString, pinnedRow, scrollingString, scrollingRow, scrollingSpeed);
  
  pinAndScrollText(lcd, 0, scrollingString, 1, 300);

  delay(2000);
  lcd.clear();
  lcd.print("Back");

}

void loop() {
}

/* This procedure pins a given text in the center of a desired row while scrolling from right to left another given text on another desired row.
    Parameters:
    const String &pinnedText: pinned String
    int pinnedRow: desired row for pinned String
    const String &scrollingText: scrolling String
    int scrollingRow: desired row for scrolling String
    int v = scrolling speed expressed in milliseconds
*/


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

