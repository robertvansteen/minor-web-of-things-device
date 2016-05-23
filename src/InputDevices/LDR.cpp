#include "LDR.h"

LDR::LDR(String id, String label, char* type)
: Input(id, label, type)
{}

boolean LDR::loop() {
  long now = millis();
  if(now - lastReading < 10000) {
    return false;
  }

  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["value"] = analogRead(A0);
  publish(root);

  lastReading = millis();
}
