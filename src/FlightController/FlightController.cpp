#include "FlightController.h"

// --------------------
// FlightController constructor
FlightController::FlightController(IGpioInstance& t_IGPIO):
	IGpioInstance(t_IGPIO)
{
}
// --------------------
// FlightController destructor
FlightController::~FlightController() {
}
// --------------------

void FlightController::programMotors() {
	int input = 0;

	std::cout<< "- Disconnect ESC Power" << "\n";
	std::cout<< "- Connect ESC with RasperryPi" << "\n";
	std::cout<< "PIN number: ";
	std::cin >> input;
	std::cout<< "\n- Connect ESC with RasperryPi" << "\n";

	BSController ctrl_1(input, 1000, 2000, IGpioInstance);

	std::cout<< "Set to MAX Speed (pulseWidth)" << "\n";
	ctrl_1.setSpeed(1.0);
	std::cout<< "Connect ESC battery:" << "\n";
	std::cout<< "Then enter any key:";
	std::cin >> input;
	std::cout<< "\n- Wait.. beep-beep" << "\n";
	std::cout<< "Then enter any key:";
	std::cin >> input;

	std::cout<< "\nSet to MIN Speed (pulseWidth)" << "\n";
	ctrl_1.setSpeed(0.0);
	std::cout<< "- Wait beep-beep-beep (for every battery Cell)" << "\n";
	std::cout<< "- Wait beep-beep-beep (for every battery Level)" << "\n";
	std::cout<< "- Wait beeeeeeep ..." << "\n";
	std::cout<< "Then enter any key:";
	std::cin >> input;

	std::cout<< "- Connect motor" << "\n";
	std::cout<< "\nThen enter any key:";
	std::cin >> input;
	for(;;) {
		double inputSpeed = 0.0;
		std::cout<< "\nNegative value: EXIT | Enter speed (0.0 - 1.0): ";
		std::cin >> inputSpeed;
		if (inputSpeed >= 0.0) {
			ctrl_1.setSpeed(double);
		} else {
			break;
		}
	}
}