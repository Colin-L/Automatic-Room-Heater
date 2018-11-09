#include <IRremote.h>
#include <Time.h>
#include <TimeAlarms.h>
#include <Wire.h>
#include "RTClib.h"

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif


int heaterPin =A0;
int switchPin = 2;
int buttonPin = 3;
int irSensorPin = 4;
int buttonLightPin = 5;
int pressedTime;

IRrecv irrecv(irSensorPin);
decode_results results;
DateTime now;
RTC_DS1307 rtc;
AlarmId morningAlarmID,timerAlarmID;


//Functions---------------------------------------------------------------------------------------------
void switchRising(){
//If switch is on timer outlet (heater) will turn on at designated time for 20 mins
  switchOn = true
  morningAlarmID = Alarm.alarmRepeat(7,0,0, morningAlarm); //Outlet(heater) will turn on every moring at 7:00am 
}

void switchFalling(){
  switchOn = false
  //Turn off morningAlarm here
  //May need to catch exception if the program is started with the switch on as morningAlarmID wont be initilized
  Alarm.free(morningAlarmID);
}
void buttonPressedRising(){
pressedTime = getTime();
heaterTime += 20*60;
}

void buttonPressedFalling(){
 if ((releasedTime-pressedTime) > 3){ //if 3 second button press turn toggle led switch light
  digitalWrite(buttonLightPin, !digitalRead(buttonLightPin));
 }
}

void setSystemClock(){
  now = rtc.now();
  setTime(now.hour(),now.minute(),now.second(),now.day(),now.month(),now.year());
}

void morningAlarm(){
  //Set outlet pin to high for 20 mins
}
void checkHeaterTime(int heaterTime){
  
}

//------------------------------------------------------------------------------------------------------


void setup() {
  Serial.begin(115200);
  pinMode(buttonLightPin,OUTPUT);
  pinMode(heaterPin,OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);

  #ifndef ESP8266
    while (!Serial); // for Leonardo/Micro/Zero
  #endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
  
  //Create Alarm
  setSystemClock();
  Alarm.timerRepeat(60, setSystemClock); //Syncs the system clock with the RTC every minute


  
  //Attach interrupts to switch and button----------------------------------------------------
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressedRising, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressedFalling, FALLING);

  pinMode(switchPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(switchPin), switchRising, RISING);
  attachInterrupt(digitalPinToInterrupt(switchPin), switchFalling, FALLING);
  //------------------------------------------------------------------------------------------

  //Get switch state. if switch is on call switchRising()
  //This will turn on the morning alarm
  if (digitalRead(switchPin) == HIGH){
    switchRising();
  }

  }
void loop() {
  //IR--------------------------------------------------
  //If an IR signal is recieved the outlet(heater) will turn on for 20 mins
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        irrecv.resume();
        heaterTime = 20;
        Serial.println("IR Signal Recieved. heaterTime = " + heaterTime);
  }
  //----------------------------------------------------

  checkHeaterTime(heaterTime);
  
}//Loop End
