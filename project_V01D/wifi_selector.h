#ifndef WIFI_SELECTOR_H
#define WIFI_SELECTOR_H

#include <WiFi.h>
#include "esp_wifi.h"

extern Adafruit_SSD1306 display;
extern const int btnDown;  // Ensure these are declared
extern const int btnSelect;

#define MAX_NETWORKS 4      // Reduced for ESP32-CAM stability
int selectedNetwork = 0;
int networkCount = 0;
String ssidList[MAX_NETWORKS];
uint8_t bssidList[MAX_NETWORKS][6];

void scanNetworks() {
  // 1. Hard reset WiFi
  esp_wifi_stop();
  esp_wifi_deinit();
  delay(200);
  
  // 2. Initialize with minimal config
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  cfg.nvs_enable = 0;       // Disable NVS for temporary scan
  esp_wifi_init(&cfg);
  esp_wifi_set_mode(WIFI_MODE_STA);
  esp_wifi_start();
  delay(100);

  // 3. Scan with timeout
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Scanning...");
  display.display();
  
  WiFi.scanNetworks(true, true); // Async scan (non-blocking)
  
  // Wait for scan with timeout
  unsigned long start = millis();
  while(WiFi.scanComplete() < 0 && millis()-start < 10000) {
    delay(100);
  }

  networkCount = WiFi.scanComplete();
  if(networkCount <= 0) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("No networks found");
    display.display();
    networkCount = 0;
    goto cleanup;  // Jump to memory cleanup
  }

  // 4. Store results
  networkCount = min(networkCount, MAX_NETWORKS);
  for(int i=0; i<networkCount; i++) {
    ssidList[i] = WiFi.SSID(i).substring(0, 12); // Trim SSIDs
    memcpy(bssidList[i], WiFi.BSSID(i), 6);
  }

cleanup:
  // 5. Critical cleanup
  WiFi.scanDelete();
  esp_wifi_stop();
  esp_wifi_deinit();
}

void showNetworkSelector() {
  scanNetworks();
  
  if(networkCount == 0) {
    delay(2000);
    return;
  }

  while(true) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Select Network:");
    
    // Paginated display (3 networks max)
    int startIdx = max(0, selectedNetwork - 1);
    for(int i=startIdx; i<min(startIdx+3, networkCount); i++) {
      display.print(i == selectedNetwork ? "> " : "  ");
      display.println(ssidList[i]);
    }
    display.display();

    // Button handling
    if(!digitalRead(btnDown)) {
      selectedNetwork = (selectedNetwork + 1) % networkCount;
      delay(200);
    }
    if(!digitalRead(btnSelect)) {
      break;
    }
  }
}
#endif
