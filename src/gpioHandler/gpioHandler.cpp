#include <pigpio.h>

class gpioHandler {
	gpioHandler() {
		if (gpioInitialise() < 0) {
   			// pigpio initialisation failed.
			std::cout << "FAILED";
		} else {
   			// pigpio initialised okay.
			 std::cout << "OK";
		}
	}
}
