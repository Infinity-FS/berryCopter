#include <iostream>
#include <string>
#include "../IGpio/IGpio.h"
#include "../GpioPin/GpioPin.h"

int main () {
	IGpio gpioInterface;
	GpioPin pin(17, 1, gpioInterface);
	pin.print();

	pin.setPWM(1.0f);
	pin.print();

	pin.setPWM(0.0f);
	pin.print();

	pin.setPWM(0.5f);
	pin.print();

	pin.setPWM(100u);
	pin.print();

	pin.setPWM(1000, 50);
	pin.print();

	return 0;
}