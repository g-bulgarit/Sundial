#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#include <EEPROM.h>
#include <Ticker.h>


#include "ProjectConstants.h"
#include "SecretKeys.h"
#include "LedControl.h"
#include "TimeUtils.h"

// Define an LED array
CRGB leds[NUM_LEDS];
WidgetRTC rtc;
Ticker update;

void setup() { 
  // Initiallize pins
  pinMode(5, OUTPUT);

  // Initiallize serial for debug
  Serial.begin(9600);

  // Set LED Type
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical

  // TODO: Load alarm from eeprom
  EEPROM.begin(256); // Emulate 256 bytes of EEPROM in RAM
  stAlarms currentAlarm;
  EEPROM.get(0, currentAlarm);

  // Allocate memory for the alarm to pass it around
  stAlarms* currentAlarmPtr = (stAlarms*)malloc(sizeof(stAlarms));
  currentAlarmPtr->Hour = currentAlarm.Hour;
  currentAlarmPtr->Minute = currentAlarm.Minute;
  memcpy(currentAlarmPtr->DayOfWeekHist, currentAlarm.DayOfWeekHist, sizeof(currentAlarm.DayOfWeekHist));

  #ifdef DEBUG
  Serial.println("[!] Current Set Alarm:");
  Serial.print("[    >] Alarm Hour: ");
  Serial.println(currentAlarm.Hour);
  Serial.print("[    >] Alarm Minute: ");
  Serial.println(currentAlarm.Minute);
  Serial.println("[    >] Alarm days: ");
  for (int d=0; d<7; d++){
    if (currentAlarm.DayOfWeekHist[d] == 1){
      Serial.println(GetWeekday(d));
    }
  }

  #endif

  // Initiallize Blynk connection  
  Blynk.begin(sBlynkAuthToken, sWifiAP, sWifiPwd);

  // Initiallize RTC
  rtc.begin();
  setSyncInterval(5 * 60); // Sync interval in seconds (5 minutes)

  update.attach(30, checkAlarm, currentAlarmPtr);

}

// Blynk Functions

// Time input:
BLYNK_WRITE(V1) {
  // Get time from time-input widget, save to eeprom!
  // Data structure:
  // 7 bytes | 1 byte hour | 1 byte minute
  
  TimeInputParam t(param);
  // Process timezone
  t.getTZ();
  t.getTZ_Offset();

  // stAlarms* Alarm = (stAlarms*)malloc(sizeof(stAlarms));
  stAlarms Alarm;
  char DoW[7] = {0};
  for (int i = 1; i <= 7; i++) {
      if (t.isWeekdaySelected(i)) {
        DoW[i] = 1;
      }
  }
  
  // Populate Alarm Struct
  memcpy(Alarm.DayOfWeekHist, DoW, sizeof(DoW));
  Alarm.Hour = t.getStartHour();
  Alarm.Minute = t.getStartMinute();

  // Save Struct to EEPROM
  EEPROM.put(0, Alarm);
  EEPROM.commit();

  Serial.println("[!] Stored the alarm in EEPROM!");

  #ifdef DEBUG
  Serial.println("[!] Data:");
  Serial.print("[    >] Alarm Hour: ");
  Serial.println(Alarm.Hour);
  Serial.print("[    >] Alarm Minute: ");
  Serial.println(Alarm.Minute);
  Serial.println("[    >] Alarm days: ");
  for (int d=0; d<7; d++){
    if (Alarm.DayOfWeekHist[d] == 1){
      Serial.println(GetWeekday(d));
    }
  }
  #endif

}

BLYNK_WRITE(V2){
    String currentTime = String(hour()) + ":" + minute() + ":" + second();
    Serial.print("Time now is:");
    Serial.println(currentTime);
    String currentWeekday = GetWeekday(weekday());
    Serial.print("Time day is:");
    Serial.println(currentWeekday);
    AmberToSunlight(leds, 30 ,30, 20);
    
}

BLYNK_WRITE(V3){
  int r,g,b;
  r = param[0].asInt();
  g = param[1].asInt();
  b = param[2].asInt();
  SetStripColorRGB(leds, r, g, b);
}


void loop() { 
  Blynk.run();
}