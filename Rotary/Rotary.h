#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

#define ADC_REF 5//reference voltage of ADC is 5v
#define GROVE_VCC 5//VCC of the grove interface is normally 5v
#define FULL_ANGLE 300//full value of the rotary angle is 300 degrees

class Rotary {
	public:
		Rotary(void);
		void setup(int apin);
		float getDegree(void);
		int getMappedValue(int min, int max);
	private:
		int	datapin;
};
