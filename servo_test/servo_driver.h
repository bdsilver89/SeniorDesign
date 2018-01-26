#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H

#include <cstdint>


class ServoDriver
{
private:
	
	/**
	 * [_i2caddr Private I2C address]
	 */
	uint8_t _i2caddr;
	
	/**
	 * [readByte description]
	 * @param  addr [description]
	 * @return      [description]
	 */
	uint8_t readByte(uint8_t addr);

	/**
	 * [writeByte description]
	 * @param addr [description]
	 * @param msg  [description]
	 */
	void writeByte(uint8_t addr, uint8_t msg);


public:

	/**
	 * 
	 */
	ServoDriver(uint8_t addr = 0x40);

	/**
	 * [begin description]
	 */
	void begin(void);

	/**
	 * [reset description]
	 */
	void reset(void);

	/**
	 * [setPWMFreq description]
	 * @param freq [description]
	 */
	void setPWMFreq(float freq);
	
	/**
	 * [setPWM description]
	 * @param num [description]
	 * @param on  [description]
	 * @param off [description]
	 */
	void setPWM(uint8_t num, uint16_t on, uint16_t off);

	/**
	 * [setPin description]
	 * @param num    [description]
	 * @param val    [description]
	 * @param invert [description]
	 */
	void setPin(uint8_t num, uint16_t val, bool invert=false);
};

#endif