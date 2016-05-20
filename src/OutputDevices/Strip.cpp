#include "Strip.h"

Adafruit_NeoPixel lib = Adafruit_NeoPixel(60, D6, NEO_GRB + NEO_KHZ800);

Strip::Strip(String id, String label, char* type) : Output(id, label, type) {
  lib.begin();
  lib.show();
}

void Strip::callback(char* topic, JsonObject& payload) {
  int r = payload["r"];
  int g = payload["g"];
  int b = payload["b"];

  update(r, g, b);
}

void Strip::update(int r, int g, int b)
{
  for(int i=0; i<lib.numPixels(); i++) {
      int color = lib.Color(r, g, b);
      lib.setPixelColor(i, color);
  }
  lib.show();
}

void Strip::rainbow(int wait) {
  int i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<lib.numPixels(); i++) {
      lib.setPixelColor(i, wheel((i+j) & 255));
    }
    lib.show();
    delay(wait);
  }
}

int Strip::wheel(byte position) {
  if(position < 85) {
   return lib.Color(position * 3, 255 - position * 3, 0);
 } else if(position < 170) {
   position -= 85;
   return lib.Color(255 - position * 3, 0, position * 3);
  } else {
   position -= 170;
   return lib.Color(0, position * 3, 255 - position * 3);
  }
}
