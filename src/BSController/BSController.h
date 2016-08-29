#ifndef __BSController_H_INCLUDED__
#define __BSController_H_INCLUDED__

#include <iostream>
#include "../GPIO/GpioPin/GpioPin.h"
#include "../GPIO/IGpio/IGpio.h"

class BSController {
 public:
	BSController(unsigned int t_gpioPinNumber, unsigned int t_minPulseWidth, unsigned int t_maxPulseWidth, IGpio& t_IGpioInstance);
	~BSController();

	void setSpeed (float t_speedPercentage);
	float getSpeed ();

 private:
 	GpioPin Pin;
 	unsigned int minPulseWidth, maxPulseWidth, pwmFrequency;
};

#endif // __BSController_H_INCLUDED__