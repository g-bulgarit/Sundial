#include <stdint.h>
#include <FastLED.h>

#include "ProjectConstants.h"
#include "LedControl.h"

// Define an LED array
CRGB leds[NUM_LEDS];

void setup() { 
    pinMode(5, OUTPUT);
    Serial.begin(9600);
    // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
}

void loop() { 
  AmberToSunlight(leds, 30);
  delay(1000);
}