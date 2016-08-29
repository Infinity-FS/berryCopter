#include <iostream>
#include <string>
#include "../GPIO/IGpio/IGpio.h"
#include "../BSController/BSController.h"

int main () {
	IGpio gpioInterface;
	BSController ctrl_1(14, 1000, 2000, gpioInterface);

	cout << ctrl_1.getSpeed() << "\n";

	ctrl_1.setSpeed(0.5f)

	cout << ctrl_1.getSpeed() << "\n";
	return 0;
}