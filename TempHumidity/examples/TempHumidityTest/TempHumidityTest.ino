// Example testing sketch for Grove Temperature&Humidity sensor (DHT11)

#include "TempHumidity.h"

// Sensor on Digital Pin 8, DHT11 type (Grove v1.0)
TempHumidity tempHumidity;

void setup() {
  Serial.begin(9600); 
  Serial.println("Temperature&Humidity test!");
   tempHumidity.setup(8, DHT11);
}

void loop() {

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = tempHumidity.readHumidity();
  float t = tempHumidity.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from Temperature&Humidity Sensor");
  } else {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
  }
}
