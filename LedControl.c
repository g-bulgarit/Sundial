#include <FastLED.h>
#include <Constants.h>

void SetStripColor(CRGB leds, int hue, int saturation, int value){
    // Set a HSV color to the whole strip at once, and show it.
    fill_solid( &(leds[i]), NUM_LEDS, CHSV(hue, saturation, value));
    FastLED.show();
}