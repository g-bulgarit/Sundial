#pragma once
#include <TimeLib.h>
#include "LedControl.h"

typedef struct Alarms{
    char DayOfWeekHist[7];
    int Hour;
    int Minute;
} stAlarms;

const char* GetWeekday(int dayNumber);
void checkAlarm(std::pair<stAlarms*, CRGB*> *currentAlarm);