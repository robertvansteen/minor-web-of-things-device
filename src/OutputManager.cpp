#include <Arduino.h>
#include <ArduinoJson.h>

#include "OutputManager.h"

Light light(String("LED"), String("Build-in LED"), "switch");
Strip strip(String("strip"), String("Temperature color"), "switch");

OutputManager::OutputManager()
{
  PubSub::Instance()->addOutputManager(this);
}

void OutputManager::connect()
{
  add(&light);
  add(&strip);

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

  PubSub::Instance()->publish("register/output", root);
}

void OutputManager::add(Output* device)
{
  devices.push_back(device);
  Serial.print("New output device connected: ");
  Serial.println(device->label);
  PubSub::Instance()->subscribe(String("output/" + device->id + "/set"));
}

void OutputManager::callback(char* topic, JsonObject& payload)
{
  for(auto& device : devices) {
    if(isTopic(topic, device->id)) {
      device->callback(topic, payload);
    }
  }
}

boolean OutputManager::isTopic(char* topic, String id)
{
  String candidate = String(ENV_DEVICE_NAME + "/output/" + id + "/set");
  char buffer[128];
  candidate.toCharArray(buffer, 128);
  return strcmp(topic, buffer) == 0;
}
