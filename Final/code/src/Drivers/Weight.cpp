#include "Drivers/Weight.h"
#include "OS/OSMemMap.h"
#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>

// #define ENABLE_DEBUG_CONSOLE


int32_t sensor;


void Weight_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err)
{
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Weight init task starting" << std::endl;
	#endif
	struct Weight_MemMap* WeightMem_ptr = &((*RTOS_MEM).WeightDriverMem);

	(*WeightMem_ptr).i2caddr = 0x00;	// Replace with the actual address of the ADC
	wiringPiSetupSys();
	sensor = wiringPiI2CSetup((*WeightMem_ptr).i2caddr);
	if (sensor < 0)
	{
		*err = 1;
		return;
	}
	
	// any device setup goes here

	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Weight init task ending\n"  << std::endl;
	#endif
}
	

void Weight_Update(struct RTOS_SHARED_MEM* RTOS_MEM,
											  uint32_t RTOSTime)
{
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Weight update task starting" << std::endl;
	#endif


	//task update code goes here
	struct Weight_MemMap* WeightMem_ptr = &((*RTOS_MEM).WeightDriverMem);


	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Weight update task ending" << std::endl;
	#endif
}
