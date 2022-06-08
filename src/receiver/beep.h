#include "EasyBuzzer.h"
unsigned int frequency = 5000;
unsigned int off_duration = 30;
unsigned int on_duration = 10;
unsigned int click_duration = 5;
unsigned int buzzer_pin = 12;

void buzzer_setup(){
    EasyBuzzer.setPin(buzzer_pin);
}

void buzzer_single_click(){
    EasyBuzzer.singleBeep(
		frequency, 	// Frequency in hertz(HZ).  
		click_duration 	// Duration of the beep in milliseconds(ms). 
	);
}

void buzzer_beep_on(){
    EasyBuzzer.singleBeep(
		frequency, 	// Frequency in hertz(HZ).  
		on_duration 	// Duration of the beep in milliseconds(ms). 
	);
}

void buzzer_beep_off(){
    EasyBuzzer.singleBeep(
		frequency, 	// Frequency in hertz(HZ).  
		off_duration 	// Duration of the beep in milliseconds(ms). 
	);

}
void buzzer_loop(){
    EasyBuzzer.update();
}
