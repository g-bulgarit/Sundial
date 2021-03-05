#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

#include "ProjectConstants.h"
#include "SecretKeys.h"
#include "LedControl.h"
#include "BlynkControl.h"

// Define an LED array
CRGB leds[NUM_LEDS];
WidgetRTC rtc;


void setup() { 
  // Initiallize pins
  pinMode(5, OUTPUT);

  // Initiallize serial for debug
  Serial.begin(9600);

  // Set LED Type
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical

  // Initiallize Blynk connection  
  Blynk.begin(sBlynkAuthToken, sWifiAP, sWifiPwd);

  // Initiallize RTC
  rtc.begin();
  setSyncInterval(5 * 60); // Sync interval in seconds (5 minutes)

}

void loop() { 
  Blynk.run();
}