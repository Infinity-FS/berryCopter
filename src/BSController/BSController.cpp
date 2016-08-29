#include "BSController.h"

// --------------------
// BSController constructor
BSController::BSController(unsigned int t_gpioPinNumber, unsigned int t_minPulseWidth, unsigned int t_maxPulseWidth, IGpio& t_IGpioInstance):
	Pin(t_gpioPinNumber, 1, t_IGpioInstance),
	minPulseWidth (t_minPulseWidth),
	maxPulseWidth (t_maxPulseWidth),
	pwmFrequency(50u) // hz
{
}
// --------------------
// BSController destructor
BSController::~BSController() {
}
// --------------------
// Speed
void BSController::setSpeed (float t_speedPercentage) {
	unsigned int pulseRange = this->maxPulseWidth -  this->minPulseWidth;
	Pin.setPWM(this->minPulseWidth + (unsigned int) (t_speedPercentage * pulseRange), this->pwmFrequency);
	Pin.print();
}

float BSController::getSpeed () {
	unsigned int pulseRange = this->maxPulseWidth - this->minPulseWidth;
	return (float) (Pin.getPWM() - this->minPulseWidth) / (float) pulseRange;
}
// --------------------
