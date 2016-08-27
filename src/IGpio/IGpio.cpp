#include <pigpio.h>
#include "IGpio.h"

IGpio::IGpio() {
	if (gpioInitialise() < 0) {
   		// pigpio initialisation failed.
		std::cout << "FAILED";
	} else {
   		// pigpio initialised okay.
		std::cout << "OK";
	}
}

