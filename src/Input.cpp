#include <Arduino.h>
#include "Input.h"

Input::Input (String id, String label, char* type)
  : id(id), label(label), type(type)
  {}

void Input::publish(JsonObject& payload)
{
  String topic = String("input/" + id);
  PubSub::Instance()->publish(topic, payload);
}
