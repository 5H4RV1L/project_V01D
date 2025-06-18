#pragma once
#include <Adafruit_SSD1306.h>
#include <time.h>

extern int menuIndex;
extern String menuItems[];
extern Adafruit_SSD1306 display;
extern const int menuSize;
extern int hour, minute, second;

#define MAX_VISIBLE 5
#define USER_NAME "username" //change to whatever you prefer

void drawMenu() {
  display.clearDisplay(); 
  
  struct tm timeinfo;
  char timeStr[9];
  //char timeStr[9];
  sprintf(timeStr, "%02d:%02d:%02d", hour, minute, second);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(timeStr);

  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(USER_NAME, 0, 0, &x1, &y1, &w, &h);
  display.setCursor(128 - w - 2, 0);
  display.print(USER_NAME);

  int topIndex = max(0, menuIndex - MAX_VISIBLE + 1);
  for (int i = 0; i < MAX_VISIBLE; i++) {
    int itemIndex = topIndex + i;
    if (itemIndex >= menuSize) break;

    display.setCursor(0, (i + 1) * 10);

    if (itemIndex == menuIndex) display.print("> ");
    else display.print("  ");

    display.println(menuItems[itemIndex]);
  }
  
  display.display();
}
