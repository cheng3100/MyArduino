#include <Wire.h>
#include <AM2321.h>
#include <Rtc_Pcf8563.h>
#include"Timer.h"

Rtc_Pcf8563 rtc;
Timer t;
AM2321 ac;
void setup() {
  Serial.begin(9600);
  t.every(2000,temper_humid,5);
  t.every(600000L, temper_humid);
  //
  //if the rtc have beed power with battery ,just initial it once
  //
  //clear out the registers
//  rtc.initClock();
//  //set a time to start with.
//  //day, weekday, month, century(1=1900, 0=2000), year(0-99)
//  rtc.setDate(12, 4, 1, 0, 17);
//  //hr, min, sec
//  rtc.setTime(18, 41, 0);
}
void temper_humid()
{
   Serial.print("(");
  Serial.print(ac.read()?"OK,":"Wrong,");
  Serial.print("Time = ");
  Serial.print(rtc.formatTime());
  Serial.print(",");
  Serial.print("Tempetrue = ");
  Serial.print(ac.temperature/10.0);
  Serial.print(" C");
  Serial.print(",");
  Serial.print("Humidity = ");
  Serial.print(ac.humidity/10.0);
   Serial.print(" %");
  Serial.println(")");
  }
void loop() {
  t.update();

}
