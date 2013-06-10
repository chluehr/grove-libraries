#ifndef AccelCompass_h
#define AccelCompass_h

#include <Arduino.h>
#include <Wire.h>
#include <math.h>

#define ACCELE_SCALE 2  // accelerometer full-scale, should be 2, 4, or 8

/* LSM303 Address definitions */
#define LSM303_MAG  0x1E  // assuming SA0 grounded
#define LSM303_ACC  0x18  // assuming SA0 grounded

#define X 0
#define Y 1
#define Z 2

/* LSM303 Register definitions */
#define CTRL_REG1_A 0x20
#define CTRL_REG2_A 0x21
#define CTRL_REG3_A 0x22
#define CTRL_REG4_A 0x23
#define CTRL_REG5_A 0x24
#define HP_FILTER_RESET_A 0x25
#define REFERENCE_A 0x26
#define STATUS_REG_A 0x27
#define OUT_X_L_A 0x28
#define OUT_X_H_A 0x29
#define OUT_Y_L_A 0x2A
#define OUT_Y_H_A 0x2B
#define OUT_Z_L_A 0x2C
#define OUT_Z_H_A 0x2D
#define INT1_CFG_A 0x30
#define INT1_SOURCE_A 0x31
#define INT1_THS_A 0x32
#define INT1_DURATION_A 0x33
#define CRA_REG_M 0x00
#define CRB_REG_M 0x01//refer to the Table 58 of the datasheet of LSM303DLM
	#define MAG_SCALE_1_3 0x20//full-scale is +/-1.3Gauss
	#define MAG_SCALE_1_9 0x40//+/-1.9Gauss
	#define MAG_SCALE_2_5 0x60//+/-2.5Gauss
	#define MAG_SCALE_4_0 0x80//+/-4.0Gauss
	#define MAG_SCALE_4_7 0xa0//+/-4.7Gauss
	#define MAG_SCALE_5_6 0xc0//+/-5.6Gauss
	#define MAG_SCALE_8_1 0xe0//+/-8.1Gauss
#define MR_REG_M 0x02
#define OUT_X_H_M 0x03
#define OUT_X_L_M 0x04
#define OUT_Y_H_M 0x07
#define OUT_Y_L_M 0x08
#define OUT_Z_H_M 0x05
#define OUT_Z_L_M 0x06
#define SR_REG_M 0x09
#define IRA_REG_M 0x0A
#define IRB_REG_M 0x0B
#define IRC_REG_M 0x0C


class AccelCompass
{
  public:
    AccelCompass();
    float getHeading(int * magValue);
    float getTiltHeading(int * magValue, float * accelValue);
    void getLSM303_mag(int * rawValues);
    void getLSM303_accel(int * rawValues);
    void initLSM303(int fs);
    void waitReady();
    void setup();
  private:
    byte LSM303_read(byte address);
    void LSM303_write(byte data, byte address);

    /* Global variables */
    int _accel[3];  // we'll store the raw acceleration values here
    int _mag[3];  // raw magnetometer values stored here
    float _realAccel[3];  // calculated acceleration values here

};

#endif