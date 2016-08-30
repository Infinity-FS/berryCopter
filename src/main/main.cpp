#include <iostream>
#include <string>
#include "../GPIO/IGpio/IGpio.h"
#include "../FlightController/FlightController.h"

int main () {
	IGpio IGpioInstance;

	FlightController flightCtrl (IGpioInstance);
	flightCtrl.programMotors();

	return 0;
}