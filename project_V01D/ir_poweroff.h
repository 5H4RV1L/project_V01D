#ifndef IR_POWEROFF_H
#define IR_POWEROFF_H

#include <IRremoteESP8266.h>
#include <IRsend.h>

extern Adafruit_SSD1306 display;

#define IR_LED_PIN 12
#define BTN_SELECT 16

extern IRsend irsend;

void startIRPowerOff() {
  irsend.begin();

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("IR Power-Off Blaster");
  display.println("Sending power codes...");
  display.println("Press SELECT to stop");
  display.display();
  
  while (!digitalRead(BTN_SELECT)) {
    delay(10); 
  }
  
  while (digitalRead(BTN_SELECT)) {

    irsend.sendNEC(0x20DF10EF, 32);  // Samsung
    delay(100);
    irsend.sendNEC(0x20DF23DC, 32);  // LG
    delay(100);
    irsend.sendNEC(0x4EBB20DF, 32);  // Haier
    delay(100);
    irsend.sendNEC(0xF20D, 32);      // Toshiba
    delay(100);
    irsend.sendNEC(0x10EF38C7, 32);  // Panasonic
    delay(100);
    irsend.sendNEC(0x00FF10EF, 32);  // Aiwa
    delay(100);
    irsend.sendNEC(0xA90, 32);       // Sansui
    delay(100);

    irsend.sendSony(0xA90, 12);      // Sony
    delay(100);
    irsend.sendSony(0x290, 12);      // Sony alt
    delay(100);

    irsend.sendRC5(0x100C, 13);      // Philips/BPL
    delay(100);
    irsend.sendRC5(0x1012, 13);      // Philips alt
    delay(100);
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("IR Blaster Stopped");
  display.display();
  delay(1500);
}

#endif
