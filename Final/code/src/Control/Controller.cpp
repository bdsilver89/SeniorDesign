#include "Control/Controller.h"
#include "OS/OSMemMap.h"
#include <iostream>

void Controller_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err)
{
	std::cout << "Controller init task starting" << std::endl;
	struct Controller_MemMap* ControllerMem_ptr = &((*RTOS_MEM).ControllerMem);
	for (int i = 0; i < NUM_MOTORS; i++)
	{
		(*ControllerMem_ptr).Motor_Speeds[0] = 0;
		(*ControllerMem_ptr).Motor_Speeds[1] = 0;
		(*ControllerMem_ptr).Motor_Speeds[2] = 0;
		(*ControllerMem_ptr).Motor_Speeds[3] = 0;
		(*ControllerMem_ptr).Motor_Speeds[4] = 0;	
	}
	
	*err = 0;
	std::cout << "Controller init task ending\n"  << std::endl;
}



void Controller_Update(struct RTOS_SHARED_MEM* RTOS_MEM,
											 		   uint32_t RTOSTime)
{
    if (RTOSTime % 10 != 0)
		return;

	else
	{
		std::cout << "Controller update starting" << std::endl;
		struct Controller_MemMap* ControllerMem_ptr = &((*RTOS_MEM).ControllerMem);
		(*ControllerMem_ptr).Motor_Speeds[0]++;

		std::cout << "Controller update ending\n"  << std::endl;
	}
}
