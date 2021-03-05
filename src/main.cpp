#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

#include "ProjectConstants.h"
#include "SecretKeys.h"
#include "LedControl.h"
#include "TimeUtils.h"

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

// Blynk Functions
BLYNK_WRITE(V1) {
  TimeInputParam t(param);
        // Process start time
        if (t.hasStartTime())
        {
            Serial.println(String("Start: ") +
                        t.getStartHour() + ":" +
                        t.getStartMinute() + ":" +
                        t.getStartSecond());
        }
        else if (t.isStartSunrise())
        {
            Serial.println("Start at sunrise");
        }
        else if (t.isStartSunset())
        {
            Serial.println("Start at sunset");
        }
        else
        {
            // Do nothing
        }

        // Process stop time

        if (t.hasStopTime())
        {
            Serial.println(String("Stop: ") +
                        t.getStopHour() + ":" +
                        t.getStopMinute() + ":" +
                        t.getStopSecond());
        }
        else if (t.isStopSunrise())
        {
            Serial.println("Stop at sunrise");
        }
        else if (t.isStopSunset())
        {
            Serial.println("Stop at sunset");
        }
        else
        {
            // Do nothing: no stop time was set
        }

        // Process timezone
        // Timezone is already added to start/stop time

        Serial.println(String("Time zone: ") + t.getTZ());

        // Get timezone offset (in seconds)
        Serial.println(String("Time zone offset: ") + t.getTZ_Offset());

        // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)

        for (int i = 1; i <= 7; i++) {
            if (t.isWeekdaySelected(i)) {
            Serial.println(String("Day ") + i + " is selected");
            }
        }

        Serial.println();
}

BLYNK_WRITE(V2){
    String currentTime = String(hour()) + ":" + minute() + ":" + second();
    Serial.print("Time now is:");
    Serial.println(currentTime);
    String currentWeekday = GetWeekday(weekday());
    Serial.print("Time day is:");
    Serial.println(currentWeekday);
    AmberToSunlight(leds, 30 ,30, 20);
    
}


void loop() { 
  Blynk.run();
}