#ifndef BLE_SPAMMER_H
#define BLE_SPAMMER_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEAdvertising.h>

extern Adafruit_SSD1306 display;

bool bleRunning = false;

void startBLESpam() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("BLE Spam started");
  display.display();

  BLEDevice::init("");
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

  BLEAdvertisementData adData;
  adData.setFlags(0x06); 
  adData.setName("Free Bluetooth");
  pAdvertising->setAdvertisementData(adData);

  pAdvertising->start();
  bleRunning = true;

  Serial.println("BLE Spammer: Advertising started");

  while (digitalRead(16)) {
    delay(100);
  }

  pAdvertising->stop();
  BLEDevice::deinit(true);
  bleRunning = false;

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("BLE Spam stopped");
  display.display();
  delay(1000);
}

#endif
