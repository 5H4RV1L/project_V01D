#ifndef BLE_ADVERTISE_H
#define BLE_ADVERTISE_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEAdvertising.h>
#include <BLEServer.h>

extern Adafruit_SSD1306 display;

#define BTN_DOWN 13
#define BTN_SELECT 16

const char* fakeDevices[] = {
  "AirPods",
  "AirPods Pro",
  "boAt Airdopes 141",
  "JBL TUNE 500BT",
  "OnePlus Buds",
  "realme Buds Q2",
  "Skullcandy Sesh",
  "Sony WH-1000XM4",
  "iPhone 14 Pro Max",
  "Samsung Galaxy A52",
  "POCO X3 Pro",
  "Mi Band 7",
  "Xbox Wireless",
  "Galaxy Watch",
  "PS4 Controller"
};

const int numDevices = sizeof(fakeDevices) / sizeof(fakeDevices[0]);

void drawBLEDeviceList(int topVisible, int selected) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Select BLE Device:");
  for (int i = 0; i < 6; i++) {
    int idx = topVisible + i;
    if (idx >= numDevices) break;
    if (idx == selected) display.print("> ");
    else display.print("  ");
    display.println(fakeDevices[idx]);
  }
  display.display();
}

void advertiseBLEDevice(const char* name) {
  BLEDevice::deinit(true);
  delay(100);  
  BLEDevice::init(name);

  BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
  BLEAdvertisementData adData;

  adData.setFlags(0x06);
  adData.setName(name);
  pAdvertising->setAdvertisementData(adData);
  pAdvertising->start();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("BLE Spoofing");
  display.println(String("As: ") + name);
  display.println("Press SELECT to stop");
  display.display();

  while (digitalRead(BTN_SELECT)) {
    delay(10);
  }

  pAdvertising->stop();
  BLEDevice::deinit(true);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("BLE Spoof Stopped");
  display.display();
  delay(1000);
}

void startBLEAdvertise() {
  int selected = 0;
  int topVisible = 0;

  drawBLEDeviceList(topVisible, selected);

  while (!digitalRead(BTN_SELECT)) delay(10);

  while (true) {
    if (!digitalRead(BTN_DOWN)) {
      while (!digitalRead(BTN_DOWN));
      selected = (selected + 1) % numDevices;
      if (selected >= topVisible + 6) {
        topVisible = selected - 5;
      }
      if (selected < topVisible) {
        topVisible = selected;
      }
      drawBLEDeviceList(topVisible, selected);
      delay(150);
    }

    if (!digitalRead(BTN_SELECT)) {
      while (!digitalRead(BTN_SELECT)); 
      break;
    }
  }

  advertiseBLEDevice(fakeDevices[selected]);
}

#endif
