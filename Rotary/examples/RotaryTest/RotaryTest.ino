#include <Rotary.h>

Rotary myRotary;

void setup()
{
  Serial.begin(9600);	// Serial is used for debugging
  myRotary.setup(A0);	// select (analog) pin to use
}

void loop()
{

  delay(500);  // delay for serial readability
  
    Serial.print("DEGREE (float): ");
	Serial.println(myRotary.getDegree());
  
    Serial.print("MAPPED (int): ");
	Serial.println(myRotary.getMappedValue(10, 20));
}
