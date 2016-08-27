#ifndef __IGPIO_H_INCLUDED__
#define __IGPIO_H_INCLUDED__

#include <pigpio.h>

class IGpio {
 public:
	IGpio() {
		if (gpioInitialise() < 0) {
   			// pigpio initialisation failed.
			std::cout << "FAILED";
		} else {
   			// pigpio initialised okay.
			 std::cout << "OK";
		}
	}

 private:
};

#endif // __IGPIO_H_INCLUDED__