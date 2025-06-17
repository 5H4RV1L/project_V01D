#ifndef WIFI_SELECTOR_H
#define WIFI_SELECTOR_H

#include <WiFi.h>
#include "esp_wifi.h"
extern Adafruit_SSD1306 display;

#define MAX_NETWORKS 10
int selectedNetwork = 0;
int networkCount = 0;
String ssidList[MAX_NETWORKS];
uint8_t bssidList[MAX_NETWORKS][6];

void scanNetworks() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  networkCount = WiFi.scanNetworks();
  if (networkCount > MAX_NETWORKS) networkCount = MAX_NETWORKS;

  for (int i = 0; i < networkCount; i++) {
    ssidList[i] = WiFi.SSID(i);
    memcpy(bssidList[i], WiFi.BSSID(i), 6);
  }

  Serial.printf("Found %d networks\n", networkCount);
}


void showNetworkSelector() {
  scanNetworks();
  
  if (networkCount == 0) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("No networks found");
  display.display();
  delay(2000);
  return;
}

  while (true) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Select SSID:");

    for (int i = 0; i < networkCount; i++) {
      if (i == selectedNetwork) display.print("> ");
      else display.print("  ");

      display.println(ssidList[i]);
    }
    display.display();

    if (!digitalRead(12)) {
      selectedNetwork = (selectedNetwork - 1 + networkCount) % networkCount;
      delay(200);
    }
    if (!digitalRead(13)) {
      selectedNetwork = (selectedNetwork + 1) % networkCount;
      delay(200);
    }
    if (!digitalRead(16)) {
      break;
    }
  }

  WiFi.mode(WIFI_OFF);
  delay(300);
}
#endif
