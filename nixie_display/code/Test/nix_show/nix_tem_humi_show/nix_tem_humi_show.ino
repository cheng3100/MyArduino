#include <Wire.h>
#include <AM2321.h>
#include <Rtc_Pcf8563.h>
#include"Timer.h"

#define SCK_NIX 9
#define SI_NIX  7
#define RCK_NIX 8

#define SCK_LED 6
#define SI_LED  4
#define RCK_LED 5
Rtc_Pcf8563 rtc;
Timer t;
AM2321 ac;

void nix_init()
{
  pinMode(SCK_LED, OUTPUT);
  pinMode(SI_LED, OUTPUT);
  pinMode(RCK_LED, OUTPUT);

  pinMode(SCK_NIX, OUTPUT);
  pinMode(SI_NIX, OUTPUT);
  pinMode(RCK_NIX, OUTPUT);

}
void led_display(byte ledcode)
{
  shiftOut(SI_LED, SCK_LED, MSBFIRST, ledcode);
  //send the data from shift register to output latch
  delayMicroseconds(5);         
  digitalWrite(RCK_LED, HIGH);
  delayMicroseconds(5);
  digitalWrite(RCK_LED, LOW);
  }
void nix_display(int num)
{
  byte nix_dig = (num%10) | (num/10%10<<4);   //turn the hex to bcd
  shiftOut(SI_NIX, SCK_NIX, MSBFIRST, nix_dig);
  delayMicroseconds(5);     
  digitalWrite(RCK_NIX, HIGH);
  delayMicroseconds(5);
  digitalWrite(RCK_NIX, LOW);
  }

void tem_humi_show()
{
  ac.read();
  nix_display(ac.temperature/10);
  delay(1500);
  nix_display(ac.humidity/10);
  delay(1500);
  }
void clock_show()
{
  nix_display(rtc.getHour());
  delay(1500);
  nix_display(rtc.getMinute());
  delay(1500);
  nix_display(rtc.getSecond());
  delay(1500);
  }
void setup() {
  nix_init();
    
}

void loop() {
  
    clock_show();
  

}
