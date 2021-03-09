#pragma once
#include "../../include/ProjectConstants.h"
#include "LedControl.h"
#include <TimeLib.h>


const char* GetWeekday(int dayNumber);
void checkAlarm(s_alarmVars *currentAlarm);
int checkCurrentTime(stAlarms* nextAlarm);
int TimeLibConversion(int dayNumber);
