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
    return "fail";
}


void checkAlarm(s_alarmVars *currentAlarm){
    #ifdef DEBUG
    Serial.println("[!] Data:");
    Serial.print("[    >] Alarm Hour: ");
    Serial.println(currentAlarm->nextAlarm->Hour);
    Serial.print("[    >] Alarm Minute: ");
    Serial.println(currentAlarm->nextAlarm->Minute);
    Serial.println("[    >] Alarm days: ");
    for (int d=0; d<7; d++){
        if (currentAlarm->nextAlarm->DayOfWeekHist[d] == 1){
        Serial.println(GetWeekday(d));
        }
    }

    Serial.print("Current time is: ");
    Serial.print(hour());
    Serial.print(":");
    Serial.println(minute());
  #endif
    
    AmberToSunlight(currentAlarm->ledArray, 30, 30, 30);


    // if (currentAlarm->nextAlarm->DayOfWeekHist[weekday()] == 1){
    //     // Today, the alarm should sound!

    //     #ifdef DEBUG
    //     Serial.println("The day matches!");
    //     #endif

    //     if (currentAlarm->nextAlarm->Hour == hour()){
    //         #ifdef DEBUG
    //         Serial.println("The hour matches!");
    //         #endif
    //         // This hour, the alarm should sound!
    //         int minLower, minUpper;
    //         minLower = currentAlarm->nextAlarm->Minute-1;
    //         minUpper = currentAlarm->nextAlarm->Minute+1;

    //         if (minute() >= minLower && minute() <= minUpper){
    //             // This is the perfect time to sound the alarm!
    //             Serial.println("Raising the alarm!");
    //             AmberToSunlight(currentAlarm->ledArray, 30, 30, 30);
    //         }
    //     }
    // }

    return;
}

// Things we get from Blynk: Day(1-7), Hour(0-24), Minute(0-60)