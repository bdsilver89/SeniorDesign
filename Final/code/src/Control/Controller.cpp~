#include "Control/Controller.h"
#include "OS/OSMemMap.h"
#include <iostream>

void Controller_Update(struct RTOS_SHARED_MEM* RTOS_MEM,
											 		   uint32_t RTOSTime)
{
	if (RTOSTime % 10 != 0)
		return;
		
	else
	{
		std::cout << "Controller update starting" << std::endl;
		struct Controller_MemMap* ControllerMem_ptr = &((*RTOS_MEM).ControllerMem);
		(*ControllerMem_ptr).Motor0_Speed = 12;
		
		std::cout << "Controller update ending\n"  << std::endl;
	}
}