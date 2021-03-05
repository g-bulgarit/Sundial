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


void checkAlarm(stAlarms* currentAlarm){
    
    #ifdef DEBUG
    Serial.println("[!] Data:");
    Serial.print("[    >] Alarm Hour: ");
    Serial.println(currentAlarm->Hour);
    Serial.print("[    >] Alarm Minute: ");
    Serial.println(currentAlarm->Minute);
    Serial.println("[    >] Alarm days: ");
    for (int d=0; d<7; d++){
        if (currentAlarm->DayOfWeekHist[d] == 1){
        Serial.println(GetWeekday(d));
        }
    }
  #endif

    // int currentHour = hour();
    // int currentMinute = minute();
    // int currentDay = weekday();

    return;

}

// Things we get from Blynk: Day(1-7), Hour(0-24), Minute(0-60)