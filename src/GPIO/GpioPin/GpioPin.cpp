#include "GpioPin.h"

// --------------------
// GpioPin constructor
GpioPin::GpioPin(unsigned int t_gpioNumber, unsigned int t_mode, IGpio& t_IGPIO): 
	IGpioInstance(t_IGPIO),
	gpioNumber(t_gpioNumber)
{
	(this->IGpioInstance).setMode(this->gpioNumber, t_mode);
	this->setPWM(800u, 120u, 0u);
}
// --------------------

// GpioPin destructor
GpioPin::~GpioPin() {
	// close Pin
	this->setPWM(800u, 120u, 0u);
	std::cout << "PIN(" << this->gpioNumber << ") destroyed: " << "\n";
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
	this->setPWM(800u, 120u, t_open);
}

void GpioPin::setPWM (unsigned int t_pulseWidth_ns, unsigned int t_frequency_hz) {
	// the time every period has in ns 
	int period_ns = 1000000/t_frequency_hz;
	this->setPWM(t_frequency_hz, period_ns, t_pulseWidth_ns);
}

void GpioPin::setPWM (unsigned int t_frequency_hz, unsigned int t_range, unsigned int t_open) {
	if (t_frequency_hz > 40000 ) {
		t_frequency_hz = 40000;
	} else if (t_frequency_hz < 0) {
		t_frequency_hz = 0;
	}

	if (t_range > 40000 ) {
		t_range = 40000;
	} else if (t_range < 0) {
		t_range = 0;
	}

	if (t_open > t_range) {
		t_open = t_range;
	} else if (t_open < 0) {
		t_open = 0;
	}

	(this->IGpioInstance).setPWMFrequency(this->gpioNumber, t_frequency_hz);
	(this->IGpioInstance).setPWMRange(this->gpioNumber, t_range);
	(this->IGpioInstance).setPWM(this->gpioNumber, t_open);
}
// --------------------
int GpioPin::getPWM (){
	return (this->IGpioInstance).getPWM(this->gpioNumber);
}

int GpioPin::getPWMrange (){
	return (this->IGpioInstance).getPWMRange(this->gpioNumber);
}

int GpioPin::getPWMfrequency (){
	return (this->IGpioInstance).getPWMFrequency(this->gpioNumber);
}

float GpioPin::getPWMpercentage (){
	return  (float) (this->getPWM()) / (float)(this->getPWMrange());
}
// --------------------
void GpioPin::print(){
	std::cout << "PIN(" << this->gpioNumber << ") pwm " << this->getPWM() << ", range " << this->getPWMrange() << ", percentage " << this->getPWMpercentage() << " freq " << this->getPWMfrequency() << "\n";
}



