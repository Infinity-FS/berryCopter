#include <iostream>
#include <stdio.h>
#include <string>
#include "../GPIO/IGpio/IGpio.h"
#include "../FlightController/FlightController.h"
#include "../Sensors/MPU6050/MPU6050.cpp"


int main () {
	IGpio IGpioInstance;

	FlightController flightCtrl (IGpioInstance);
	//flightCtrl.programMotors();
	MPU6050 mpu6050 (IGpioInstance);
	mpu6050.reset();
	mpu6050.startLoop();
	return 0;
}