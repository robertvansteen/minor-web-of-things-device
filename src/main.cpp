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
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(A0, INPUT);

  digitalWrite(BUILTIN_LED, HIGH);

  wifi.connect();
  PubSub::Instance()->connect();
  outputManager.connect();
  inputManager.connect();
}

void loop(void) {
  PubSub::Instance()->loop();
}
