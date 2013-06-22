#include <Button.h>

Button myButton;

void setup()
{
  Serial.begin(9600);	// Serial is used for debugging
  myButton.setup(2);	// select pin to use
}

void loop()
{

  delay(500);  // delay for serial readability
  if (myButton.isPressed()) {
	Serial.println("PRESSED");
  } else {
	Serial.println("-------");
  }
  
}
