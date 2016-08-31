#include "I2CDevice.h"

// --------------------
// FlightController constructor
I2CDevice::I2CDevice(unsigned int t_I2CAddr, unsigned int t_busInterfaceId, IGpio& t_IGpioInstance):
	I2CAddr(t_I2CAddr),
	IGpioInstance(t_IGpioInstance)
{
	this->I2CHandleID = (this->IGpioInstance).registerI2CDevice(t_busInterfaceId, this->I2CAddr);
	if(this->I2CHandleID >= 0) {
		std::cout << "I2C device "<< this->I2CAddr <<" Registered at " << this->I2CHandleID << "\n";
	} else {
		std::cout << "FAILED to register I2C device "<< this->I2CAddr << "\n";
	}
}
// --------------------
// FlightController destructor
I2CDevice::~I2CDevice() {
	(this->IGpioInstance).unregisterI2CDevice(this->I2CHandleID);
}
// --------------------

int I2CDevice::readRegister(unsigned int t_regAddr, unsigned int byteCount, char* buffer) {
	int readBytesCount = (this->IGpioInstance).readI2CRegister(this->I2CHandleID, t_regAddr, buffer, byteCount);
	if (readBytesCount == byteCount) {
		return 1;
	} else {
		return 0;
	}
}