#ifndef TEMP_H
#define TEMP_H

#include <DHT.h>
#include <Arduino.h>
#include "../Input.h"
#include "../PubSub.h"

class Temp: public Input
{
public:
  Temp(String id, String label, char* type);
  boolean loop();
};

#endif
