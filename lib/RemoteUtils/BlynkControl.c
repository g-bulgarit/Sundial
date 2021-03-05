// Blynk Widgets Layout:
//  Time Input on V1

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

void StartBlynkConnectivity(){
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
        Serial.println("I was clicked");
    }

}