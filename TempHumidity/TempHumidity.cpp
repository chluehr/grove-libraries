/* 
TempHumidity library, based on:
DHT library 
MIT license
written by Adafruit Industries
*/
// Modified by SeeedStudio, public domain 

#include "TempHumidity.h"

TempHumidity::TempHumidity() {

}

void TempHumidity::setup(uint8_t pin, uint8_t type, uint8_t count) {

  _pin = pin;
  _type = type;
  _count = count;
  firstreading = true;

  // set up the pins!
  pinMode(_pin, INPUT);
  digitalWrite(_pin, HIGH);
  _lastreadtime = 0;
}

//boolean S == Scale.  True == Farenheit; False == Celcius
float TempHumidity::readTemperature(bool S) {
  float f;

  if (read()) {
    switch (_type) {
    case DHT11:
      f = data[2];
      if(S)
      	f = convertCtoF(f);
      	
      return f;
    case DHT22:
    case DHT21:
      f = data[2] & 0x7F;
      f *= 256;
      f += data[3];
      f /= 10;
      if (data[2] & 0x80)
	f *= -1;
      if(S)
	f = convertCtoF(f);

      return f;
    }
  }
  Serial.print("Read fail");
  return NAN;
}

float TempHumidity::convertCtoF(float c) {
	return c * 9 / 5 + 32;
}

float TempHumidity::readHumidity(void) {
  float f;
  if (read()) {
    switch (_type) {
    case DHT11:
      f = data[0];
      return f;
    case DHT22:
    case DHT21:
      f = data[0];
      f *= 256;
      f += data[1];
      f /= 10;
      return f;
    }
  }
  Serial.print("Read fail");
  return NAN;
}

uint8_t TempHumidity::read_dht11_dat(void)
{
  byte i = 0;
  byte result=0;
  for(i=0; i< 8; i++){
    while(!digitalRead(_pin));  // wait for 50us
    delayMicroseconds(30);

    if(digitalRead(_pin)) 
      result |=(1<<(7-i));
    while(digitalRead(_pin));  // wait '1' finish
  }
  return result;
}

boolean TempHumidity::read(void) {
  uint8_t laststate = HIGH;
  uint8_t counter = 0;
  uint8_t j = 0, i;
  unsigned long currenttime;
  digitalWrite(_pin, HIGH);
  delay(250);

  currenttime = millis();
  if (currenttime < _lastreadtime) {  
    _lastreadtime = 0;
  }
  if (!firstreading && ((currenttime - _lastreadtime) < 2000)) {
    return true; // return last correct measurement
  }
  firstreading = false;
  _lastreadtime = millis();

  data[0] = data[1] = data[2] = data[3] = data[4] = 0;
    
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  delay(10);
 // cli();
  digitalWrite(_pin, HIGH);
  delayMicroseconds(40);
  //delay(1);
  pinMode(_pin, INPUT);
  while(digitalRead(_pin)){
    Serial.println("dht11 start condition 1 not met");
  }
  delayMicroseconds(80);

  while(!digitalRead(_pin)){
    Serial.println("dht11 start condition 2 not met");
  }
  delayMicroseconds(80);
  
  for (i=0; i<5; i++){
    data[i] = read_dht11_dat();
	}

  if (
      (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) ) {
    return true;
  }

  return false;
}
