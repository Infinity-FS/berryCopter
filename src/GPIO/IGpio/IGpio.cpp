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
	std::cout << "PIGPIO terminated \n";
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
// I2C
int IGpio::registerI2CDevice (unsigned int t_busInterface, unsigned int t_addr) {
	return i2cOpen(t_busInterface, t_addr, 0);
}

int IGpio::unregisterI2CDevice (unsigned int t_deviceHandleID) {
	return i2cClose(t_deviceHandleID);
}

int IGpio::readI2CRegister(unsigned int t_deviceHandleID, unsigned int t_RegAddr, char* t_buffer, unsigned int count) {
	return i2cReadI2CBlockData(t_deviceHandleID, t_RegAddr, t_buffer, count);
}

int IGpio::writeI2CRegister(unsigned int t_deviceHandleID, unsigned int t_RegAddr, char* t_val, unsigned int count) {
	return i2cWriteI2CBlockData(t_deviceHandleID, t_RegAddr, t_val, count);
}
