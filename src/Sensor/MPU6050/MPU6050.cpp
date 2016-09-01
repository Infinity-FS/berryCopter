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

MPU6050::reset () {
	char hex_00 = { 0x00 };
	I2CDevice.writeRegister(MPU6050_PWR_MGMT_1, &hex_00[0], 1);
}
// --------------------

MPU6050::startLoop() {
	char* lastValue = new char[1];
	char* value = new char[1];
	for(;;) {
		MPU6050.readRegister(0x75, value);
		if (*lastValue != value) {
			lastValue = value;
			printf("%02x ", *lastValue);
		}
	}
	
}