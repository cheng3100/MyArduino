#define SCK_NIX 9
#define SI_NIX  7
#define RCK_NIX 8

#define SCK_LED 6
#define SI_LED  4
#define RCK_LED 5

void init_595()
{
  digitalWrite(SCK_NIX, LOW);
  digitalWrite(SI_NIX, LOW);
  digitalWrite(RCK_NIX, LOW);
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


void setup() {
 pinMode(SCK_LED, OUTPUT);
 pinMode(SI_LED, OUTPUT);
 pinMode(RCK_LED, OUTPUT);
 
 pinMode(SCK_NIX, OUTPUT);
 pinMode(SI_NIX, OUTPUT);
 pinMode(RCK_NIX, OUTPUT);
 led_display(~(1<<1));
}
 int a = 0;
  int i =1;
void loop() {
 
  
  if(i>7)
    i=1;
  if(a>99)
    a=0;
  led_display(~(1<<i++));
  nix_display(a++);
  delay(300);
  
                                                                                                                                                                                                                                                                                               
//led_display(~(1<<6));
//delay(500);

}
