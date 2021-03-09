#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#include <EEPROM.h>

#include "ProjectConstants.h"

#include "SecretKeys.h"
#include "TimeUtils.h"
#include "LedControl.h"


WidgetRTC rtc;
BlynkTimer wifi_wd;

void PeriodicWiFiCheck(){
  #ifdef DEBUG
  Serial.println("[!] Checking connections...");
  #endif

  // First, check Blynk connection
  if (!Blynk.connected()){
    yield();
    // Check WiFi status
    if (WiFi.status() != WL_CONNECTED){
      #ifdef DEBUG
      Serial.println("[!] Reconnecting to WiFi");
      #endif

      WiFi.begin(sWifiAP, sWifiPwd);
    }

    // Check if the issue is the blynk servers
    if (WiFi.status() == WL_CONNECTED && !Blynk.connected()){
      #ifdef DEBUG
      Serial.println("[!] Reconnecting to Blynk");
      #endif

      Blynk.connect();
    }
  }
  #ifdef DEBUG
  Serial.println("[!] Connections OK");
  #endif
}

// Define an LED array
static CRGB leds[NUM_LEDS];

void setup() { 
  // Initiallize pins
  pinMode(5, OUTPUT);

  // Initiallize serial for debug
  Serial.begin(9600);

  // Set LED Type
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness(50);

  // TODO: Load alarm from eeprom
  EEPROM.begin(256); // Emulate 256 bytes of EEPROM in RAM
  stAlarms currentAlarm;
  EEPROM.get(0, currentAlarm);

  // Allocate memory for the alarm to pass it around
  stAlarms* currentAlarmPtr = (stAlarms*)malloc(sizeof(stAlarms));
  currentAlarmPtr->Hour = currentAlarm.Hour;
  currentAlarmPtr->Minute = currentAlarm.Minute;
  memcpy(currentAlarmPtr->DayOfWeekHist, currentAlarm.DayOfWeekHist, sizeof(currentAlarm.DayOfWeekHist));

  
  // Create a struct to hold most of the required parameters for every other function
  s_alarmVars* alarmVariables = (s_alarmVars*)malloc(sizeof(s_alarmVars));
  alarmVariables->ledArray = leds;
  alarmVariables->nextAlarm = currentAlarmPtr;

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
  while (!Blynk.connected()){
    Serial.println("[!] Connecting to WiFi");
    Blynk.begin(sBlynkAuthToken, sWifiAP, sWifiPwd);
    Serial.println("[V] Connected to WiFi");
  }
  

  // Initiallize RTC
  rtc.begin();
  setSyncInterval(5 * 60); // Sync interval in seconds (5 minutes)

  // WiFi Check - diagnose and solve connection problems every 30 seconds
  wifi_wd.setInterval(30000L, PeriodicWiFiCheck);

  // Main loop...
  // Bad practice to have a loop in the setup routine, but it only makes sense in this context
  while(1){
    int flag=0;
    unsigned long timeNow = millis();
    while (millis() <= timeNow + UPDATE_RATE_SEC*1000){
        // Calling Blynk.run from within to keep connection alive,
        // And yield to allow the OS to deal with other things while it waits
        Blynk.run();
        wifi_wd.run();

        yield();
    }
    // Time had passed, check the current time!
    flag = checkCurrentTime(alarmVariables->nextAlarm);
    if (flag){
        AmberToSunlight(alarmVariables->ledArray, 120, 180, 180);
    }
    Blynk.run();
    wifi_wd.run();

}
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
  uint8_t DoW[7] = {0};
  for (int i = 1; i <= 7; i++) {
      if (t.isWeekdaySelected(i)) {
        DoW[i-1] = 1;
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
  for (int d=0; d<6; d++){
    if (Alarm.DayOfWeekHist[d] == 1){
      Serial.println(GetWeekday(d));
    }
  }
  #endif

  Serial.println("[!] Restarting!");
  ESP.restart();
}

BLYNK_WRITE(V2){
  // This used to be a debug button but it's repurposed now
  // This button shuts off the LEDs for manual mode.
    SetStripColorRGB(leds, 0, 0, 0);
    
}

BLYNK_WRITE(V3){
  int r,g,b;
  r = param[0].asInt();
  g = param[1].asInt();
  b = param[2].asInt();
  SetStripColorRGB(leds, r, g, b);
}

BLYNK_WRITE(V4){
  int inputBrightness = param.asInt();
  Serial.print("[!] New brightness value:");
  Serial.println(inputBrightness);
  FastLED.setBrightness(inputBrightness);
  FastLED.show();
}


void loop() {
  Blynk.run();
}