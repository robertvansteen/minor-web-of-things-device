#include <Arduino.h>
#include "Output.h"

Output::Output (String id, String label, char* type)
  : id(id), label(label), type(type)
  {}
