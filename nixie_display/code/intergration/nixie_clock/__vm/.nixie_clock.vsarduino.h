/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino/Genuino Mega w/ ATmega2560 (Mega 2560), Platform=avr, Package=arduino
*/

#define __AVR_ATmega2560__
#define _VMDEBUG 1
#define ARDUINO 10801
#define ARDUINO_MAIN
#define F_CPU 16000000L
#define __AVR__
#define F_CPU 16000000L
#define ARDUINO 10801
#define ARDUINO_AVR_MEGA2560
#define ARDUINO_ARCH_AVR
 #include <VM_DBG.h>

void nix_led_init();
void led_display(byte ledcode);
void nix_display(int num);
void nix_off(int num);
void led_state();
void tem_display();
void hum_display();
void tim_display();
void wek_display();
void mon_display();
void dat_display();
void welcome();
//
//

#include "pins_arduino.h" 
#include "arduino.h"
#include "nixie_clock.ino"
