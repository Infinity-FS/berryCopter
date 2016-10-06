#include <iostream>
#include <stdio.h>
#include <string>
#include "../GPIO/IGpio/IGpio.h"
#include "../FlightController/FlightController.h"


int main () {
	IGpio IGpioInstance;

	FlightController flightCtrl (IGpioInstance);
	//flightCtrl.programMotors();
	/*MPU6050 mpu6050 (IGpioInstance);
	mpu6050.wakeUp();
	mpu6050.calibrate();
	mpu6050.startLoop();*/

	return 0;
}