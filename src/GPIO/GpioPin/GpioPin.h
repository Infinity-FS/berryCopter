#ifndef __GPIOPIN_H_INCLUDED__
#define __GPIOPIN_H_INCLUDED__

#include "../IGpio/IGpio.h"
#include <iostream>

class GpioPin {
 public:
	GpioPin(unsigned int t_gpioNumber, unsigned int t_mode, IGpio& t_IGpio);
	~GpioPin();

	int getMode();
 	int getNumber();

 	// ---
 	// PWM: (Hz/range: 25 - 40000)
 	void setPWM (unsigned int t_open);
 	void setPWM (unsigned int t_pulseWidth_ns, unsigned int t_frequency_hz);
 	void setPWM (unsigned int t_frequency_hz, unsigned int t_range, unsigned int t_open);

 	int getPWM ();
 	int getPWMrange ();
 	int getPWMfrequency ();

 	float getPWMpercentage ();
 	// ---
 	void print();

 private:
 	IGpio& IGpioInstance;
 	unsigned int gpioNumber;
};

#endif // __GPIOPIN_H_INCLUDED__