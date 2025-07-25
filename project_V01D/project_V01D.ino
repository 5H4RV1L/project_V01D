#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <time.h>

#include "menu.h"
#include "beacon_flood.h"
#include "fake_deauth.h"
#include "wifi_selector.h"
#include "evil_portal.h"
#include "ble_spammer.h"
#include "ble_advertise.h"
#include "ble_jammer.h"
#include "ir_poweroff.h"
#include "ir_replay.h"

#define USER_NAME "username" //change it to whatever you prefer to be displayed

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

#define I2C_SDA 15
#define I2C_SCL 14

int hour = 0;
int minute = 0;
int second = 0;
unsigned long lastClockUpdate = 0;

#define IR_SEND_PIN 12
IRsend irsend(IR_SEND_PIN);

const int btnDown = 13;
const int btnSelect = 16;

TwoWire myWire = TwoWire(0);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &myWire, -1);

int menuIndex = 0;
String menuItems[] = {"AP Flood", "Deauth (maybe?)", "Evil Portal", "BLE Spammer", "BLE Spoffing", "BLE jammer", "IR Powweroff", "IR Cloner", "IR Cloner", "slot 1", "slot 2"};
const int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);

void updateClock() {
  unsigned long now = millis();
  if (now - lastClockUpdate >= 1000) {
    lastClockUpdate = now;
    second++;
    if (second >= 60) {
      second = 0;
      minute++;
    }
    if (minute >= 60) {
      minute = 0;
      hour++;
    }
    if (hour >= 24) {
      hour = 0;
    }
  }
}

void setup() {
  
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  
  Serial.begin(115200);

  pinMode(btnDown, INPUT_PULLUP);
  pinMode(btnSelect, INPUT_PULLUP);

  myWire.begin(I2C_SDA, I2C_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  String title = "p r o j e c t";
  int16_t x1, y1;
  uint16_t w1, h1;
  display.getTextBounds(title, 0, 0, &x1, &y1, &w1, &h1);
  int16_t xTitle = (SCREEN_WIDTH - w1) / 2;
  int16_t yTitle = 12; 
  display.setCursor(xTitle, yTitle);
  display.println(title);

  display.setTextSize(4);
  String text = "V01D";
  int16_t x2, y2;
  uint16_t w2, h2;
  display.getTextBounds(text, 0, 0, &x2, &y2, &w2, &h2);
  int16_t xText = (SCREEN_WIDTH - w2) / 2;
  int16_t yText = yTitle + h1 + 4;
  display.setCursor(xText, yText);
  display.println(text);
  
  display.display();
  delay(1500);
  display.clearDisplay();
  drawMenu();
}

void loop() {
  updateClock();
  
  if (!digitalRead(btnDown)) {
    menuIndex = (menuIndex + 1) % menuSize;
    drawMenu();
    delay(200);
  }
  if (!digitalRead(btnSelect)) {
    runSelectedTool(menuIndex);
    delay(300);
  }
}

void runSelectedTool(int index) {
  switch (index) {
    case 0: 
      startBeaconFlood(); 
      break;
    case 1:  
      showNetworkSelector();
      startFakeDeauth();
      break;
    case 2: 
      startEvilPortal();
      break;
    case 3:
      startBLESpam();
      break;
    case 4:
      startBLEAdvertise();
      break;
    case 5:
      startBLEJammer();
      break;
    case 6:
      startIRPowerOff();
      break;
    case 7:
      startIRReplay();
      break;
    case 8:
      break;
    case 9:
      break;
  }
}
