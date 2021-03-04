#include <FastLED.h>
#include "../../include/ProjectConstants.h"

void SetStripColor(struct CRGB* leds, uint8_t hue, uint8_t saturation, uint8_t value){
    // Set a HSV color to the whole strip at once, and show it.
    fill_solid(leds, NUM_LEDS, CHSV(hue, saturation, value));
    FastLED.show();
}