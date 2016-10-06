#include "MPU6050.h"

// --------------------
// FlightController constructor
MPU6050::MPU6050 (int t_AccelerometerRange_G, IGpio& t_IGpioInstance):
I2CDevice (0x68, 1, t_IGpioInstance),
Accelerometer(t_AccelerometerRange_G ,16, 1000, 2000, 50)
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

	(this->accelerometerAxisData).X = ((((short) result[0] ) << 8) | (char) result[1]);
	(this->accelerometerAxisData).Y = ((((short) result[2] ) << 8) | (char) result[3]);
	(this->accelerometerAxisData).Z = ((((short) result[4] ) << 8) | (char) result[5]);
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
	std::cout<< "X:" << ((((short) result[0] ) << 8) | (char) result[1]);
	std::cout<< "Y:" << ((((short) result[2] ) << 8) | (char) result[3]);
	std::cout<< "Z:" << ((((short) result[4] ) << 8) | (char) result[5]);
	std::cout<< "\n";
}


// --------------------
void MPU6050::writeAccelerometerOffset (axisData<short> &t_offset){
	I2CDevice::writeRegister(MPU6050_ACCEL_XOFFS_USR_H, (unsigned int) ((t_offset.X >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_ACCEL_XOFFS_USR_L, (unsigned int) (t_offset.X & 0xff) );

	I2CDevice::writeRegister(MPU6050_ACCEL_YOFFS_USR_H, (unsigned int) ((t_offset.Y >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_ACCEL_YOFFS_USR_L, (unsigned int) (t_offset.Y & 0xff) );

	I2CDevice::writeRegister(MPU6050_ACCEL_ZOFFS_USR_H, (unsigned int) ((t_offset.Z >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_ACCEL_ZOFFS_USR_L, (unsigned int) (t_offset.Z & 0xff) );
}


