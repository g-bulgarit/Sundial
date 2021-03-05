#include "TimeUtils.h"
#include "../../include/ProjectConstants.h"

const char* GetWeekday(int dayNumber){
    switch (dayNumber){
        case 1: return "Sunday";
        case 2: return "Monday";
        case 3: return "Tuesday";
        case 4: return "Wednesday";
        case 5: return "Thursday";
        case 6: return "Friday";
        case 7: return "Saturday";
    }
}


void checkAlarm(std::pair<stAlarms*, CRGB*> *currentAlarm){
    
    #ifdef DEBUG
    Serial.println("[!] Data:");
    Serial.print("[    >] Alarm Hour: ");
    Serial.println(currentAlarm->first->Hour);
    Serial.print("[    >] Alarm Minute: ");
    Serial.println(currentAlarm->first->Minute);
    Serial.println("[    >] Alarm days: ");
    for (int d=0; d<7; d++){
        if (currentAlarm->first->DayOfWeekHist[d] == 1){
        Serial.println(GetWeekday(d));
        }
    }
  #endif

    if (currentAlarm->first->DayOfWeekHist[weekday()] == 1){
        // Today, the alarm should sound!

        if (currentAlarm->first->Hour == hour()){
            // This hour, the alarm should sound!
            int minLower, minUpper;
            minLower = minute()-1;
            minUpper = minute()+1;

            if (minute() >= minLower && minute() <= minUpper){
                // This is the perfect time to sound the alarm!
                AmberToSunlight(currentAlarm->second, 30, 30, 30);
            }
        }
    }

    return;
}

// Things we get from Blynk: Day(1-7), Hour(0-24), Minute(0-60)