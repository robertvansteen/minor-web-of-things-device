#include <Arduino.h>
#include <ArduinoJson.h>

#include "OutputManager.h"

Light light(String("LED"), String("Build-in LED"), "switch");
Strip strip(String("strip"), String("Temperature color"), "switch");

/**
 * Constructor.
 * Register the output manager with the pubsub instance.
 */
OutputManager::OutputManager()
{
  PubSub::Instance()->addOutputManager(this);
}

/**
 * Connect the output manager by letting the server know what outputs are on the
 * device.
 * Call the add method with a reference to a Output instance to add your own
 * outputs.
 */
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

/**
 * Add a output to the manager.
 */
void OutputManager::add(Output* device)
{
  devices.push_back(device);
  Serial.print("New output device connected: ");
  Serial.println(device->label);
  PubSub::Instance()->subscribe(String("output/" + device->id + "/set"));
}

/**
 * Callback from MQTT. This is called when the server sends a message to us.
 * Here we check if it matches a topic from an output, if so we call the callback
 * method on that instance.
 */
void OutputManager::callback(char* topic, JsonObject& payload)
{
  for(auto& device : devices) {
    if(isTopic(topic, device->id)) {
      device->callback(topic, payload);
    }
  }
}

/**
 * Check if the topic matches an output ID.
 */
boolean OutputManager::isTopic(char* topic, String id)
{
  String candidate = String(ENV_DEVICE_NAME + "/output/" + id + "/set");
  char buffer[128];
  candidate.toCharArray(buffer, 128);
  return strcmp(topic, buffer) == 0;
}
