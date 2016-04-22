#ifndef STRIP_H
#define STRIP_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "../Output.h"

class Strip: public Output
{
public:
  Strip(String id, String label, char* type);
  void callback(char* topic, JsonObject& payload);
protected:
  void update(int r, int g, int b);
  void rainbow(int wait);
  int wheel(byte position);
};

#endif
