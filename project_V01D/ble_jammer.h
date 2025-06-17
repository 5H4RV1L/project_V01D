#ifndef BLE_JAMMER_H
#define BLE_JAMMER_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEAdvertising.h>

extern Adafruit_SSD1306 display;

#define BTN_SELECT 16

void startBLEJammer() {
  BLEDevice::init("");
  BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
  BLEAdvertisementData adData;
  BLEAdvertisementData scanData;

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("BLE Jammer");
  display.println("Status: ACTIVE");
  display.println("Press SELECT to stop");
  display.display();

  while (digitalRead(BTN_SELECT)) {
    char name[10];
    sprintf(name, "VOID_%02X", random(0x00, 0xFF));

    adData.setName(name);
    adData.setFlags(0x06); 

    pAdvertising->setAdvertisementData(adData);
    pAdvertising->setScanResponseData(scanData);
    pAdvertising->start();
    delay(10);  

    pAdvertising->stop();
    delay(1);  

    static int ch = 37;
    ch = (ch == 39) ? 37 : ch + 1;
    esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, ESP_PWR_LVL_P9);
    
  }

  BLEDevice::deinit(true);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Jammer Stopped");
  display.display();
  delay(1500);
}

#endif
