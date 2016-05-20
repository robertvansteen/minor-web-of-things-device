#include "Sound.h"

Sound::Sound(String id, String label, char* type)
: Input(id, label, type)
{}

boolean Sound::loop() {
  long now = millis();

  if(now - lastReading < 250) {
    return false;
  }

  int reading = analogRead(A0);
  // int reading = Serial.read();
  array.push_back(reading);

  lastReading = now;

  if(now - lastPublish < 10000) {
    return false;
  }

  int size = array.size();
  int total = 0;
  double average = 0.0;
  for(int i = 0; i < size; i++)
  {
    total += array[i];
  }

  average = (total / size);

  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["value"] = average;
  publish(root);

  array.clear();
  lastPublish = now;
}
