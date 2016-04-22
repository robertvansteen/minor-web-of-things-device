#ifndef LDR_H
#define LDR_H

#include <Arduino.h>
#include "../Input.h"
#include "../PubSub.h"

class LDR: public Input
{
public:
  LDR(String id, String label, char* type);
  boolean loop();
};

#endif
