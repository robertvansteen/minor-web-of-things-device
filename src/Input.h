#ifndef INPUT_H
#define INPUT_H

#include "PubSub.h"

class Input
{
public:
  Input(String id, String label, char* type);
  String id;
  String label;
  char* type;
  virtual boolean loop() = 0;
protected:
  long lastPublish;
  long lastReading;
  void publish(JsonObject& payload);
};

#endif
