#include <Arduino.h>
const char* GetWeekday(int dayNumber);
// void updateTime();

typedef struct Alarms{
    char DayOfWeekHist[7];
    int Hour;
    int Minute;
} stAlarms;