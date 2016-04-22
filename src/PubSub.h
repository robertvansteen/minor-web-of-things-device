#ifndef PUBSUB_H
#define PUBSUB_H

#undef max
#include <vector>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

class OutputManager;
class InputManager;

class PubSub
{
  public:
    static PubSub* Instance();
    void loop();
    boolean connect();
    void publish(String topic);
    void publish(String topic, JsonObject& payload);
    void publish(String topic, JsonArray& payload);
    void subscribe(String topic);
    void addOutputManager(OutputManager* outputManager);
    void addInputManager(InputManager* inputManager);
    void callback(char* topic, byte* payload, unsigned int length);
  private:
    PubSub(const char* host, const int port);
    static PubSub* _instance;
    void ping();
    void registerDevice();
    String getTopic(String topic);
    const char* _name;
    long lastReconnectAttempt;
    long lastPing;
    OutputManager* outputManager;
    InputManager* inputManager;
    PubSubClient _client;
    WiFiClient _wifi;
};

#endif
