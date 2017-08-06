#include<EEPROM.h>
int eeAddr = 0;

void setup() {
  int a =10;
  Serial.begin(9600);
 for(int i=0;i<10;i++)
 {
    EEPROM.put(eeAddr, a++);
    eeAddr += sizeof(int);
  }
  eeAddr =0;
  for(int i=0;i<10;i++)
  {
      EEPROM.get(eeAddr, a);
      eeAddr += sizeof(int);
      Serial.println(a);
      
    }

}

void loop() {
  // put your main code here, to run repeatedly:

}
