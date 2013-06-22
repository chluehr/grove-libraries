#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

class Button {
	public:
		Button(void); // Configurable pins
		boolean isPressed(void);
		boolean isClicked(void);
		void setup(int dpin);
 private:
		int	datapin;
		int	value;
		int	oldValue;
		int	state;
};
