#ifndef __IGPIO_H_INCLUDED__
#define __IGPIO_H_INCLUDED__

#include <pigpio.h>
#include <iostream>

class IGpio {
 public:
	IGpio();
	~IGpio();

	int setMode(unsigned int t_gpioNb, unsigned int t_mode);
	int getMode(unsigned int t_gpioNb);

	// PWM
	int setPWM (unsigned int t_gpioNb, unsigned int t_open);
	int getPWM (unsigned int t_gpioNb);

	int setPWMFrequency (unsigned int t_gpioNb, unsigned int t_freq);
	int getPWMFrequency (unsigned int t_gpioNb);

	int setPWMRange (unsigned int t_gpioNb, unsigned int t_range);
	int getPWMRange (unsigned int t_gpioNb);

	// I2C
	int registerI2CDevice (unsigned int t_busInterface, unsigned int t_addr); // returns Handle_ID
	int unregisterI2CDevice (unsigned int t_deviceHandleID);

	// S Addr Wr [A] i2cReg [A] S Addr Rd [A] [buf0] A [buf1] A ... A [bufn] NA P
	int readI2CRegister (unsigned int t_deviceHandleID, unsigned int t_RegAddr, char* t_buffer, unsigned int count);

	// S Addr Wr [A] i2cReg [A] buf0 [A] buf1 [A] ... [A] bufn [A] P
	int writeI2CRegister (unsigned int t_deviceHandleID, unsigned int t_RegAddr, char* t_val, unsigned int count);
};

/*
Pin Types 
	Number:  -- -- -- 14 15 18 -- 23 24 -- 25 08 07 -- -- 12 -- 16 20 21
	PNumber: 02 04 06 08 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40
	Type:     5  5  G  X  X  X  G  X  X  G  X  X  X ID  G  X  G  X  X  X

	Number:  -- 02 03 04 -- 17 27 22 -- 10 09 11 -- -- 05 06 13 19 26 --
	PNumber: 01 03 05 07 09 11 13 15 17 19 21 23 25 27 29 31 33 35 37 39
	Type:     3  X  X  X  G  X  X  X  3  X  X  X  G ID  X  X  X  X  X  G

	I2C.1: 
		- SDA:  03 PNumber (GPIO02)
		- SCL:  05 PNumber (GPIO03)
	(I2C.0: 
		- SDA:  27 PNumber
		- SCL:  28 PNumber) --> Not supported

Pin modes:
	PI_INPUT 0; PI_OUTPUT 1;

I2C:
	S      (1 bit) : Start bit
	P      (1 bit) : Stop bit
	Rd/Wr  (1 bit) : Read/Write bit. Rd equals 1, Wr equals 0.
	A, NA  (1 bit) : Accept and not accept bit.

	Addr   (7 bits): I2C 7 bit address.
	i2cReg (8 bits): Command byte, a byte which often selects a register.
	Data   (8 bits): A data byte.
	Count  (8 bits): A byte defining the length of a block operation.

[..]: Data sent by the device.

*/

#endif // __IGPIO_H_INCLUDED__
