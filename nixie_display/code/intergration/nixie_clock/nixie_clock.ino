#include <Wire.h>
#include <AM2321.h>
#include <Rtc_Pcf8563.h>
#include"Timer.h"
#include<avr/wdt.h>     //the nix clock  frequently hangs without finding out why,so add a watch dog to fix it

#define SCK_NIX 9
#define SI_NIX  7
#define RCK_NIX 8

#define SCK_LED 6
#define SI_LED  4
#define RCK_LED 5

#define LED_TEM 7
#define LED_HUM 6
#define LED_TIM 5
#define LED_YEA 4
#define LED_MON 3
#define LED_DAT 2
#define LED_NEG 1

#define AD_SHAKE 10

#define _1MIN_ 60000L
#define _10MIN_ 600000L

Rtc_Pcf8563 rtc;
Timer t;
AM2321 ac;

int led_ad = A0;
int led_Value;

enum funcState {Tem, Hum, Tim, Wek, Mon, Dat } state;
void nix_led_init()
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
  byte nix_dig = (abs(num) % 10) | (abs(num) / 10 % 10 << 4); //turn the hex to bcd
  shiftOut(SI_NIX, SCK_NIX, MSBFIRST, nix_dig);
  delayMicroseconds(5);
  digitalWrite(RCK_NIX, HIGH);
  delayMicroseconds(5);
  digitalWrite(RCK_NIX, LOW);
}

void nix_off(int num)
{
  shiftOut(SI_NIX, SCK_NIX, MSBFIRST, 0xff);
  delayMicroseconds(5);
  digitalWrite(RCK_NIX, HIGH);
  delayMicroseconds(5);
  digitalWrite(RCK_NIX, LOW);
  delay(num);
}
void led_state()
{
  led_Value = analogRead(led_ad);
  if (led_Value > (1000 + AD_SHAKE) && led_Value < 1023)
  { led_display(~(1 << LED_TEM));
    state = Tem;
  }
  else if (led_Value > (900 + AD_SHAKE) && led_Value < (1000 - AD_SHAKE))
  { led_display(~(1 << LED_HUM));
    state = Hum;
  }
  else if (led_Value > (740 + AD_SHAKE) && led_Value < (900 - AD_SHAKE))
  { led_display(~(1 << LED_TIM));
    state = Tim;
  }
  else if (led_Value > (515 + AD_SHAKE) && led_Value < (740 - AD_SHAKE))
  { led_display(~(1 << LED_YEA));
    state = Wek;
  }
  else if (led_Value > (279 + AD_SHAKE) && led_Value < (515 - AD_SHAKE))
  { led_display(~(1 << LED_MON));
    state = Mon;
  }
  else if (led_Value > 0 && led_Value < (279 - AD_SHAKE))
  { led_display(~(1 << LED_DAT));
    state = Dat;
  }
}

void tem_display()
{
  ac.read();
  int tem = ac.temperature / 10;
  nix_display(tem);
  if (tem < 0)
    led_display(~(1 << LED_TEM | 1 << LED_NEG)); //negative temperature indicate （will case the negative led blink because of the "ledstate()" just light the tem_led）
}

void hum_display()
{
  ac.read();
  nix_display(ac.humidity / 10);
}

void tim_display()
{

  static int num_h = 0;   //use to dislay several second time by record the how many time the function has been load
  static int num_m = 0;
  static int num_s = 0;
  if (num_h < 10 && num_m == 0 && num_s == 0)
  { nix_display(rtc.getHour());
    delay(200);
    num_h++;
  }
  else if (num_h == 10 && num_m < 10 && num_s == 0)
  {
    if (num_m == 0 )
      nix_off(200);;
    nix_display(rtc.getMinute());
    delay(200);
    num_m++;
  }
  else if (num_h == 10 && num_m == 10 && num_s < 40)
  {
    if (num_s == 0)
      nix_off(200);;
    nix_display(rtc.getSecond());
    delay(200);
    num_s++;
  }
  else if (num_s == 40)
  {
    nix_off(200);
    num_h = 0, num_m = 0, num_s = 0;

  }

}
void wek_display()
{
  nix_display(rtc.getWeekday());
}
void mon_display()
{
  nix_display(rtc.getMonth());
}
void dat_display()
{
  nix_display(rtc.getDay());
}

void welcome()
{
  int n = 1;
  for (int i = 0 ; i < 10; i++)
  {
    wdt_reset();
    nix_display(11 * i);
    led_display(~(1 << n++));
    if (n >= 8)
      n = 1;
    delay(400);
  }
  delay(400);
  for (int i = 9 ; i >= 0; i--)
  {
    wdt_reset();
    nix_display(11 * i);
    led_display(~(1 << n++));
    if (n >= 8)
      n = 1;
    delay(400);
  }

}
void setup() {
  wdt_disable();      //  must disable the WDT at first or it may always reboot and could enter in the loop
  //
  Serial.begin(9600);
  nix_led_init();
  welcome();        //the welcome function using more than 4 second.so must reset the WDT inside it !!!
  t.every(_10MIN_, welcome);  //aviod the cathode poisoning

  //the WDT time can be choose from
  //WDTO_25MS  WDTO_30MS  WDTO_60MS  WDTO_250MS  WDTO_500MS
  //WDTO_1S  WDTO_3S  WDTO_4S  WDTO_8S
  //be very carfully when use too short time value because  most avr's WDT still on work even after reboot
  wdt_enable(WDTO_4S);      //had better enable it after initial case some initial function is time-consuming
}
void loop() {
  t.update();
  wdt_reset();    //reset the WDT every loop,or it will cause reboot
  led_state();
  switch (state)
  {
    case Tem: tem_display(); break;
    case Hum: hum_display(); break;
    case Tim: tim_display(); break;
    case Wek: wek_display(); break;
    case Mon: mon_display(); break;
    case Dat: dat_display(); break;
    default: tem_display(); break;
  }
}
