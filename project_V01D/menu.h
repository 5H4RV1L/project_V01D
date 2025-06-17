#pragma once
#include <Adafruit_SSD1306.h>

extern int menuIndex;
extern String menuItems[];
extern Adafruit_SSD1306 display;

void drawMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);  
  for (int i = 0; i < 8; i++) {
    if (i == menuIndex) display.print("> ");
    else display.print("  ");
    display.println(menuItems[i]);
  }
  display.display();
}
