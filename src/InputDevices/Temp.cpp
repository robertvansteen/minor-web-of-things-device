#include "Temp.h"

DHT dht(D2, DHT22);

Temp::Temp(String id, String label, char* type)
: Input(id, label, type)
{
  dht.begin();
}

boolean Temp::loop() {
  long now = millis();
  if(now - lastReading < 10000) {
    return false;
  }

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    return false;
  }

  float hic = dht.computeHeatIndex(t, h, false);

  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["value"] = hic;
  publish(root);

  lastReading = millis();
}
