#include "GroveLedbar.h"

// Pin definition
int dataPin = 12;
int clockPin = 13;

GroveLedbar strip = GroveLedbar(dataPin, clockPin);

void setup(){
  Serial.begin(57600);
}

void loop() {
  unsigned int i=0x0000;
  while(i<=0x03ff) {
    strip.setCmdMode();
    strip.sendLED(i); // Set LED States
    strip.latchData();
    i=i*2+1;
   delay(100); 
  }
}