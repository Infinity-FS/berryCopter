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
		trial++;

		std::cout<<"... ";

		this->writeGyroOffset(tmp_gyroOffset);
		this->writeAccelOffset(tmp_accelOffset);

		axisData_int32 tmp_gyroMean, tmp_accelMean;

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
		tmp_gyroMean.X = tmp_gyroMean.X / (int) iterations;
		tmp_gyroMean.Y = tmp_gyroMean.Y / (int) iterations;
		tmp_gyroMean.Z = tmp_gyroMean.Z / (int) iterations;

		tmp_accelMean.X = tmp_accelMean.X / (int) iterations;
		tmp_accelMean.Y = tmp_accelMean.Y / (int) iterations;
		tmp_accelMean.Z = tmp_accelMean.Z / (int) iterations;

		// check for every axis, if calibration is complete
		int axisComplete = 0;

		// gyro axis X, Y, Z
		if (abs(tmp_gyroMean.X) > maxGyroError) {
			tmp_gyroOffset.X += tmp_gyroMean.X ;
			std::cout << "| new gyro.X " << tmp_gyroOffset.X << " (" << tmp_gyroMean.X << ") |";
		} else {
			std::cout << "| gyro.X OK at " << tmp_gyroOffset.X << " (" << tmp_gyroMean.X << ") |";
			axisComplete++;
		}

		if (abs(tmp_gyroMean.Y) > maxGyroError) {
			tmp_gyroOffset.Y += tmp_gyroMean.Y ;
			std::cout << "| new gyro.Y " << tmp_gyroOffset.Y << " (" << tmp_gyroMean.Y << ") |";
		} else {
			std::cout << "| gyro.Y OK at " << tmp_gyroOffset.Y << " (" << tmp_gyroMean.Y << ") |";
			axisComplete++;
		}

		if (abs(tmp_gyroMean.Z) > maxGyroError) {
			tmp_gyroOffset.Z += tmp_gyroMean.Z ;
			std::cout << "| new gyro.Z " << tmp_gyroOffset.Z << " (" << tmp_gyroMean.Z << ") |";
		} else {
			std::cout << "| gyro.Z OK at " << tmp_gyroOffset.Z << " (" << tmp_gyroMean.Z << ") |";
			axisComplete++;
		}

		// accel axis X, Y, Z
		if (abs(tmp_accelMean.X) > maxAccelError) {
			tmp_accelOffset.X += tmp_accelMean.X ;
			std::cout << "| new accel.X " << tmp_accelOffset.X << " (" << tmp_accelMean.X << ") |";
		} else {
			std::cout << "| accel.X OK at " << tmp_accelOffset.X << " (" << tmp_accelMean.X << ") |";
			axisComplete++;
		}

		if (abs(tmp_accelMean.Y) > maxAccelError) {
			tmp_accelOffset.Y += tmp_accelMean.Y;
			std::cout << "| new accel.Y " << tmp_accelOffset.Y << " (" << tmp_accelMean.Y << ") |";
		} else {
			std::cout << "| accel.Y OK at " << tmp_accelOffset.Y << " (" << tmp_accelMean.Y << ") |";
			axisComplete++;
		}

		if (abs(tmp_accelMean.Z) > maxAccelError) {
			tmp_accelOffset.Z += tmp_accelMean.Z;
			std::cout << "| new accel.Z " << tmp_accelOffset.Z << " (" << tmp_accelMean.Z << ") |";
		} else {
			std::cout << "| accel.Z OK at " << tmp_accelOffset.Z << " (" << tmp_accelMean.Z << ") |";
			axisComplete++;
		}

		std::cout<< "\n";

		// check if complete
		if (axisComplete == 6) {
			std::cout<< "Gyro: ";
			std::cout << "X "<< tmp_gyroOffset.X << ", ";
			std::cout << "Y "<< tmp_gyroOffset.Y << ", ";
			std::cout << "Z "<< tmp_gyroOffset.Z << "\n";

			std::cout<< "Accel: ";
			std::cout << "X "<< tmp_accelOffset.X << ", ";
			std::cout << "Y "<< tmp_accelOffset.Y << ", ";
			std::cout << "Z "<< tmp_accelOffset.Z << "\n";

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

	/*std::cout << "Gyro X: " << (this->gyroData).X << " Y: " << (this->gyroData).Y << " Z: " << (this->gyroData).Z;
	std::cout << " Acc X: " << (this->acceleratorData).X << " Y: "  << (this->acceleratorData).Y << " Z: " << (this->acceleratorData).Z;
	std::cout << "\n";*/
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


