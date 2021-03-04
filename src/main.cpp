#include <stdint.h>
#include <FastLED.h>

#include "ProjectConstants.h"
#include "LedControl.h"

// Define an LED array
CRGB leds[NUM_LEDS];

void setup() { 
    // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
}

void loop() { 
  SetStripColor(leds, 160, 250, 160);
  delay(500);
  SetStripColor(leds, 120, 250, 160);
  delay(500);
}