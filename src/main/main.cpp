#include <iostream>
#include <string>

int main()
{
	if (gpioInitialise() < 0){
 		// pigpio initialisation failed.
 		std::cout << "initialised FAILED";
	} else {
   		// pigpio initialised okay.
		std::cout << "initialised OK";
	}
}
