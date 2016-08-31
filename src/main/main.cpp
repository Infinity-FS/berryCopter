#include <iostream>
#include <string>
#include "../GPIO/IGpio/IGpio.h"
#include "../FlightController/FlightController.h"
#include "../GPIO/I2C/I2CDevice.h"


int main () {
	IGpio IGpioInstance;

	FlightController flightCtrl (IGpioInstance);
	//flightCtrl.programMotors();
	I2CDevice MPU6050 (0x68, 1, IGpioInstance);

	char* buffer;

	std::cout << "READ FROM MPU6050: " << MPU6050.readRegister(0x75, 8, buffer) << "\n";
	 for (const char* p = buffer; *p; ++p)
    {
        printf("%02x", *p);
    }
    printf("\n");
	return 0;
}