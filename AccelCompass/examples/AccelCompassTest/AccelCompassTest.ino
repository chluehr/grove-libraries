#include <AccelCompass.h>
#include <Wire.h>

/* Global variables */
int accel[3];  // we'll store the raw acceleration values here
int mag[3];  // raw magnetometer values stored here
float realAccel[3];  // calculated acceleration values here

AccelCompass accelCompass;

void setup()
{
  Serial.begin(9600);  // Serial is used for debugging
  accelCompass.setup();
}

void loop()
{
  delay(1000);  // delay for serial readability
  Serial.println("**************");

  accelCompass.getLSM303_accel(accel);  // get the acceleration values and store them in the accel array
  accelCompass.waitReady();
  accelCompass.getLSM303_mag(mag);  // get the magnetometer values, store them in mag
  //printValues(mag, accel);  // print the raw accel and mag values, good debugging
  Serial.println("Acceleration of X,Y,Z is");
  for (int i=0; i<3; i++)
  {
    realAccel[i] = accel[i] / pow(2, 15) * ACCELE_SCALE;  // calculate real acceleration values, in units of g
	Serial.print(realAccel[i]);
	Serial.println("g");
  }
  // print both the level, and tilt-compensated headings below to compare 
  Serial.println("The clockwise angle between the magnetic north and x-axis: ");
  Serial.print(accelCompass.getHeading(mag), 3); // this only works if the sensor is level
  Serial.println(" degrees");
  Serial.print("The clockwise angle between the magnetic north and the projection");
  Serial.println(" of the positive x-axis in the horizontal plane: ");
  Serial.print(accelCompass.getTiltHeading(mag, realAccel), 3);  // see how awesome tilt compensation is?!
  Serial.println(" degrees");
  /*
  */
  delay(200);  // delay for serial readability
}

void printValues(int * magArray, int * accelArray)
{
  /* print out mag and accel arrays all pretty-like */
  Serial.print(accelArray[X], DEC);
  
  Serial.print("\t");
  Serial.print(accelArray[Y], DEC);
  Serial.print("\t");
  Serial.print(accelArray[Z], DEC);
  Serial.print("\t\t");
  
  Serial.print(magArray[X], DEC);
  Serial.print("\t");
  Serial.print(magArray[Y], DEC);
  Serial.print("\t");
  Serial.print(magArray[Z], DEC);
  Serial.println();
}

