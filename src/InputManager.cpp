#include "InputManager.h"

LDR ldr(String("LDR"), String("Light sensor"), "light");
Temp temp(String("temp"), String("Temperature sensor"), "chart");
Sound sound(String("sound"), String("Sound sensor"), "chart");

InputManager::InputManager()
{
  PubSub::Instance()->addInputManager(this);
}

void InputManager::connect()
{
  add(&temp);
  // add(&ldr);
  // add(&sound);

  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  JsonArray& deviceArray = root.createNestedArray("devices");
  for(int i = 0; i < devices.size(); i++) {
    JsonObject& object = jsonBuffer.createObject();
    object["id"] = devices[i]->id;
    object["label"] = devices[i]->label;
    object["type"] = devices[i]->type;
    deviceArray.add(object);
  }

  PubSub::Instance()->publish("register/input", root);
}

void InputManager::add(Input* device)
{
  devices.push_back(device);
  Serial.print("New input device connected: ");
  Serial.println(device->label);
}

void InputManager::loop()
{
  for(auto& device : devices) {
    device->loop();
  }
}
