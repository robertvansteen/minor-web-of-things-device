#ifndef OUTPUT_H
#define OUTPUT_H

#include <ArduinoJson.h>
#include "env.h"
#include "PubSub.h"

class Output
{
public:
  Output(String id, String label, char* type);
  String id;
  String label;
  char* type;
  virtual void callback(char* topic, JsonObject& payload) = 0;
};

#endif
