#include "InputManager.h"

LDR ldr(String("LDR"), String("Light sensor"), "light");
Temp temp(String("temp"), String("Temperature sensor"), "chart");
Sound sound(String("sound"), String("Sound sensor"), "chart");

/**
 * Constructor.
 * Register the input manager with the pubsub instance.
 */
InputManager::InputManager()
{
  PubSub::Instance()->addInputManager(this);
}

/**
 * Connect the input manager by letting the server know what inputs are on the
 * device.
 * Call the add method with a reference to a Input instance to add your own
 * inputs.
 */
void InputManager::connect()
{
  add(&temp);

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

/**
 * Add a input to the manager.
 */
void InputManager::add(Input* device)
{
  devices.push_back(device);
  Serial.print("New input device connected: ");
  Serial.println(device->label);
}

/**
 * The loop method is called every loop on the device.
 * This will loop through all the registered inputs & call the loop method on
 * that instance.
 */
void InputManager::loop()
{
  for(auto& device : devices) {
    device->loop();
  }
}
