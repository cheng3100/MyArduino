#include<EEPROM.h>


const int _10MIN_ = 600000L;
int eeAddr = 0;

struct RT_Sensor{
  byte hour;
  byte minute;
  byte second;
  int temperature;
  int humidity;
  }tem_hum;

void getEEPROM(int num)
{
  eeAddr = 2;   //the first two bit used to store which address EEPROM has been writed 
  for(int i=0;i<num;i++)
    getEEPROM();
  }
void getEEPROM()
{
  EEPROM.get(eeAddr, tem_hum);
  eeAddr += sizeof(RT_Sensor);
  
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
void EEPROM_addr_init()   //only using it for the first time(like RTC setting)
{
  EEPROM.put(0, 2); //write EEPROM from the third unit,the first two unit used to store addr
  }



void setup() {
  Serial.begin(9600);
  EEPROM_addr_init();     // only should run just one time ,like the RTC initial
//  getEEPROM(50);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
