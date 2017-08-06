#include <Wire.h>
#include <AM2321.h>
#include"Timer.h"

AM2321 ac;
//Timer t;
void setup() {
  Serial.begin(9600);
//  t.every(2000,temper_humid,5);
 // t.every(600000L, temper_humid);
}
void temper_humid()
{
   Serial.print("(");
  Serial.print(ac.read()?"OK,":"Wrong,");
  Serial.print("Time = ");
  Serial.print(millis()/1000);
  Serial.print(" s");
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
// t.update();
// t1.update();
 temper_humid();
 delay(300);
}
