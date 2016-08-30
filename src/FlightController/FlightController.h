#ifndef __FLIGHT_CONTROLLER_H_INCLUDED__
#define __FLIGHT_CONTROLLER_H_INCLUDED__

#include <iostream>
#include "../BSController/BSController.h"
#include "../GPIO/IGpio/IGpio.h"

// Brushless Speed Controller
class FlightController {
 public:
	FlightController(IGpio& t_IGpioInstance);
	~FlightController();

	void programMotors();
 private:
 	IGpio& IGpioInstance;
};

#endif // __FLIGHT_CONTROLLER_H_INCLUDED__