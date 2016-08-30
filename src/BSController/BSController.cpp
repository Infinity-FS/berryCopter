#include "BSController.h"

// --------------------
// BSController constructor
BSController::BSController(unsigned int t_gpioPinNumber, unsigned int t_minPulseWidth, unsigned int t_maxPulseWidth, IGpio& t_IGpioInstance):
	Pin(t_gpioPinNumber, 1, t_IGpioInstance),
	minPulseWidth (t_minPulseWidth),
	maxPulseWidth (t_maxPulseWidth),
	pwmFrequency(50u) // hz
{
	this->setSpeed(0.0f);
}
// --------------------
// BSController destructor
BSController::~BSController() {
	this->setSpeed(0.0f);
}
// --------------------
// Speed
void BSController::setSpeed (double t_speedPercentage) {
	unsigned int pulseRange = this->maxPulseWidth -  this->minPulseWidth;
	Pin.setPWM(this->minPulseWidth + (unsigned int) (t_speedPercentage * pulseRange), this->pwmFrequency);
	Pin.print();
}

double BSController::getSpeed () {
	unsigned int pulseRange = this->maxPulseWidth - this->minPulseWidth;
	return (double) (Pin.getPWM() - this->minPulseWidth) / (double) pulseRange;
}

int BSController::getSpeedPulseWave_ns () {
	return Pin.getPWM();
}
// --------------------
