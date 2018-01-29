#include "Drivers/Motors.h"
#include "OS/OSMemMap.h"
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define	PCA9685_MODE1		0x0
#define PCA9685_MODE2		0x01
#define	PCA9685_PRESCALE	0xFE

#define LED0_ON_L	0x6
#define LED0_ON_H	0x7
#define LED0_OFF_L	0x8
#define LED0_OFF_H	0x9

#define ALL_LED_ON_L	0xFA
#define ALL_LED_ON_H	0xFB
#define ALL_LED_OFF_L	0xFC
#define ALL_LED_OFF_H	0xFD

// #define ENABLE_DEBUG_CONSOLE

int32_t servoBoard;



void setPWMFreq(float freq)
{
	// freq *= 0.9;		// Adafruit corrects for an overshoot
	float prescaleval = 25000000;
	prescaleval /= 4096;
	prescaleval/= freq;
	prescaleval -= 1;
	uint8_t prescale = floor(prescaleval + 0.5);
	
	uint8_t oldmode = wiringPiI2CReadReg8(servoBoard, PCA9685_MODE1);
	uint8_t newmode = (oldmode & 0x7F) | 0x10;	// sleep
	wiringPiI2CWriteReg8(servoBoard, PCA9685_MODE1, newmode);
	wiringPiI2CWriteReg8(servoBoard, PCA9685_PRESCALE, prescale);
	wiringPiI2CWriteReg8(servoBoard, PCA9685_MODE1, oldmode);
	usleep(5000);
	wiringPiI2CWriteReg8(servoBoard, PCA9685_MODE1, oldmode | 0x80);
}



void setPWM(uint8_t num, uint16_t on, uint16_t off)
{
	wiringPiI2CWriteReg8(servoBoard, (LED0_ON_L + 4*num),	(on & 0x00FF));
	wiringPiI2CWriteReg8(servoBoard, (LED0_ON_H + 4*num),	(on>>8));
	wiringPiI2CWriteReg8(servoBoard, (LED0_OFF_L + 4*num),	(off & 0x00FF));
	wiringPiI2CWriteReg8(servoBoard, (LED0_OFF_H + 4*num),	(off>>8));
}



void setAllPWM(uint16_t on, uint16_t off)
{
	wiringPiI2CWriteReg8(servoBoard, (ALL_LED_ON_L),	(on & 0x00FF));
	wiringPiI2CWriteReg8(servoBoard, (ALL_LED_ON_H),	(on>>8));
	wiringPiI2CWriteReg8(servoBoard, (ALL_LED_OFF_L),	(off & 0x00FF));
	wiringPiI2CWriteReg8(servoBoard, (ALL_LED_OFF_H),	(off>>8));
}



void Motor_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err)
{
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Motor init task starting" << std::endl;
	#endif
	struct Motors_MemMap* MotorMem_ptr = &((*RTOS_MEM).MotorDriverMem);
	(*MotorMem_ptr).i2caddr = 0x40;
	wiringPiSetupSys();
	servoBoard = wiringPiI2CSetup((*MotorMem_ptr).i2caddr);
	if (servoBoard < 0)
	{
		*err = 1;
		return;
	}
	wiringPiI2CWriteReg8(servoBoard, PCA9685_MODE2, 0x04);	// OUTDRV
	wiringPiI2CWriteReg8(servoBoard, PCA9685_MODE1, 0x01);	// ALLCALL
	usleep(5000);
	uint8_t mode1 = wiringPiI2CReadReg8(servoBoard, PCA9685_MODE1);
	wiringPiI2CWriteReg8(servoBoard, PCA9685_MODE1, mode1 & 0x7F);	// wake up
	wiringPiI2CWriteReg8(servoBoard, PCA9685_MODE1, mode1);
	usleep(5000);

	setPWMFreq(60.0f);
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Motor init task ending\n"  << std::endl;
	#endif
}



void Motor_Update(struct RTOS_SHARED_MEM* RTOS_MEM,
							uint32_t RTOSTime)
{
	/*
	if (RTOSTime % 10 != 0)
		return;
		
	else
	{
	*/
		#ifdef ENABLE_DEBUG_CONSOLE
			std::cout << "Motor update task starting" << std::endl;
		#endif
		struct Motors_MemMap* MotorMem_ptr = &((*RTOS_MEM).MotorDriverMem);
		struct Controller_MemMap* ControllerMem_ptr = &((*RTOS_MEM).ControllerMem);
		
		for (int i = 0; i < 5; i++)
		{
			if ((*ControllerMem_ptr).Motor_Speeds[i] != 0)
			{
				setPWM(i, 0, (*ControllerMem_ptr).Motor_Speeds[i]);
			}
		}

		#ifdef ENABLE_DEBUG_CONSOLE		
			std::cout << "Motor update task ending\n"  << std::endl;
		#endif
	//}
}
