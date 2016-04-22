#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>
#include "../Output.h"

class Light: public Output
{
public:
  Light(String id, String label, char* type);
  void callback(char* topic, JsonObject& payload);
};

#endif
