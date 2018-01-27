#include "Drivers/Motors.h"
#include "OS/OSMemMap.h"
#include <iostream>
#include <math.h>
#include <wiringPiI2C.h>

#define	PCA9685_MODE1		0x0
#define	PCA9685_PRESCALE	0xFE

#define LED0_ON_L	0x6
#define LED0_ON_H	0x7
#define LED0_OFF_L	0x8
#define LED0_OFF_H	0x9

int32_t fd;

void setPWMFreq(float freq)
{
	freq *= 0.9;		// Adafruit corrects for an overshoot
	float prescaleval = 25000000;
	prescaleval /= 4096;
	prescaleval/= freq;
	prescaleval -= 1;
	uint8_t prescale = floor(prescaleval + 0.5);
	
	uint8_t oldmode = wiringPiI2CReadReg8(fd, PCA9685_MODE1);
	uint8_t newmode = (oldmode & 0x7F) | 0x10;	// sleep
	wiringPiI2CWriteReg8(fd, PCA9685_MODE1, newmode);
	wiringPiI2CWriteReg8(fd, PCA9685_PRESCALE, prescale);
	wiringPiI2CWriteReg8(fd, PCA9685_MODE1, oldmode);
	// delay(5);
	wiringPiI2CWriteReg8(fd, PCA9685_MODE1, oldmode | 0xA0);
}



void setPWM(uint8_t num, uint16_t on, uint16_t off)
{
	wiringPiI2CWriteReg8(fd,(LED0_ON_L + 4*num),	(on & 0x00FF));
	wiringPiI2CWriteReg8(fd, (LED0_ON_H + 4*num),	((on>>8) & 0xF));
	wiringPiI2CWriteReg8(fd, (LED0_OFF_L + 4*num),	(off & 0x00FF));
	wiringPiI2CWriteReg8(fd, (LED0_OFF_H + 4*num),	((off>>8) & 0xF));
}



void Motor_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err)
{
	std::cout << "Motor init task starting" << std::endl;
	struct Motors_MemMap* MotorMem_ptr = &((*RTOS_MEM).MotorDriverMem);
	(*MotorMem_ptr).i2caddr = 0x40;
	fd = wiringPiI2CSetup((*MotorMem_ptr).i2caddr);
	if (fd < 0)
	{
		*err = 1;
		return;
	}
	setPWMFreq(1000);
	std::cout << "Motor init task ending\n"  << std::endl;
}



void Motor_Update(struct RTOS_SHARED_MEM* RTOS_MEM,
							uint32_t RTOSTime)
{
	if (RTOSTime % 10 != 0)
		return;
		
	else
	{
		std::cout << "Motor update task starting" << std::endl;
		struct Motors_MemMap* MotorMem_ptr = &((*RTOS_MEM).MotorDriverMem);
		struct Controller_MemMap* ControllerMem_ptr = &((*RTOS_MEM).ControllerMem);
		
		for (int i = 0; i < 5; i++)
		{
			uint16_t on = (*ControllerMem_ptr).Motor_Speeds[i];
			uint16_t off = 4096 - (*ControllerMem_ptr).Motor_Speeds[i];
			std::cout << "\tMotor # "  << i;
			std::cout << "\tOn time: " << on;
			std::cout << "\tOff time:" << off << "\n" << std::endl;
			setPWM(i, on, off);
		}
			
		std::cout << "Motor update task ending\n"  << std::endl;
	}
}
