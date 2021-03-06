#include "TimeUtils.h"
#include "../../include/ProjectConstants.h"

const char* GetWeekday(int dayNumber){
    // Convert Blynk weekday to text for debugging
    switch (dayNumber){
        case 6: return "Sunday";
        case 0: return "Monday";
        case 1: return "Tuesday";
        case 2: return "Wednesday";
        case 3: return "Thursday";
        case 4: return "Friday";
        case 5: return "Saturday";
    }
    return "fail";
}

int TimeLibConversion(int dayNumber){
    // Convert TimeLib weekday to blynk-suitable numbers.
    // This part took a toll on my soul, and I hope to recover sometime.
    switch (dayNumber){
        case 1: return 6;
        case 2: return 0;
        case 3: return 1;
        case 4: return 2;
        case 5: return 3;
        case 6: return 4;
        case 7: return 5;
    }
    return -1;
}

int checkCurrentTime(stAlarms* nextAlarm){
    // Check if the day, hour and minute matches, if so - wake.

     if (nextAlarm->DayOfWeekHist[TimeLibConversion(weekday())] == 1){
        // Today, the alarm should sound!

        #ifdef DEBUG
        Serial.println("The day matches!");
        #endif

        if (nextAlarm->Hour == hour()){
            #ifdef DEBUG
            Serial.println("The hour matches!");
            #endif
            // This hour, the alarm should sound!
            int minLower, minUpper;
            minLower = nextAlarm->Minute-1;
            minUpper = nextAlarm->Minute+1;

            if (minute() >= minLower && minute() <= minUpper){
                // This is the perfect time to sound the alarm!
                return 1;
            }
        }
    }
    // It's not the right time to wake up, return 0.
    return 0;
}
