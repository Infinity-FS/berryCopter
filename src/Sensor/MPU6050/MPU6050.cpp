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
	}
}

// --------------------

void MPU6050::calibrate() {
	unsigned int iterations = 1000; // iterations to calculate the mean value
	unsigned int maxAccelError = 8;
	unsigned int maxGyroError = 4;

	axisData tmp_gyroOffset, tmp_accelOffset;


	int trial = 0;
	while(true) {

		if(trial % 100 == 0){
			std::cout<<"100 corrections performed\n";
		}

		trial++;


		this->writeGyroOffset(tmp_gyroOffset);
		this->writeAccelOffset(tmp_accelOffset);

		axisData tmp_gyroMean, tmp_accelMean;

		unsigned int i;
		for(i=0; i<iterations; i++) {

			// reads data and updates class' values
			this->read();

			// add values
			tmp_gyroMean.X += (this->gyroData).X;
			tmp_gyroMean.Y += (this->gyroData).Y;
			tmp_gyroMean.Z += (this->gyroData).Z;

			tmp_accelMean.X += (this->acceleratorData).X;
			tmp_accelMean.Y += (this->acceleratorData).Y;
			tmp_accelMean.Z += (this->acceleratorData).Z;

			// wait for 2 ms
			usleep(2000); 
		}
		
		// divide by iterations to get the mean
		tmp_gyroMean.X /= iterations;
		tmp_gyroMean.Y /= iterations;
		tmp_gyroMean.Z /= iterations;

		tmp_accelMean.X /= iterations;
		tmp_accelMean.Y /= iterations;
		tmp_accelMean.Z /= iterations;

		// check for every axis, if calibration is complete
		int axisComplete = 0;

		// gyro axis X, Y, Z
		if (abs(tmp_gyroMean.X) <= maxGyroError) {
			tmp_gyroOffset.X -= tmp_gyroMean.X / (maxGyroError);
		} else {
			axisComplete++;
		}

		if (abs(tmp_gyroMean.Y) <= maxGyroError) {
			tmp_gyroOffset.Y -= tmp_gyroMean.Y / (maxGyroError);
		} else {
			axisComplete++;
		}

		if (abs(tmp_gyroMean.Z) <= maxGyroError) {
			tmp_gyroOffset.Z -= tmp_gyroMean.Z / (maxGyroError);
		} else {
			axisComplete++;
		}

		// accel axis X, Y, Z
		if (abs(tmp_accelMean.X) <= maxAccelError) {
			tmp_accelOffset.X -= tmp_accelMean.X / (maxAccelError);
		} else {
			axisComplete++;
		}

		if (abs(tmp_accelMean.Y) <= maxAccelError) {
			tmp_accelOffset.Y -= tmp_accelMean.Y / (maxAccelError);
		} else {
			axisComplete++;
		}

		if (abs(tmp_accelMean.Z) <= maxAccelError) {
			tmp_accelOffset.Z -= tmp_accelMean.Z / (maxAccelError);
		} else {
			axisComplete++;
		}

		// check if complete
		if (axisComplete == 6) {
			std::cout<< "Gyro: ";
			std::cout << "X "<< tmp_gyroOffset.X << ", ";
			std::cout << "Y "<< tmp_gyroOffset.X << ", ";
			std::cout << "Z "<< tmp_gyroOffset.X << "\n";

			std::cout<< "Accel: ";
			std::cout << "X "<< tmp_accelOffset.X << ", ";
			std::cout << "Y "<< tmp_accelOffset.X << ", ";
			std::cout << "Z "<< tmp_accelOffset.X << "\n";

			break;
		}
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

	(this->acceleratorData).X = parseToShort((char) result[6], (char) result[7]);
	(this->acceleratorData).Y = parseToShort((char) result[8], (char) result[9]);
	(this->acceleratorData).Z = parseToShort((char) result[10], (char) result[11]);

	//std::cout << "Gyro X: " << (this->gyroData).X << " Y: " << (this->gyroData).Y << " Z: " << (this->gyroData).Z;
	//std::cout << "Acc X: " << (this->acceleratorData).X << " Y: "  << (this->acceleratorData).Y << " Z: " << (this->acceleratorData).Z;
	//std::cout << "\n";
}

// --------------------

void MPU6050::writeGyroOffset(axisData& t_gyroMean) {
	I2CDevice::writeRegister(MPU6050_GYRO_XOFFS_USR_H, (unsigned int) ((t_gyroMean.X >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_GYRO_XOFFS_USR_H, (unsigned int) (t_gyroMean.X & 0xff) );

	I2CDevice::writeRegister(MPU6050_GYRO_YOFFS_USR_H, (unsigned int) ((t_gyroMean.Y >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_GYRO_YOFFS_USR_H, (unsigned int) (t_gyroMean.Y & 0xff) );

	I2CDevice::writeRegister(MPU6050_GYRO_ZOFFS_USR_H, (unsigned int) ((t_gyroMean.Z >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_GYRO_ZOFFS_USR_H, (unsigned int) (t_gyroMean.Z & 0xff) );
}

// --------------------
void MPU6050::writeAccelOffset(axisData& t_accelMean) {
	I2CDevice::writeRegister(MPU6050_ACCEL_XOFFS_USR_H, (unsigned int) ((t_accelMean.X >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_ACCEL_XOFFS_USR_L, (unsigned int) (t_accelMean.X & 0xff) );

	I2CDevice::writeRegister(MPU6050_ACCEL_YOFFS_USR_H, (unsigned int) ((t_accelMean.Y >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_ACCEL_YOFFS_USR_L, (unsigned int) (t_accelMean.Y & 0xff) );

	I2CDevice::writeRegister(MPU6050_ACCEL_ZOFFS_USR_H, (unsigned int) ((t_accelMean.Z >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_ACCEL_ZOFFS_USR_L, (unsigned int) (t_accelMean.Z & 0xff) );
}


