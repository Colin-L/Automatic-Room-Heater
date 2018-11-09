#include <SimpleDHT.h>
#include <stdio.h>

#define MAX_OUT_CHARS 16  //max nbr of characters to be sent on any one serial command
char   buffer[MAX_OUT_CHARS + 1];  //buffer used to format a line (+1 is for trailing 0)

int MAX_TEMP = 26;
int MIN_TEMP = 22;

int temperature = 999, humidity = 0, err = SimpleDHTErrSuccess;
SimpleDHT11 dht11;

int HEATER_PIN = 3;
int TEMP_SENSOR_PIN = A0;

int readCount = 0;
int errCount = 0;
int concecutiveFails  = 0;
int digits;
int onTime = 0;
int offTime = 0;
float onOffTimeRatio;
  int displayValue = 99;

int A1_SEGMENT = 8;
int B1_SEGMENT = 7;
int C1_SEGMENT = A2;
int D1_SEGMENT = A1;
int E1_SEGMENT = 13;
int F1_SEGMENT = 10;
int G1_SEGMENT = 9;
int DECIMAL1_SEGMENT = A3;

int A2_SEGMENT = 11;
int B2_SEGMENT = 2;
int C2_SEGMENT = A6;
int D2_SEGMENT = A5;
int E2_SEGMENT = A4;
int F2_SEGMENT = 6;
int G2_SEGMENT = 5;
int DECIMAL2_SEGMENT = A7;


void displayNumber(int num){
  //Given a 2 or 1 digit number it will display it on the two seven segment displays
  //digit[0] Tens digit, digit[1] Ones digit
  int digit[2];

  if (num > 9){
    digit[0] = num / 10;
    digit[1] = num % 10;
    digits = 2;
  }else{
    digits = 1;
    digit[0] = num;
  }
  for (int i = 0; i<digits; i++){
    switch(digit[i]){ //Switch on digit[i]: 
      case 1:
        displayOne(i);
        break;
      case 2:
        displayTwo(i);
        break;
      case 3:
        displayThree(i);
        break;
      case 4:
        displayFour(i);
        break;
      case 5:
        displayFive(i);
        break;
      case 6:
        displaySix(i);
        break;
      case 7:
        displaySeven(i);
        break;
      case 8:
        displayEight(i);
        break;
      case 9:
        displayNine(i);
        break;
      case 0:
        displayZero(i);
        break;
      default:
        Serial.println("Default Switch Case Reached");
        
  }
}
}

void clearDisplay(int digitPosition){
  if (digitPosition == 0){
  digitalWrite(A1_SEGMENT,LOW);
  digitalWrite(B1_SEGMENT,LOW);
  digitalWrite(C1_SEGMENT,LOW);
  digitalWrite(D1_SEGMENT,LOW);
  digitalWrite(E1_SEGMENT,LOW);
  digitalWrite(F1_SEGMENT,LOW);
  digitalWrite(G1_SEGMENT,LOW);
  digitalWrite(DECIMAL1_SEGMENT,LOW);
  }else{
  digitalWrite(A2_SEGMENT,LOW);
  digitalWrite(B2_SEGMENT,LOW);
  digitalWrite(C2_SEGMENT,LOW);
  digitalWrite(D2_SEGMENT,LOW);
  digitalWrite(E2_SEGMENT,LOW);
  digitalWrite(F2_SEGMENT,LOW);
  digitalWrite(G2_SEGMENT,LOW);
  digitalWrite(DECIMAL2_SEGMENT,LOW);
  }
}


