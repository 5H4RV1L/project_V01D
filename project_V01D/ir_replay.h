#ifndef IR_REPLAY_H
#define IR_REPLAY_H

#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>

extern Adafruit_SSD1306 display;

#define IR_RECV_PIN 2      
#define IR_LED_PIN 12     
#define BTN_SELECT 16
#define BTN_DOWN 13

IRrecv irrecv(IR_RECV_PIN);
decode_results results;
extern IRsend irsend;

decode_type_t savedProtocol;
uint64_t savedData = 0;
uint16_t savedBits = 0;

void showMsg(const char* msg) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println(msg);
  display.display();
}

void startIRReplay() {
  irrecv.enableIRIn();
  irsend.begin();

  bool recorded = false;
  bool replaying = false;

  showMsg("IR Replay\nPress SELECT\nto start recording");
  while (digitalRead(BTN_SELECT)) delay(10);
  while (!digitalRead(BTN_SELECT)) delay(10);  

  showMsg("Recording IR...");
  unsigned long startTime = millis();
  while (!recorded && millis() - startTime < 5000) { 
    if (irrecv.decode(&results)) {
      savedProtocol = results.decode_type;
      savedData = results.value;
      savedBits = results.bits;
      recorded = true;
      irrecv.resume();
    }
  }

  if (!recorded) {
    showMsg("Recording failed!\n(No signal)");
    delay(1500);
    return;
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Recording Done!");
  display.print("Type: ");
  display.println(typeToString(savedProtocol));
  display.print("Bits: ");
  display.println(savedBits);
  display.display();
  delay(2000);

  showMsg("Press SELECT to replay\nPress DOWN to exit");
  while (true) {
    if (!digitalRead(BTN_SELECT)) {
      while (!digitalRead(BTN_SELECT)) delay(10);
      replaying = true;
      break;
    }
    if (!digitalRead(BTN_DOWN)) {
      while (!digitalRead(BTN_DOWN)) delay(10);
      return;
    }
  }

  while (true) {
  showMsg("Press SELECT to replay\nPress DOWN to exit");
  while (digitalRead(BTN_SELECT) && digitalRead(BTN_DOWN)) delay(10);
  
    if (!digitalRead(BTN_DOWN)) {
      while (!digitalRead(BTN_DOWN)) delay(10);
      break;
    }
  }

  showMsg("Replaying IR...\nPress SELECT to stop");

  while (true) {
    if (!digitalRead(BTN_SELECT)) {
      while (!digitalRead(BTN_SELECT)) delay(10);
      showMsg("Replay stopped.");
      delay(1000);
      break;
    }

    switch (savedProtocol) {
      case NEC:      irsend.sendNEC(savedData, savedBits); break;
      case SONY:     irsend.sendSony(savedData, savedBits); break;
      case RC5:      irsend.sendRC5(savedData, savedBits); break;
      case RC6:      irsend.sendRC6(savedData, savedBits); break;
      case SAMSUNG:  irsend.sendSAMSUNG(savedData, savedBits); break;
      default: break;
    }

    delay(300);
  }
}

#endif
