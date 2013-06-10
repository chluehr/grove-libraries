#include "LEDBar.h"
// Constructor for use with arbitrary clock/data pins:
LEDBar::LEDBar(uint8_t dpin, uint8_t cpin) {
  pinMode(dpin, OUTPUT);
  pinMode(cpin, OUTPUT);
  datapin     = dpin;
  clkpin      = cpin;
  clkport     = portOutputRegister(digitalPinToPort(cpin));
  clkpinmask  = digitalPinToBitMask(cpin);
  dataport    = portOutputRegister(digitalPinToPort(dpin));
  datapinmask = digitalPinToBitMask(dpin);
}

void LEDBar::sendLED(uint16_t data) {
  unsigned char i;
  for(i=0;i<12;i++) {
    if(data & 0x0001)
      send16bitData(0x00ff);
    else 
      send16bitData(0x0000);
    data = data >> 1;
  }
}

void LEDBar::setSingleBar(uint8_t barnum) {
  setCmdMode();
  sendLED(0x01<<barnum);
  latchData();
}

void LEDBar::setGauge(uint8_t gauge) {

  uint16_t val = 0;
  for (uint16_t barnum = 0; barnum < gauge ; barnum++) {
	
	val = val |( 0x01<<barnum);
  }
  setCmdMode();
  sendLED(val);
  latchData();
}


void LEDBar::setCmdMode(void){
  send16bitData(0x0000);
}
void LEDBar::send16bitData(uint16_t data) {
  for(unsigned char i=0;i<16;i++) {
    if(data&0x8000) {
      *dataport |= datapinmask;
    } else {
      *dataport &=~ datapinmask;
    }
    *clkport ^= clkpinmask;
    data <<= 1;
  }
}

//latch routine for MY9221 data exchange
void LEDBar::latchData(void) {
  *clkport &=~ datapinmask;
  delayMicroseconds(10);
  for(unsigned char i=0;i<8;i++) {
    *clkport ^= datapinmask;
  }
}