#include <iostream>
#include <string>
#include "../IGpio/IGpio.h"
#include "../GpioPin/GpioPin.h"

int main () {
	IGpio gpioInterface;
	GpioPin pin(17, 1, gpioInterface);
	pin.print();

	pin.setPWM(800u, 100u, 100u);
	pin.print();

	pin.setPWM(800u, 100u, 0u);
	pin.print();

	pin.setPWM(800u, 100u, 50u);
	pin.print();

	pin.setPWM(800u, pin.getPWMrange(), 60);
	pin.print();

	pin.setPWM(1000, 50);
	pin.print();

	return 0;
}