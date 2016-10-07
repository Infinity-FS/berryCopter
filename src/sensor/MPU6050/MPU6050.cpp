#include "MPU6050.h"

// --------------------
// FlightController constructor
MPU6050::MPU6050 (int t_AccelerometerRange_G, int t_GyrometerRange, IGpio& t_IGpioInstance):
I2CDevice (0x68, 1, t_IGpioInstance),
Accelerometer(t_AccelerometerRange_G ,16, 1000, 10, (int) (0.0025 * ( (double) pow(2, 15) / (double) t_AccelerometerRange_G))), // 0.25 % of G max noise
Gyrometer(t_GyrometerRange , 2000, 1000, 10, (int) (0.01 * ((double) pow(2, 15) / (double) t_GyrometerRange))) //1 % 1 deg/sec max noise
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

	// Disables self tests & set Gyrorange
    int gyroConfig = 0b00000000; // default is +-250 deg/s

    int gyroRange = this->getGyrometerRange();
    if (gyroRange == 2000) {
        gyroConfig = 0b00011000;
    } else if(gyroRange == 1000) {
        gyroConfig = 0b00010000;
    } else if(gyroRange == 500) {
        gyroConfig = 0b00001000;
    }
	I2CDevice::writeRegister(MPU6050_GYRO_CONFIG, gyroConfig);

	// Disables self tests & set Accelrange
    int accelConfig = 0b00000000; // default is +- 2g

    int accelRange = this->getAccelerometerRange_G();
    if (accelRange == 16) {
        accelConfig = 0b00011000;
    } else if(accelRange == 8) {
        accelConfig = 0b00010000;
    } else if(accelRange == 4) {
        accelConfig = 0b00001000;
    }

	I2CDevice::writeRegister(MPU6050_ACCEL_CONFIG, accelConfig);
}

// --------------------

void MPU6050::startLoop() {

    long start_ns = 0; // NanoSec
    long end_ns = 0;
    struct timespec spec;

    int i = 0;
    for(;;){
        clock_gettime(CLOCK_REALTIME, &spec);
        start_ns = (long) (spec.tv_nsec);
        // < LOOP

		this->readAccelerometer();
        this->readGyrometer();


        i++;

        // > LOOP
        clock_gettime(CLOCK_REALTIME, &spec);
        end_ns = (long) (spec.tv_nsec);
        if(i%1000 == 0){
            std::cout<< "Accel: ";
            std::cout << "X "<< (this->accelerometerVector3).X << ", ";
            std::cout << "Y "<< (this->accelerometerVector3).Y << ", ";
            std::cout << "Z "<< (this->accelerometerVector3).Z << " >";

            std::cout<< "< Gyro: ";
            std::cout << "X "<< (this->gyrometerVector3).X << ", ";
            std::cout << "Y "<< (this->gyrometerVector3).Y << ", ";
            std::cout << "Z "<< (this->gyrometerVector3).Z << " >";

            std::cout << "loop Hz: " << ((1e9) / (end_ns - start_ns)) << "Hz \n";
        }
	}
}


// -------------------------------
// PRIVATE
// -------------------------------

// -------------------------
// ACCELEROMETER
// -------------------------

void MPU6050::readAccelerometer () {
	int sizeToRead = 6;
	unsigned int regAdrr [sizeToRead] = {
		MPU6050_ACCEL_XOUT_H, MPU6050_ACCEL_XOUT_L,
		MPU6050_ACCEL_YOUT_H, MPU6050_ACCEL_YOUT_L,
		MPU6050_ACCEL_ZOUT_H, MPU6050_ACCEL_ZOUT_L
	};

	unsigned int result [sizeToRead] = {};
	I2CDevice::readRegister(regAdrr, result, sizeToRead);

	(this->accelerometerVector3).X = ((((short) result[0] ) << 8) | (char) result[1]);
	(this->accelerometerVector3).Y = ((((short) result[2] ) << 8) | (char) result[3]);
	(this->accelerometerVector3).Z = ((((short) result[4] ) << 8) | (char) result[5]);
}

// --------------------
void MPU6050::readAccelerometerOffset(Vector3<short> &t_offset) {
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

    t_offset.X = ((((short) result[0] ) << 8) | (char) result[1]);
    t_offset.Y = ((((short) result[2] ) << 8) | (char) result[3]);
    t_offset.Z = ((((short) result[4] ) << 8) | (char) result[5]);
}


