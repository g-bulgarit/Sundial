#include <FastLED.h>
#include "../../include/ProjectConstants.h"

void SetStripColor(struct CRGB* leds, uint8_t hue, uint8_t saturation, uint8_t value){
    // Set a HSV color to the whole strip at once, and show it.
    fill_solid(leds, NUM_LEDS, CHSV(hue, saturation, value));
    FastLED.show();
}

void AmberToSunlight(struct CRGB* leds, int transitionTimeSec){
    int color_steps = hue_sunlight - hue_amber;
    for (int ihue = hue_amber; ihue < (hue_amber + color_steps); ihue++){
        SetStripColor(leds, ihue, 255, 20);
        
        #ifdef DEBUG
        Serial.print("Hue of ");
        Serial.print(ihue);
        Serial.print(" out of ");
        Serial.println(color_steps);
        #endif
        
        delay(transitionTimeSec*1000 / color_steps);
    }

}