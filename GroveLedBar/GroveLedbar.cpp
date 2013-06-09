#include "GroveLedbar.h"
// Constructor for use with arbitrary clock/data pins:
GroveLedbar::GroveLedbar(uint8_t dpin, uint8_t cpin) {
  pinMode(dpin, OUTPUT);
  pinMode(cpin, OUTPUT);
  datapin     = dpin;
  clkpin      = cpin;
  clkport     = portOutputRegister(digitalPinToPort(cpin));
  clkpinmask  = digitalPinToBitMask(cpin);
  dataport    = portOutputRegister(digitalPinToPort(dpin));
  datapinmask = digitalPinToBitMask(dpin);
}

void GroveLedbar::sendLED(uint16_t data) {
  unsigned char i;
  for(i=0;i<12;i++) {
    if(data & 0x0001)
      send16bitData(0x00ff);
    else 
      send16bitData(0x0000);
    data = data >> 1;
  }
}

void GroveLedbar::setSingleBar(uint8_t barnum) {
  setCmdMode();
  sendLED(0x01<<barnum);
  latchData();
}

void GroveLedbar::setCmdMode(void){
  send16bitData(0x0000);
}
void GroveLedbar::send16bitData(uint16_t data) {
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
void GroveLedbar::latchData(void) {
  *clkport &=~ datapinmask;
  delayMicroseconds(10);
  for(unsigned char i=0;i<8;i++) {
    *clkport ^= datapinmask;
  }
}