#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

class LEDBar {
 public:
  LEDBar(uint8_t dpin, uint8_t cpin); // Configurable pins
  void
    sendLED(uint16_t data),
    setCmdMode(void),
	latchData(void),
	setGauge(uint8_t gauge),
	setSingleBar(uint8_t barnum);
 private:
  void
    send16bitData(uint16_t data);
  uint8_t
    clkpin    , datapin,     // Clock & data pin numbers
    clkpinmask, datapinmask; // Clock & data PORT bitmasks
  volatile uint8_t
    *clkport  , *dataport;   // Clock & data PORT registers
};
