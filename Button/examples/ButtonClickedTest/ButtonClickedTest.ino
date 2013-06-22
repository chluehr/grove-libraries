#include <Button.h>

Button myButton;

void setup()
{
  Serial.begin(9600);	// Serial is used for debugging
  myButton.setup(2);	// select pin to use
}

void loop()
{

  delay(100);  // delay for serial readability
  if (myButton.isClicked()) {
	Serial.println("CLICKED");
  } else {
	Serial.println("-------");
  }
  
}
