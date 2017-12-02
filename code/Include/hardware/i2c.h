#ifndef I2C_H
#define I2C_H

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>


class I2CDevice
{
private:
	unsigned char DeviceAddress;

public:
	I2CDevice(unsigned char addr);
	
	~I2CDevice(void);

	void setAddress(unsigned char addr);

	void startRead(char* data, int length);

	void startWrite(char* data, int length);
};
#endif