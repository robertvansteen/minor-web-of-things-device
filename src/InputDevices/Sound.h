#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include <Arduino.h>
#include "../Input.h"
#include "../PubSub.h"

class Sound: public Input
{
public:
  Sound(String id, String label, char* type);
  boolean loop();
protected:
  std::vector<int> array;
};

#endif
