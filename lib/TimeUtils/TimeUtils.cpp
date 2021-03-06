#include "TimeUtils.h"
#include "../../include/ProjectConstants.h"

const char* GetWeekday(int dayNumber){
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
    // sun 1, sat 7
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

    for (int d=0; d<6; d++){
    if (nextAlarm->DayOfWeekHist[d] == 1){
      Serial.println(GetWeekday(d));
    }
  }

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


void Ticker(int updateTimeSec, s_alarmVars* currentAlarm){
    int flag=0;
    unsigned long timeNow = millis();
    while (millis() <= timeNow + updateTimeSec*1000){
        ESP.wdtFeed();
        yield();
    }
    // Time had passed, check the current time!
    flag = checkCurrentTime(currentAlarm->nextAlarm);
    if (flag){
        AmberToSunlight(currentAlarm->ledArray, 30, 30, 30);
    }
    return;
}



void dbgPrintEEPROMAlarm(s_alarmVars* currentAlarm){
    
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
}
// Things we get from Blynk: Day(1-7), Hour(0-24), Minute(0-60)