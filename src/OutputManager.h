#undef max
#include <vector>
#include <ArduinoJson.h>
#include "PubSub.h"
#include "Output.h"
#include "OutputDevices/Light.h"
#include "OutputDevices/Strip.h"

class OutputManager
{
  public:
    OutputManager();
    void connect();
    void add(Output* output);
    void callback(char* topic, JsonObject& payload);
    boolean isTopic(char* topic, String candidate);
  private:
    std::vector<Output *> devices;
    int count = 0;
};
