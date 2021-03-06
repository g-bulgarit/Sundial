#pragma once
#include "../../include/ProjectConstants.h"
#include "LedControl.h"
#include <TimeLib.h>


const char* GetWeekday(int dayNumber);
void checkAlarm(s_alarmVars *currentAlarm);
void Ticker(int updateTimeSec, s_alarmVars* currentAlarm);
int checkCurrentTime(stAlarms* nextAlarm);
void dbgPrintEEPROMAlarm(s_alarmVars* currentAlarm);
int TimeLibConversion(int dayNumber);