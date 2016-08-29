#include <iostream>
#include <string>
#include "../IGpio/IGpio.h"
#include "../GpioPin/GpioPin.h"

int main () {
	IGpio gpioInterface();
	GpioPin pin(17, 1, gpioInterface);
}