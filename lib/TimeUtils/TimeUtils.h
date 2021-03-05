#include <Arduino.h>
#include <TimeLib.h>

typedef struct Alarms{
    char DayOfWeekHist[7];
    int Hour;
    int Minute;
} stAlarms;

const char* GetWeekday(int dayNumber);
void checkAlarm(stAlarms* currentAlarm);