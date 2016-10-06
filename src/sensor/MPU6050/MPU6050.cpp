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

void MPU6050::wakeUp () {
	// Set Clocksource to GyroX
	I2CDevice::writeRegister(MPU6050_PWR_MGMT_1, 0b00000001);

	// Disables self tests & set Gyrorange to +-250 grad/sec
	I2CDevice::writeRegister(MPU6050_GYRO_CONFIG, 0b00000000);

	// Disables self tests & set Accelrange to +- 2g
	I2CDevice::writeRegister(MPU6050_ACCEL_CONFIG, 0b00000000);
}

// --------------------

void MPU6050::startLoop() {
	for(;;){
		this->readAccelerometer();

		std::cout<< "Accel: ";
		std::cout << "X "<< (this->accelerometerAxisData).X << ", ";
		std::cout << "Y "<< (this->accelerometerAxisData).Y << ", ";
		std::cout << "Z "<< (this->accelerometerAxisData).Z << "\n";
		usleep(2000 * 1000); 
	}
}


// -------------------------------
// PRIVATE
// -------------------------------

void MPU6050::readAccelerometer () {
	int sizeToRead = 6;
	unsigned int regAdrr [sizeToRead] = {
		MPU6050_ACCEL_XOUT_H, MPU6050_ACCEL_XOUT_L,
		MPU6050_ACCEL_YOUT_H, MPU6050_ACCEL_YOUT_L,
		MPU6050_ACCEL_ZOUT_H, MPU6050_ACCEL_ZOUT_L
	};

	unsigned int result [sizeToRead] = {};
	I2CDevice::readRegister(regAdrr, result, sizeToRead);

	(this->accelerometerAxisData).X = (((short) result[1] ) << 8) | result[0];
	(this->accelerometerAxisData).Y = (((short) result[3] ) << 8) | result[2];
	(this->accelerometerAxisData).Z = (((short) result[5] ) << 8) | result[4];
}

// --------------------
void MPU6050::readAccelerometerOffset(axisData<short> &t_offset) {
	int sizeToRead = 6;
	unsigned int regAdrr [sizeToRead] = {
		MPU6050_ACCEL_XOFFS_USR_H, MPU6050_ACCEL_XOFFS_USR_L, 
		MPU6050_ACCEL_YOFFS_USR_H, MPU6050_ACCEL_YOFFS_USR_L, 
		MPU6050_ACCEL_ZOFFS_USR_H, MPU6050_ACCEL_ZOFFS_USR_L,
	};

	unsigned int result [sizeToRead] = {};
	I2CDevice::readRegister(regAdrr, result, sizeToRead);
	std::cout<< "Accel Offset ";
	std::cout<< "X:" << (((short) result[1] ) << 8) | result[0];
	std::cout<< "Y:" << (((short) result[3] ) << 8) | result[2];
	std::cout<< "Z:" << (((short) result[5] ) << 8) | result[4];
	std::cout<< "\n";
}


// --------------------
void MPU6050::writeAccelerometerOffset (axisData<short> &t_offset){
	I2CDevice::writeRegister(MPU6050_ACCEL_XOFFS_USR_H, (unsigned int) ((t_accelOffset.X >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_ACCEL_XOFFS_USR_L, (unsigned int) (t_accelOffset.X & 0xff) );

	I2CDevice::writeRegister(MPU6050_ACCEL_YOFFS_USR_H, (unsigned int) ((t_accelOffset.Y >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_ACCEL_YOFFS_USR_L, (unsigned int) (t_accelOffset.Y & 0xff) );

	I2CDevice::writeRegister(MPU6050_ACCEL_ZOFFS_USR_H, (unsigned int) ((t_accelOffset.Z >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_ACCEL_ZOFFS_USR_L, (unsigned int) (t_accelOffset.Z & 0xff) );
}

