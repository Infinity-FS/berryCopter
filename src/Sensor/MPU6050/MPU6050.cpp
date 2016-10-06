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
		this->read();
		std::cout<< "Gyro: ";
		std::cout << "X "<< (this->gyroData).X << ", ";
		std::cout << "Y "<< (this->gyroData).Y << ", ";
		std::cout << "Z "<< (this->gyroData).Z << "  ";

		std::cout<< "Accel: ";
		std::cout << "X "<< (this->acceleratorData).X << ", ";
		std::cout << "Y "<< (this->acceleratorData).Y << ", ";
		std::cout << "Z "<< (this->acceleratorData).Z << "\n";
		usleep(2000 * 1000); 
	}
}


// -------------------------------
// PRIVATE
// -------------------------------

void MPU6050::read () {
	int sizeToRead = 12;
	unsigned int regAdrr [sizeToRead] = {
		MPU6050_GYRO_XOUT_H, MPU6050_GYRO_XOUT_L, 
		MPU6050_GYRO_YOUT_H, MPU6050_GYRO_YOUT_L, 
		MPU6050_GYRO_ZOUT_H, MPU6050_GYRO_ZOUT_L,

		MPU6050_ACCEL_XOUT_H, MPU6050_ACCEL_XOUT_L,
		MPU6050_ACCEL_YOUT_H, MPU6050_ACCEL_YOUT_L,
		MPU6050_ACCEL_ZOUT_H, MPU6050_ACCEL_ZOUT_L
	};

	unsigned int result [sizeToRead] = {};
	I2CDevice::readRegister(regAdrr, result, sizeToRead);

	(this->gyroData).X = parseToShort((char) result[0], (char) result[1]);
	(this->gyroData).Y = parseToShort((char) result[2], (char) result[3]);
	(this->gyroData).Z = parseToShort((char) result[4], (char) result[5]);

	(this->accelerometerData).X = parseToShort((char) result[6], (char) result[7]);
	(this->accelerometerData).Y = parseToShort((char) result[8], (char) result[9]);
	(this->accelerometerData).Z = parseToShort((char) result[10], (char) result[11]);

	/*std::cout << "Gyro X: " << (this->gyroData).X << " Y: " << (this->gyroData).Y << " Z: " << (this->gyroData).Z;
	std::cout << " Acc X: " << (this->accelerometerData).X << " Y: "  << (this->accelerometerData).Y << " Z: " << (this->accelerometerData).Z;
	std::cout << "\n";*/
}

// --------------------
void MPU6050::readAccelOffset() {
	int sizeToRead = 6;
	unsigned int regAdrr [sizeToRead] = {
		MPU6050_ACCEL_XOFFS_USR_H, MPU6050_ACCEL_XOFFS_USR_L, 
		MPU6050_ACCEL_YOFFS_USR_H, MPU6050_ACCEL_YOFFS_USR_L, 
		MPU6050_ACCEL_ZOFFS_USR_H, MPU6050_ACCEL_ZOFFS_USR_L,
	};

	unsigned int result [sizeToRead] = {};
	I2CDevice::readRegister(regAdrr, result, sizeToRead);
	std::cout<< "Accel Offset ";
	std::cout<< "X:" << parseToShort((char) result[0], (char) result[1]);
	std::cout<< "Y:" << parseToShort((char) result[2], (char) result[3]);
	std::cout<< "Z:" << parseToShort((char) result[4], (char) result[5]);
	std::cout<< "\n";
}


// --------------------
void MPU6050::writeGyroOffset(axisData& t_gyroOffset){
	I2CDevice::writeRegister(MPU6050_GYRO_XOFFS_USR_H, (unsigned int) ((t_gyroOffset.X >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_GYRO_XOFFS_USR_L, (unsigned int) (t_gyroOffset.X & 0xff) );

	I2CDevice::writeRegister(MPU6050_GYRO_YOFFS_USR_H, (unsigned int) ((t_gyroOffset.Y >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_GYRO_YOFFS_USR_L, (unsigned int) (t_gyroOffset.Y & 0xff) );

	I2CDevice::writeRegister(MPU6050_GYRO_ZOFFS_USR_H, (unsigned int) ((t_gyroOffset.Z >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_GYRO_ZOFFS_USR_L, (unsigned int) (t_gyroOffset.Z & 0xff) );
}

// --------------------
void MPU6050::writeAccelOffset(axisData& t_accelOffset){
	I2CDevice::writeRegister(MPU6050_ACCEL_XOFFS_USR_H, (unsigned int) ((t_accelOffset.X >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_ACCEL_XOFFS_USR_L, (unsigned int) (t_accelOffset.X & 0xff) );

	I2CDevice::writeRegister(MPU6050_ACCEL_YOFFS_USR_H, (unsigned int) ((t_accelOffset.Y >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_ACCEL_YOFFS_USR_L, (unsigned int) (t_accelOffset.Y & 0xff) );

	I2CDevice::writeRegister(MPU6050_ACCEL_ZOFFS_USR_H, (unsigned int) ((t_accelOffset.Z >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_ACCEL_ZOFFS_USR_L, (unsigned int) (t_accelOffset.Z & 0xff) );
}