// --------------------
void MPU6050::writeAccelerometerOffset (Vector3<short> &t_offset){
	I2CDevice::writeRegister(MPU6050_ACCEL_XOFFS_USR_H, (unsigned int) ((t_offset.X >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_ACCEL_XOFFS_USR_L, (unsigned int) (t_offset.X & 0xff) );

	I2CDevice::writeRegister(MPU6050_ACCEL_YOFFS_USR_H, (unsigned int) ((t_offset.Y >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_ACCEL_YOFFS_USR_L, (unsigned int) (t_offset.Y & 0xff) );

	I2CDevice::writeRegister(MPU6050_ACCEL_ZOFFS_USR_H, (unsigned int) ((t_offset.Z >> 8) & 0xff) );
	I2CDevice::writeRegister(MPU6050_ACCEL_ZOFFS_USR_L, (unsigned int) (t_offset.Z & 0xff) );
}

// -------------------------
// GYROMETER
// -------------------------

void MPU6050::readGyrometer() {
    int sizeToRead = 6;
    unsigned int regAdrr [sizeToRead] = {
            MPU6050_GYRO_XOUT_H, MPU6050_GYRO_XOUT_L,
            MPU6050_GYRO_YOUT_H, MPU6050_GYRO_YOUT_L,
            MPU6050_GYRO_ZOUT_H, MPU6050_GYRO_ZOUT_L
    };

    unsigned int result [sizeToRead] = {};
    I2CDevice::readRegister(regAdrr, result, sizeToRead);

    (this->gyrometerVector3).X = ((((short) result[0] ) << 8) | (char) result[1]);
    (this->gyrometerVector3).Y = ((((short) result[2] ) << 8) | (char) result[3]);
    (this->gyrometerVector3).Z = ((((short) result[4] ) << 8) | (char) result[5]);
}

// --------------------
void MPU6050::readGyrometerOffset(Vector3<short> &t_offset) {
    int sizeToRead = 6;
    unsigned int regAdrr [sizeToRead] = {
            MPU6050_GYRO_XOFFS_USR_H, MPU6050_GYRO_XOFFS_USR_L,
            MPU6050_GYRO_YOFFS_USR_H, MPU6050_GYRO_YOFFS_USR_L,
            MPU6050_GYRO_ZOFFS_USR_H, MPU6050_GYRO_ZOFFS_USR_L,
    };

    unsigned int result [sizeToRead] = {};
    I2CDevice::readRegister(regAdrr, result, sizeToRead);
    std::cout<< "Gyro Offset ";
    std::cout<< "X:" << ((((short) result[0] ) << 8) | (char) result[1]);
    std::cout<< "Y:" << ((((short) result[2] ) << 8) | (char) result[3]);
    std::cout<< "Z:" << ((((short) result[4] ) << 8) | (char) result[5]);
    std::cout<< "\n";

    t_offset.X = ((((short) result[0] ) << 8) | (char) result[1]);
    t_offset.Y = ((((short) result[2] ) << 8) | (char) result[3]);
    t_offset.Z = ((((short) result[4] ) << 8) | (char) result[5]);
}


// --------------------
void MPU6050::writeGyrometerOffset (Vector3<short> &t_offset){
    I2CDevice::writeRegister(MPU6050_GYRO_XOFFS_USR_H, (unsigned int) ((t_offset.X >> 8) & 0xff) );
    I2CDevice::writeRegister(MPU6050_GYRO_XOFFS_USR_L, (unsigned int) (t_offset.X & 0xff) );

    I2CDevice::writeRegister(MPU6050_GYRO_YOFFS_USR_H, (unsigned int) ((t_offset.Y >> 8) & 0xff) );
    I2CDevice::writeRegister(MPU6050_GYRO_YOFFS_USR_L, (unsigned int) (t_offset.Y & 0xff) );

    I2CDevice::writeRegister(MPU6050_GYRO_ZOFFS_USR_H, (unsigned int) ((t_offset.Z >> 8) & 0xff) );
    I2CDevice::writeRegister(MPU6050_GYRO_ZOFFS_USR_L, (unsigned int) (t_offset.Z & 0xff) );
}


