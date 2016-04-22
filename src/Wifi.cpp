#include "Wifi.h"
#include <ESP8266WiFi.h>

Wifi::Wifi(char const* ssid, char const* password)
{
  _ssid = ssid;
  _password = password;
  WiFi.begin(ssid, password);
}

/**
 * Attempt a connection with the WiFi network.
 */
void Wifi::connect() {
  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(_ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
