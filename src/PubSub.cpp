#include "env.h"
#include "PubSub.h"
#include "OutputManager.h"
#include "InputManager.h"

PubSub* PubSub::_instance = NULL;

PubSub* PubSub::Instance()
{
  if(!_instance) {
    _instance = new PubSub(ENV_PUBSUB_HOST, ENV_PUBSUB_PORT);
  }

  return _instance;
}

/**
 * Constructor.
 */
PubSub::PubSub(const char* host, const int port) :
  _client(PubSubClient()),
  _wifi(WiFiClient())
{
  _client.setClient(_wifi);
  _client.setServer(host, port);
  _client.setCallback([this] (char* topic, byte* payload, unsigned int length) {
    this->callback(topic, payload, length);
  });
}

/**
 * Connect with the MQTT server.
 */
boolean PubSub::connect() {
  Serial.print("Connecting to PubSub server..");
  while (!_client.connected()) {
    Serial.print(".");
    char buffer[32];
    String name = ENV_DEVICE_NAME;
    name.toCharArray(buffer, 32);
    _client.connect(buffer);
    delay(100);
  }

  Serial.println(" success!");
  registerDevice();
  return _client.connected();
}

/**
 * Set output manager.
 */
void PubSub::addOutputManager(OutputManager* manager)
{
  outputManager = manager;
}

/**
 * Set input manager.
 */
void PubSub::addInputManager(InputManager* manager)
{
  inputManager = manager;
}

/**
 * Get the topic by appending the local topic with the namespace of the device.
 */
String PubSub::getTopic(String topic)
{
  topic = String(ENV_DEVICE_NAME + "/" + topic);
  return topic;
}

/**
 * Loop, keep the MQTT connection alive.
 * Reconnect if necessary.
 * Call the loop method on the input manager.
 */
void PubSub::loop()
{
  if (!_client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 10000) {
        lastReconnectAttempt = now;
        // Attempt to reconnect
        if (connect()) {
          lastReconnectAttempt = 0;
        }
      }
  } else {
    ping();
    _client.loop();
    inputManager->loop();
  }
}

/**
 * Register a device.
 */
void PubSub::registerDevice()
{
  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["name"] = ENV_DEVICE_NAME;
  root["label"] = ENV_DEVICE_LABEL;

  publish(String("register"), root);
  lastPing = millis();
}

/**
 * Ping the server to know we are still alive.
 */
void PubSub::ping()
{
  long now = millis();
  if(now - lastPing > 60000) {
    publish("ping");
    lastPing = now;
  }
}

/**
 * Publish something on a topic without a message.
 */
void PubSub::publish(String topic)
{
  String str = getTopic(topic);
  _client.publish(str.c_str(), "");
}

/**
 * Publish something on a topic, with JsonObject as message.
 */
void PubSub::publish(String topic, JsonObject& payload)
{
  String str = getTopic(topic);
  char buffer[1024];
  payload.printTo(buffer, sizeof(buffer));
  Serial.print("Publishing new message to: ");
  Serial.println(str);
  _client.publish(str.c_str(), buffer);
}

/**
 * Publish something on a topic, with JsonArray as message.
 */
void PubSub::publish(String topic, JsonArray& payload)
{
  String str = getTopic(topic);
  char buffer[1024];
  payload.printTo(buffer, sizeof(buffer));
  Serial.print("Publishing new message to: ");
  Serial.println(str);
  _client.publish(str.c_str(), buffer);
}

/**
 * Subscribe on a topic.
 * Device ID will be automatically prepended.
 */
void PubSub::subscribe(String topic)
{
  String str = getTopic(topic);
  _client.subscribe(str.c_str());
}

/**
 * Callback, this function is called when a message is received by the device.
 */
void PubSub::callback(char* topic, byte* payload, unsigned int length) {
  char data[80];

  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++)
  {
    data[i] = (char)payload[i];
    Serial.print((char)payload[i]);
  }
  Serial.println();

  StaticJsonBuffer<256> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(data);

  outputManager->callback(topic, root);
}
