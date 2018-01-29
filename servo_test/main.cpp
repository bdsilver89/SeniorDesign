#include <iostream>
#include <cstdint>
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


int32_t servoBoard;


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


int main(int argc, char const *argv[])
{
	std::cout << "Program initializing..." << std::endl;	
	
	std::cout << "Motor init task starting" << std::endl;
	wiringPiSetupSys();
	servoBoard = wiringPiI2CSetup(0x40);
	wiringPiI2CWriteReg8(servoBoard, PCA9685_MODE2, 0x04);	// OUTDRV
	wiringPiI2CWriteReg8(servoBoard, PCA9685_MODE1, 0x01);	// ALLCALL
	usleep(5000);
	uint8_t mode1 = wiringPiI2CReadReg8(servoBoard, PCA9685_MODE1);

	wiringPiI2CWriteReg8(servoBoard, PCA9685_MODE1, mode1 & 0x7F);	// wake up
	wiringPiI2CWriteReg8(servoBoard, PCA9685_MODE1, mode1);	// OUTDRV
	usleep(5000);

	std::cout << "Motor init task ending" << std::endl;


	float prescaleval = 25000000;
	prescaleval /= 4096;
	prescaleval/= 60;
	prescaleval -= 1;
	uint8_t prescale = floor(prescaleval + 0.5);
	
	uint8_t oldmode = wiringPiI2CReadReg8(servoBoard, PCA9685_MODE1);
	uint8_t newmode = (oldmode & 0x7F) | 0x10;	// sleep
	wiringPiI2CWriteReg8(servoBoard, PCA9685_MODE1, newmode);
	wiringPiI2CWriteReg8(servoBoard, PCA9685_PRESCALE, prescale);
	wiringPiI2CWriteReg8(servoBoard, PCA9685_MODE1, oldmode);
	usleep(5000);
	wiringPiI2CWriteReg8(servoBoard, PCA9685_MODE1, oldmode | 0x80);
	
	std::cout << "Done initializing" << std::endl;

	for (int i = 0; i < 3; i++)
	{
		// setPWM(0, 150, 3946);
		setPWM(0, 0, 150);
		usleep(1000000);
		// setPWM(0, 500, 3496);
		setPWM(0, 0, 600);
		usleep(1000000);		
	}
	setAllPWM(0, 0);

	std::cout << "Program closing" << std::endl;
	return 0;
}