//Digit position 0 first 7-segment 1 second 7-segment
void displayOne(int digitPosition){
  clearDisplay(digitPosition);
  if (digitPosition == 0){
  digitalWrite(B1_SEGMENT,HIGH);
  digitalWrite(C1_SEGMENT,HIGH);
  }
  else{
  digitalWrite(B2_SEGMENT,HIGH);
  digitalWrite(C2_SEGMENT,HIGH);
  }
}
void displayTwo(int digitPosition){
  clearDisplay(digitPosition);
  if (digitPosition == 0){
  digitalWrite(A1_SEGMENT,HIGH);
  digitalWrite(B1_SEGMENT,HIGH);
  digitalWrite(G1_SEGMENT,HIGH);
  digitalWrite(E1_SEGMENT,HIGH);
  digitalWrite(D1_SEGMENT,HIGH);
  }
  else{
  digitalWrite(A2_SEGMENT,HIGH);
  digitalWrite(B2_SEGMENT,HIGH);
  digitalWrite(G2_SEGMENT,HIGH);
  digitalWrite(E2_SEGMENT,HIGH);
  digitalWrite(D2_SEGMENT,HIGH);
  }
}
void displayThree(int digitPosition){
  clearDisplay(digitPosition);
  if (digitPosition == 0){
  digitalWrite(A1_SEGMENT,HIGH);
  digitalWrite(B1_SEGMENT,HIGH);
  digitalWrite(G1_SEGMENT,HIGH);
  digitalWrite(C1_SEGMENT,HIGH);
  digitalWrite(D1_SEGMENT,HIGH);
  }
  else{
  digitalWrite(A2_SEGMENT,HIGH);
  digitalWrite(B2_SEGMENT,HIGH);
  digitalWrite(G2_SEGMENT,HIGH);
  digitalWrite(C2_SEGMENT,HIGH);
  digitalWrite(D2_SEGMENT,HIGH);
  }
}
void displayFour(int digitPosition){
  clearDisplay(digitPosition);
  if (digitPosition == 0){
  digitalWrite(F1_SEGMENT,HIGH);
  digitalWrite(B1_SEGMENT,HIGH);
  digitalWrite(G1_SEGMENT,HIGH);
  digitalWrite(C1_SEGMENT,HIGH);
  }
  else{
  digitalWrite(F2_SEGMENT,HIGH);
  digitalWrite(B2_SEGMENT,HIGH);
  digitalWrite(G2_SEGMENT,HIGH);
  digitalWrite(C2_SEGMENT,HIGH);
  }
}
void displayFive(int digitPosition){
  clearDisplay(digitPosition);
  if (digitPosition == 0){
  digitalWrite(A1_SEGMENT,HIGH);
  digitalWrite(F1_SEGMENT,HIGH);
  digitalWrite(G1_SEGMENT,HIGH);
  digitalWrite(C1_SEGMENT,HIGH);
  digitalWrite(D1_SEGMENT,HIGH);
  }
  else{
  digitalWrite(A2_SEGMENT,HIGH);
  digitalWrite(F2_SEGMENT,HIGH);
  digitalWrite(G2_SEGMENT,HIGH);
  digitalWrite(C2_SEGMENT,HIGH);
  digitalWrite(D2_SEGMENT,HIGH);
  }
}
void displaySix(int digitPosition){
  clearDisplay(digitPosition);
  if (digitPosition == 0){
  digitalWrite(A1_SEGMENT,HIGH);
  digitalWrite(F1_SEGMENT,HIGH);
  digitalWrite(G1_SEGMENT,HIGH);
  digitalWrite(C1_SEGMENT,HIGH);
  digitalWrite(D1_SEGMENT,HIGH);
  digitalWrite(E1_SEGMENT,HIGH);
  }
  else{
  digitalWrite(A2_SEGMENT,HIGH);
  digitalWrite(F2_SEGMENT,HIGH);
  digitalWrite(G2_SEGMENT,HIGH);
  digitalWrite(C2_SEGMENT,HIGH);
  digitalWrite(D2_SEGMENT,HIGH);
  digitalWrite(E2_SEGMENT,HIGH);
  }
}
void displaySeven(int digitPosition){
  clearDisplay(digitPosition);
  if (digitPosition == 0){
  digitalWrite(A1_SEGMENT,HIGH);
  digitalWrite(B1_SEGMENT,HIGH);
  digitalWrite(C1_SEGMENT,HIGH);
  }
  else{
  digitalWrite(A2_SEGMENT,HIGH);
  digitalWrite(B2_SEGMENT,HIGH);
  digitalWrite(C2_SEGMENT,HIGH);
  }
}
void displayEight(int digitPosition){
  clearDisplay(digitPosition);
  if (digitPosition == 0){
  digitalWrite(A1_SEGMENT,HIGH);
  digitalWrite(B1_SEGMENT,HIGH);
  digitalWrite(F1_SEGMENT,HIGH);
  digitalWrite(G1_SEGMENT,HIGH);
  digitalWrite(C1_SEGMENT,HIGH);
  digitalWrite(D1_SEGMENT,HIGH);
  digitalWrite(E1_SEGMENT,HIGH);
  }
  else{
  digitalWrite(A2_SEGMENT,HIGH);
  digitalWrite(B2_SEGMENT,HIGH);
  digitalWrite(F2_SEGMENT,HIGH);
  digitalWrite(G2_SEGMENT,HIGH);
  digitalWrite(C2_SEGMENT,HIGH);
  digitalWrite(D2_SEGMENT,HIGH);
  digitalWrite(E2_SEGMENT,HIGH);
  }
}
void displayNine(int digitPosition){
  clearDisplay(digitPosition);
  if (digitPosition == 0){
  digitalWrite(A1_SEGMENT,HIGH);
  digitalWrite(B1_SEGMENT,HIGH);
  digitalWrite(F1_SEGMENT,HIGH);
  digitalWrite(G1_SEGMENT,HIGH);
  digitalWrite(C1_SEGMENT,HIGH);
  digitalWrite(D1_SEGMENT,HIGH);
  }
  else{
  digitalWrite(A2_SEGMENT,HIGH);
  digitalWrite(B2_SEGMENT,HIGH);
  digitalWrite(F2_SEGMENT,HIGH);
  digitalWrite(G2_SEGMENT,HIGH);
  digitalWrite(C2_SEGMENT,HIGH);
  digitalWrite(D2_SEGMENT,HIGH);
}
}
void displayZero(int digitPosition){
  clearDisplay(digitPosition);
  if (digitPosition == 0){
  digitalWrite(A1_SEGMENT,HIGH);
  digitalWrite(B1_SEGMENT,HIGH);
  digitalWrite(F1_SEGMENT,HIGH);
  digitalWrite(C1_SEGMENT,HIGH);
  digitalWrite(D1_SEGMENT,HIGH);
  digitalWrite(E1_SEGMENT,HIGH);
  }
  else{
  digitalWrite(A2_SEGMENT,HIGH);
  digitalWrite(B2_SEGMENT,HIGH);
  digitalWrite(F2_SEGMENT,HIGH);
  digitalWrite(C2_SEGMENT,HIGH);
  digitalWrite(D2_SEGMENT,HIGH);
  digitalWrite(E2_SEGMENT,HIGH);
}
}
int readTemperature() {
  byte t = 999;
  byte h = 999;
  err = SimpleDHTErrSuccess;
  readCount ++;
  if ((err = dht11.read(TEMP_SENSOR_PIN, &t, &h, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);
    concecutiveFails ++;
    errCount ++;
    //If the reading fails 30 times in a row it will set the temp to 99. This will turn off the heater.
    //This is to prevent the heater from staying on forever in the event that the sensor keeps failing 
    //while the heater is on
    if (concecutiveFails >=100){ 
      Serial.println("Concecutive Fails: "); Serial.println(concecutiveFails);
      return 99;
    }
    return 999;
  }
  Serial.println("======================================================================");
  Serial.print("Temperature: "); Serial.print(t); Serial.println(" *C ");
  Serial.print("Humidity:    "); Serial.print(h); Serial.println("% ");
  Serial.println("======================================================================");
  concecutiveFails = 0;
  return (int)t;
} //Read temperature end


void setup() {
  Serial.begin(115200);
  pinMode(HEATER_PIN,OUTPUT);
  
  //Segment 1
  pinMode(A1_SEGMENT,OUTPUT);
  pinMode(B1_SEGMENT,OUTPUT);
  pinMode(C1_SEGMENT,OUTPUT);
  pinMode(D1_SEGMENT,OUTPUT);
  pinMode(E1_SEGMENT,OUTPUT);
  pinMode(F1_SEGMENT,OUTPUT);  
  pinMode(G1_SEGMENT,OUTPUT);
  pinMode(DECIMAL1_SEGMENT,OUTPUT);

  //Segment 2
  pinMode(A2_SEGMENT,OUTPUT);
  pinMode(B2_SEGMENT,OUTPUT);
  pinMode(C2_SEGMENT,OUTPUT);
  pinMode(D2_SEGMENT,OUTPUT);
  pinMode(E2_SEGMENT,OUTPUT);
  pinMode(F2_SEGMENT,OUTPUT);
  pinMode(G2_SEGMENT,OUTPUT);
  pinMode(DECIMAL2_SEGMENT,OUTPUT);
  
  //Tests that everything is working on startup
  //Will turn on  heater for 5 seconds and countdown then turn off
  //and start normal function
  digitalWrite(HEATER_PIN,HIGH);
  Serial.println("Setup:");
  for (int i=9; i>-1; i--){  
    
    displayNumber(i*11);
    delay(500);
  }
  digitalWrite(HEATER_PIN,LOW);
  displayNumber(99);
} //Setup end

void loop() {
  temperature = readTemperature();

  Serial.print("Total reads: "); Serial.print(readCount);
  Serial.print(", err: "); Serial.print(errCount);
  Serial.print(", success rate: "); Serial.print((readCount - errCount) * 100.0 / (float)readCount); Serial.println("%");

  //Serial.println(temperature);
  if (temperature != 999){ //If the temperature reading succceded display the value, otherwise display the last successful reading
    displayValue = temperature;
  }
  displayNumber(displayValue);
  delay(1500); 
  clearDisplay(0);
  clearDisplay(1);
  delay(6000);
  
  if (temperature >= MAX_TEMP) {
    digitalWrite(HEATER_PIN,LOW);
    offTime = offTime + 1;
  }
  
  if (temperature <= MIN_TEMP) {
    digitalWrite(HEATER_PIN,HIGH);
    onTime = onTime + 1;
  }
  //onOffTimeRatio = onTime / offTime;
  //Print onTime/Offtime in seconds
  //sprintf(buffer,"OnTime: %d OffTime: %d Ratio: %.2f",onTime,offTime,onOffTimeRatio); 
  //Serial.println(buffer);
    
}
