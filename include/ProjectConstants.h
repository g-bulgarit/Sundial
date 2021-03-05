#pragma once

// PINOUT
const int DATA_PIN = 5; // digital pin 1 on the Wemos D1Mini afaik

// LED
const int MAX_LED_BRIGHTNESS = 80;
#define NUM_LEDS 60

// Colors
const int hue_amber = 0;
const int hue_sunlight = 60;

// Blynk Debug
#define BLYNK_PRINT Serial
#define DEBUG