#include <iostream>
#include <stdio.h>
#include <string>
#include "../GPIO/IGpio/IGpio.h"
#include "../FlightController/FlightController.h"
#include "../GPIO/I2C/I2CDevice.h"


int main () {
	IGpio IGpioInstance;

	FlightController flightCtrl (IGpioInstance);
	//flightCtrl.programMotors();
	I2CDevice MPU6050 (0x68, 1, IGpioInstance);

	char* buffer = new char[8];
	MPU6050.readRegister(0x75, buffer);
	 for (const char* p = buffer; *p; ++p)
    {
        printf("%02x", *p);
    }
    printf("\n");
	return 0;
}