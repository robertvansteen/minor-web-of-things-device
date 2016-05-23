#include <GDBStub.h>

#include "env.h"
#include "Wifi.h"
#include "PubSub.h"
#include "OutputManager.h"
#include "InputManager.h"

Wifi wifi(ENV_SSID, ENV_PASSWORD);
OutputManager outputManager;
InputManager inputManager;

void setup(void) {
  Serial.begin(9600);

  // Set up input & output.
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(A0, INPUT);

  // Turn off the builtin led.
  digitalWrite(BUILTIN_LED, HIGH);

  // Connect with the wifi.
  wifi.connect();

  // Set up pubsub (MQTT) singleton & connect with the broker.
  PubSub::Instance()->connect();

  // Connect the outputs.
  outputManager.connect();

  // Connect the inputs.
  inputManager.connect();
}

void loop(void) {
  // Keep the MQTT connection alive.
  PubSub::Instance()->loop();
}
