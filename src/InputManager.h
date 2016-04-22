#ifndef INPUT_MANGER_H
#define INPUT_MANAGER_H

#undef max
#include <Arduino.h>
#include <vector>
#include <ArduinoJson.h>
#include "PubSub.h"
#include "Input.h"
#include "InputDevices/LDR.h"
#include "InputDevices/Temp.h"

class InputManager
{
  public:
    InputManager();
    void connect();
    void loop();
    void add(Input* input);
  private:
    std::vector<Input *> devices;
};

#endif
