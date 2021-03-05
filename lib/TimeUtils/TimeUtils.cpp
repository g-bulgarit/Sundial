
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

/*
void updateTime(int updateIntervalSec){
    unsigned long currentTime = millis();
    if (millis() <= currentTime + updateIntervalSec){
        // Get current time and DoW
        // Compare time to alarm
        // Activate wake sequence if alarm should be triggered
    }

}
*/
// Things we get from Blynk: Day(1-7), Hour(0-24), Minute(0-60)