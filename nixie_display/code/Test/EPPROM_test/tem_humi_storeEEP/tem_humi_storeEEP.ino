#include <Wire.h>
#include <AM2321.h>
#include <Rtc_Pcf8563.h>
#include"Timer.h"
#include<EEPROM.h>

Rtc_Pcf8563 rtc;
Timer t;
AM2321 ac;
#define _10MIN_  600000L
int eeAddr = 0;
int eeAddr_get = 2;

const int button_get = 31; //when press show the eeprom
const int button_init =33;//initial the address of reading EEPROM
byte buttonState =1;
byte initiState =1;

struct RT_Sensor{
  byte day;
  byte hour;
  byte minute;
  byte second;
  int temperature;
  int humidity;
  }tem_hum;

void setup() {
  Serial.begin(9600);
  pinMode(button_get, INPUT);
  pinMode(button_init, INPUT);
//  storeEEPROM();
  
//  EEPROM_addr_init();     // only should run just one time ,like the RTC initial
//  t.every(2000,storeEEPROM, 10);
  t.every(_10MIN_, storeEEPROM);
//  t.after(10000, getEEPROM_10);
//  getEEPROM(50);
}
void getEEPROM_all()
{
  eeAddr = 0;
  for(int i =0;i<(EEPROM.length()/sizeof(RT_Sensor)); i++)
    getEEPROM();
  }
void getEEPROM(int num)
{
//  eeAddr_get = 2;
  for(int i=0;i<num;i++)
    getEEPROM();
  }
void getEEPROM()
{
  EEPROM.get(eeAddr_get, tem_hum);
  eeAddr_get += sizeof(RT_Sensor);
  Serial.print("Day: ");
  Serial.print(tem_hum.day);
  Serial.print("  ");
  Serial.print("Time: ");
  Serial.print(tem_hum.hour);
  Serial.print(':');
  Serial.print(tem_hum.minute);
  Serial.print(':');
  Serial.print(tem_hum.second);
  Serial.print("  ");
  Serial.print("Temperature: ");
  Serial.print(tem_hum.temperature/10.0);
  Serial.print(" C  ");
  Serial.print("Humidity: ");
  Serial.print(tem_hum.humidity/10.0);
  Serial.println(" %");
  }
void EEPROM_addr_init()
{
  EEPROM.put(0, 2); //write EEPROM from the third unit,the first two unit used to store addr
  }
void storeEEPROM()
{
  EEPROM.get(0, eeAddr);     //little-End mode
  tem_hum.day = rtc.getDay();
  tem_hum.hour = rtc.getHour();
  tem_hum.minute = rtc.getMinute();
  tem_hum.second = rtc.getSecond();
  ac.read();
  tem_hum.temperature = ac.temperature;
  tem_hum.humidity = ac.humidity;

  EEPROM.put(eeAddr, tem_hum);
  eeAddr += sizeof(RT_Sensor);
  if(eeAddr >=EEPROM.length())
    eeAddr = 2;
  EEPROM.put(0, eeAddr);  //put the current address to the first two byte of EEPROM
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

void dete_button()
{
  buttonState = digitalRead(button_get);
  if(buttonState == 0)
    {
      getEEPROM(30);
      buttonState = 1;
      Serial.println();
      }
   initiState = digitalRead(button_init);  
   if(initiState == 0)
      eeAddr_get = 2;
      
   
  }

void loop() {
  t.update();
  dete_button();
}
