#include "Rotary.h"

// Constructor for use with arbitrary data pins:
Rotary::Rotary() {
}

// dummy setup method
void Rotary::setup(int apin) {
  pinMode(apin, INPUT);
  datapin     	= apin;
}

float Rotary::getDegree()
{
	int sensor_value = analogRead(datapin);
	float voltage;
	voltage = (float)sensor_value*ADC_REF/1023;
	float degrees = (voltage*FULL_ANGLE)/GROVE_VCC;
	return degrees;
}

int Rotary::getMappedValue(int min, int max) {

	float degrees = getDegree();
	return map(degrees, 0, FULL_ANGLE, min, max); 
}