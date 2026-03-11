#include "led.h"
#include "keyboard.h"

#define MilS 5000

void Delay(unsigned int uiTimeMs) {
	unsigned int uiCounter;
	
	for(uiCounter = 0; uiCounter < (MilS*uiTimeMs); uiCounter++) {
		
	}
}

enum LedState{STOP, LED_LEFT, LED_RIGHT, BLINKING};

int main(){
	
	enum LedState eLedState = STOP;
	unsigned char ucBlinker;
	LedInit();
	KeyboardInit();
	
	
	while(1) {
	
		switch(eLedState) {
		
			case STOP:
				if( eKeyboardRead() == BUTTON_0) {
					
					eLedState = LED_LEFT;
				} else if(eKeyboardRead() == BUTTON_2){
					
					eLedState = LED_RIGHT;
				} else {
					
					eLedState = STOP;
				}
			break;
				
			case LED_LEFT:
				
				if( eKeyboardRead() == BUTTON_1) {
					 eLedState = STOP;
				} else {
					LedStepLeft();
					eLedState = LED_LEFT;
				}
			break;
		
			case LED_RIGHT:
				
				if( eKeyboardRead() == BUTTON_1) {
					 eLedState = STOP;
					} else if(eKeyboardRead() == BUTTON_3){
					eLedState = BLINKING;
					} else {
					LedStepRight();
					eLedState = LED_RIGHT;
				}
			break;
			
			case BLINKING:
				
				if (ucBlinker >= 6) { 
						ucBlinker = 0;
						eLedState = LED_LEFT;
				} else {
						if ((ucBlinker % 2) == 0) {
							LedOn(2);
						} else {
							LedOn(3);
						}
						ucBlinker++;
						eLedState = BLINKING;
			}
    break;
				
			}
		
		Delay(100);
	}
}
