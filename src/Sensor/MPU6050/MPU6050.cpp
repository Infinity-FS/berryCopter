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
	unsigned int wakeUp = 0b00000000;
	I2CDevice::writeRegister(MPU6050_PWR_MGMT_1, &wakeUp);
}
// --------------------

void MPU6050::startLoop() {
	for(;;){
		this->readSensorData();
	}
}

void MPU6050::readSensorData () {
	int sizeToRead = 12;
	unsigned int regAdrr [sizeToRead] = {MPU6050_GYRO_XOUT_H, MPU6050_GYRO_XOUT_L, 
								MPU6050_GYRO_YOUT_H, MPU6050_GYRO_YOUT_L, 
								MPU6050_GYRO_ZOUT_H, MPU6050_GYRO_ZOUT_L,

							    MPU6050_ACCEL_XOUT_H, MPU6050_ACCEL_XOUT_L,
							    MPU6050_ACCEL_YOUT_H, MPU6050_ACCEL_YOUT_L,
							    MPU6050_ACCEL_ZOUT_H, MPU6050_ACCEL_ZOUT_L};

	unsigned int result [sizeToRead] = {};
	I2CDevice::readRegister(regAdrr, result, sizeToRead);

	(this->gyroData).X = parseToShort((char) result[0], (char) result[1]);
	(this->gyroData).Y = parseToShort((char) result[2], (char) result[3]);
	(this->gyroData).Z = parseToShort((char) result[4], (char) result[5]);

	(this->acceleratorData).X = parseToShort((char) result[6], (char) result[7]);
	(this->acceleratorData).Y = parseToShort((char) result[8], (char) result[9]);
	(this->acceleratorData).Z = parseToShort((char) result[10], (char) result[11]);

	std::cout << "Gyro X: " << (this->gyroData).X << " Y: " (this->gyroData).Y << " Z: " (this->gyroData).Z;
	std::cout << "Acc X: " << (this->acceleratorData).X << " Y: " (this->acceleratorData).Y << " Z: " (this->acceleratorData).Z;
	std::cout << "\n";
}