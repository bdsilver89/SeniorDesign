#include "servo_driver.h"


ServoDriver::ServoDriver(uint8_t addr)
{
	_i2caddr = addr;
}

void ServoDriver::begin(void) {}

void ServoDriver::reset(void) {}

void ServoDriver::setPWMFreq(float freq) {}

void ServoDriver::setPWM(uint8_t num, uint16_t on, uint16_t off) {}

void ServoDriver::setPin(uint8_t num, uint16_t val, bool invert) {}


/**************************************************************************/

uint8_t ServoDriver::readByte(uint8_t addr)
{
	return 0x00;
}

void ServoDriver::writeByte(uint8_t addr, uint8_t msg) {}



