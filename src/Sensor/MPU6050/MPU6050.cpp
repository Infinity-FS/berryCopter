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
	unsigned int resetValue = 0b10000000;
	I2CDevice::writeRegister(MPU6050_PWR_MGMT_1, &resetValue);
}
// --------------------

void MPU6050::startLoop() {
	unsigned int tmp = 0;
	unsigned int* p_val = &tmp;
	unsigned int* p_lastVal = &tmp;

	unsigned int reg = 00;

	for(;;) {
		std::cin >> reg;
		I2CDevice::readRegister(reg, p_val);
		//if (*p_lastValue != *p_value) {
			//p_lastVal = p_val;
		//}
	}
	
}