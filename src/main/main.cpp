#include <iostream>
#include <string>
#include "../IGpio/IGpio.h"
#include "../GpioPin/GpioPin.h"

int main () {
	IGpio gpioInterface;
	GpioPin pin(17, 1, gpioInterface);
	std::cout << " pwm " << pin.getPWM() << ", range " << pin.getPWMrange() << ", percentage " << pin.getPWMpercentage() << " freq " << pin.getPWMfrequency() << "\n";
	
	pin.setPWM(1.0);
	std::cout << " pwm " << pin.getPWM() << ", range " << pin.getPWMrange() << ", percentage " << pin.getPWMpercentage() << " freq " << pin.getPWMfrequency() << "\n";

	pin.setPWM(0.0);
	std::cout << " pwm " << pin.getPWM() << ", range " << pin.getPWMrange() << ", percentage " << pin.getPWMpercentage() << " freq " << pin.getPWMfrequency() << "\n";

	pin.setPWM(0.5);
	std::cout << " pwm " << pin.getPWM() << ", range " << pin.getPWMrange() << ", percentage " << pin.getPWMpercentage() << " freq " << pin.getPWMfrequency() << "\n";

	pin.setPWM(100);
	std::cout << " pwm " << pin.getPWM() << ", range " << pin.getPWMrange() << ", percentage " << pin.getPWMpercentage() << " freq " << pin.getPWMfrequency() << "\n";

	pin.setPWM(1000, 50);
	std::cout << " pwm " << pin.getPWM() << ", range " << pin.getPWMrange() << ", percentage " << pin.getPWMpercentage() << " freq " << pin.getPWMfrequency() << "\n";

	return 0;
}