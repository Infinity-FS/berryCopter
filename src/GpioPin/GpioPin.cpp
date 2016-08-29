#include "GpioPin.h"

/ --------------------
// GpioPin constructor
GpioPin::GpioPin(unsigned int t_gpioNumber, unsigned int t_mode, const IGpio& t_IGPIO) {
	this->IGpioInstance = t_IGPIO;
	this->gpioNumber = t_gpioNumber;
	(this->IGpioInstance).setMode(this->gpioNumber, t_mode);
}
// --------------------

// GpioPin destructor
GpioPin::~GpioPin() {
	// close Pin
	(this->IGpioInstance).setPWM(this->gpioNumber, 0);
}
// --------------------
int GpioPin::getMode() {
	return (this->IGpioInstance).getMode(this->gpioNumber);
}

int GpioPin::getNumber() {
	return this->gpioNumber;
}
// --------------------
// PWM
void GpioPin::setPWM (unsigned int t_open) {
	string 
	int range = (this->IGpioInstance).getPWMRange(this->gpioNumber);

	if (t_open > range) {
		t_open = range;
	} else if (t_open < 0) {
		t_open = 0;
	}

	(this->IGpioInstance).setPWM(this->gpioNumber, t_open);
}

void GpioPin::setPWM (float t_fopenPercentage) {
	this->setPWM((int) (t_fopenPercentage * range));
}

void GpioPin::setPWM (unsigned int t_pulseWidth_ns, unsigned int t_frequency_hz) {
	(this->IGpioInstance).setPWMFrequency(this->gpioNumber, t_frequency_hz);

	// the time every period has in ns 
	int period_ns = 1000000/t_frequency_hz;
	// set range to period_ns (25-40000)
	this->setPWMrange(period_ns);

	// set the desired pulseWidth
	this->setPWM(t_pulseWidth_ns);
}
// --------------------
void GpioPin::setPWMrange (unsigned int t_range) {
	if(t_range < 25){
		t_range = 25;
	} else if (t_range > 40000) {
		t_range = 40000;
	}
	(this->IGpioInstance).setRange(this->gpioNumber, t_range);
}
// --------------------
int GpioPin::getPWM (){
	return this->IGpioInstance).getPWM(this->gpioNumber);
}
// --------------------
int GpioPin::getPWMrange (){
	return this->IGpioInstance).getPWMRange(this->gpioNumber);
}
// --------------------
int GpioPin::getPWMrange (){
	return this->IGpioInstance).getPWMPercentage(this->gpioNumber);
}
// --------------------
int GpioPin::getPWMfrequency (){
	return this->IGpioInstance).getPWMFrequency(this->gpioNumber);
}
// --------------------



