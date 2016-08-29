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
 	// PWM 
 	void setPWM (unsigned int t_open);
 	void setPWM (float t_openfPercentage);
 	// Hz: 25 - 40000
 	void setPWM (unsigned int t_pulseWidth_ns, unsigned int t_frequency_hz);

 	void setPWMrange (unsigned int t_range);

 	int getPWM ();
 	int getPWMrange ();
 	float getPWMpercentage ();
 	int getPWMfrequency ();

 	//---
 	void print();

 private:
 	IGpio& IGpioInstance;
 	unsigned int gpioNumber;
};

#endif // __GPIOPIN_H_INCLUDED__