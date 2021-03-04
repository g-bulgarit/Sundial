#include <FastLED.h>

#include "Constants.h"
#include "LedControl.h"

// Define an LED array
CRGB leds[NUM_LEDS];

void setup() { 
    // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
}

void loop() { 
  SetStripColor(leds, 160, 250, MAX_LED_BRIGHTNESS);
  delay(500);
  SetStripColor(leds, 120, 250, MAX_LED_BRIGHTNESS);
  delay(500);
}