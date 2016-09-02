#include "MPU6050.h"

// --------------------
// FlightController constructor
MPU6050::MPU6050 (IGpio& t_IGpioInstance): 
	I2CDevice (0x68, 1, t_IGpioInstance)
{
}
// --------------------
// FlightController destructor
MPU6050::~MPU6050 () {
}
// --------------------

void MPU6050::reset () {
	I2CDevice::writeRegister(MPU6050_PWR_MGMT_1, 0b10000000);
}
// --------------------

void MPU6050::startLoop() {
	int tmp = 0;
	unsigned int* val = &tmp;
	unsigned int* lastVal = &tmp;

	unsigned int reg = 00;

	for(;;) {
		std::cin >> reg;
		I2CDevice::readRegister(reg, ,val);
		//if (*p_lastValue != *p_value) {
			lastVal = val;
			std::cout<< reg << " = ";
			printf("%02x ", *lastVal);
		//}
	}
	
}