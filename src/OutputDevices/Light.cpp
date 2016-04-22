#include "Light.h"

Light::Light(String id, String label, char* type) : Output(id, label, type) {}

void Light::callback(char* topic, JsonObject& payload) {
  digitalWrite(BUILTIN_LED, !payload["value"]);

  String replyTopic = String("output/" + id);
  PubSub::Instance()->publish(replyTopic , payload);
}
