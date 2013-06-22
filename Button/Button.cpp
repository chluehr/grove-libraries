#include "Button.h"

// Constructor for use with arbitrary data pins:
Button::Button() {
}

// dummy setup method
void Button::setup(int dpin) {
  pinMode(dpin, INPUT);
  datapin     	= dpin;
  state 		= 0;
}

boolean Button::isPressed(void) {

	value = digitalRead(datapin);
	if (value == HIGH) {
		return true;
	}
	
	return false;
}

// returns only true if pin went through a LOW - HIGH - LOW sequence
boolean Button::isClicked(void) {

	value = digitalRead(datapin);
	
	switch (state) {
	
		case 1:
			if (value == HIGH) {
				state = 2; // button pressed
			}
			break;
		case 2:
			if (value == LOW) {
				state = 1; // button released
				return true;
			}
			break;

		default:
			if (value == LOW) {
				state = 1; // initial low state
			}
			break;
	}

	return false;
}
