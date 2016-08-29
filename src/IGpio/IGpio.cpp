#include "IGpio.h"

// --------------------
// GPIO()
IGpio::IGpio() {
	if (gpioInitialise() < 0) {
   		// pigpio initialisation failed.
		std::cout << "FAILED";
	} else {
   		// pigpio initialised okay.
		std::cout << "Initalized PIGPIO\n";
	}
}
// --------------------
// ~GPIO()
IGpio::~IGpio() {
	gpioTerminate();
	std::cout << "IGpio terminated \n";
}

// --------------------
// MODE
int IGpio::setMode(unsigned int t_gpioNb, unsigned int t_mode) {
	return gpioSetMode(t_gpioNb, t_mode);
}

int IGpio::getMode(unsigned int t_gpioNb) {
	return gpioGetMode(t_gpioNb);
}

// --------------------
// PWM cycle (0 - range)
int IGpio::setPWM(unsigned int t_gpioNb, unsigned int t_open) {
	return gpioPWM(t_gpioNb, t_open);
}

int IGpio::getPWM(unsigned int t_gpioNb) {
	return gpioGetPWMdutycycle(t_gpioNb);
}

// t_freq in Hz
int IGpio::setPWMFrequency(unsigned int t_gpioNb, unsigned int t_freq) {
	return gpioSetPWMfrequency(t_gpioNb, t_freq);
}

int IGpio::getPWMFrequency(unsigned int t_gpioNb) {
return gpioGetPWMfrequency(t_gpioNb);
}

// Range 
int IGpio::setPWMRange (unsigned int t_gpioNb, unsigned int t_range) {
	return gpioSetPWMrange(t_gpioNb, t_range);
}

int IGpio::getPWMRange(unsigned int t_gpioNb) {
	return gpioGetPWMrange(t_gpioNb);
}
// --------------------