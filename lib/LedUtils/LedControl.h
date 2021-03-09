#pragma once
#include <FastLED.h>
#include "../../include/ProjectConstants.h"



void SetStripColor(struct CRGB* leds, uint8_t hue, uint8_t saturation, uint8_t value);
void SetStripColorRGB(struct CRGB* leds, uint8_t r, uint8_t g, uint8_t b);
void AmberToSunlight(struct CRGB* leds, int introTimeSec, int transitionTimeSec, int dwellTimeSec);
