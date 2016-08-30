#include "FlightController.h"

// --------------------
// FlightController constructor
FlightController::FlightController(IGpio& t_IGPIO):
	IGpioInstance(t_IGPIO)
{
	std::cout<<"FlightController init";
}
// --------------------
// FlightController destructor
FlightController::~FlightController() {
	
}
// --------------------

void FlightController::programMotors() {
	int input = 0;
	std::cout<< "PIN number: ";
	std::cin >> input;
	BSController ctrl_1(input, 1000, 2000, IGpioInstance);
	for(;;) {
		double inputSpeed = 0.0;
		std::cout<< "\nEnter speed (0.0 - 1.0): ";
		std::cin >> inputSpeed;
		if (inputSpeed >= 0.0) {
			ctrl_1.setSpeed(inputSpeed);
		} else {
			break;
		}
	}
}