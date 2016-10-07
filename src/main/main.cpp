#include <iostream>
#include <stdio.h>
#include <string>
#include "../GPIO/IGpio/IGpio.h"
#include "../FlightController/FlightController.h"
#include "../sensor/MPU6050/MPU6050.h"


int main () {
	IGpio IGpioInstance;

	FlightController flightCtrl (IGpioInstance);
	//flightCtrl.programMotors();
	MPU6050 mpu6050 (2, 250, IGpioInstance);
	mpu6050.wakeUp();

	mpu6050.calibrateAccelerometer();
	mpu6050.calibrateGyrometer();

	mpu6050.startLoop();

	return 0;
}