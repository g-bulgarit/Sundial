#include "LedControl.h"

void SetStripColor(struct CRGB* leds, uint8_t hue, uint8_t saturation, uint8_t value){
    // Set a HSV color to the whole strip at once, and show it.
    fill_solid(leds, NUM_LEDS, CHSV(hue, saturation, value));
    FastLED.show();
}

void SetStripColorRGB(struct CRGB* leds, uint8_t r, uint8_t g, uint8_t b){
    // Set a RGB color to the whole strip at once, and show it.
    FastLED.setBrightness(MAX_LED_BRIGHTNESS);
    fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
    FastLED.show();
}

void AmberToSunlight(struct CRGB* leds, int introTimeSec, int transitionTimeSec, int dwellTimeSec){
    // Transition from amber color to `sunlight` color, with parameters:
    //      ::transitionTimeSec - Time from start (amber) to finish
    //      ::dwellTimeSec      - Time to stay lit with the last color of the sequence. 
    int color_steps = hue_sunlight - hue_amber;
    int isat;
    int ihue;
    // Fade to red
    for (int f=0; f < MAX_LED_BRIGHTNESS; f++){
        SetStripColor(leds, hue_amber, 255, f);
        yield();
        FastLED.delay(introTimeSec*1000 / color_steps);
    }

    // Fade colors
    for (ihue = hue_amber; ihue < (hue_amber + color_steps); ihue++){
        isat = 255-(ihue*1.5);
        SetStripColor(leds, ihue, isat, MAX_LED_BRIGHTNESS);
        
        #ifdef DEBUG
        Serial.print("Hue of ");
        Serial.print(ihue);
        Serial.print(" out of ");
        Serial.println(color_steps);
        #endif

        FastLED.delay(transitionTimeSec*1000 / color_steps);
    }
    
    // Dwell
    for (int j = 0; j < dwellTimeSec; j++){
        SetStripColor(leds, ihue, isat, MAX_LED_BRIGHTNESS);
        FastLED.delay(1000);
    }

    // Fade out
    for (int f=MAX_LED_BRIGHTNESS; f > 0; f--){
        SetStripColor(leds, ihue, isat, f);
        FastLED.delay(introTimeSec*1000 / color_steps);
    }

    SetStripColor(leds, 0, 0, 0); // turn off leds
}