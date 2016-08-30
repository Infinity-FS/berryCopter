#ifndef __BS_CONTROLLER_H_INCLUDED__
#define __BS_CONTROLLER_H_INCLUDED__

#include <iostream>
#include "../GPIO/GpioPin/GpioPin.h"
#include "../GPIO/IGpio/IGpio.h"

// Brushless Speed Controller
class BSController {
 public:
	BSController(unsigned int t_gpioPinNumber, unsigned int t_minPulseWidth, unsigned int t_maxPulseWidth, IGpio& t_IGpioInstance);
	~BSController();

	void setSpeed (double t_speedPercentage);
	double getSpeed ();

	int getSpeedPulseWave_ns();
 private:
 	GpioPin Pin;
 	unsigned int minPulseWidth, maxPulseWidth, pwmFrequency;
};

#endif // __BS_CONTROLLER_H_INCLUDED__