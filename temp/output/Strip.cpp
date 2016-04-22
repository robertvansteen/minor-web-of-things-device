#include "Strip.h"
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, D6, NEO_GRB + NEO_KHZ800);

Strip::Strip()
{
  strip.begin();
  strip.show();
}

void Strip::update(int r, int g, int b)
{
  for(int i=0; i<strip.numPixels(); i++) {
      int color = strip.Color(r, g, b);
      strip.setPixelColor(i, color);
      strip.show();
  }
}
