#ifndef I2C_H
#define I2C_H

/* Uncomment for running on raspberry pi
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
*/
#include <cstdint>

class I2CDevice
{
private:
	uint8_t DeviceAddr;

public:
	I2CDevice(uint8_t addr);
	
	void setAddress(uint8_t addr);

	void startRead(uint8_t* data, uint32_t length);

	void startWrite(uint8_t* data, uint32_t length);
};
#endif