#include "Control/Controller.h"
#include "OS/OSMemMap.h"
#include <iostream>

// #define ENABLE_DEBUG_CONSOLE

uint16_t motor_val = 375;


void Controller_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err)
{
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Controller init task starting" << std::endl;
	#endif
	struct Controller_MemMap* ControllerMem_ptr = &((*RTOS_MEM).ControllerMem);
	
	for (int i = 0; i < NUM_MOTORS; i++)
	{
		(*ControllerMem_ptr).Motor_Speeds[i] = 0;
		(*ControllerMem_ptr).Motor_Enable[i] = 0;
	}
	
	*err = 0;
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Controller init task ending\n"  << std::endl;
	#endif
}



void Controller_Update(struct RTOS_SHARED_MEM* RTOS_MEM,
											 		   uint32_t RTOSTime)
{
    if (RTOSTime % 5 != 0)
		return;

	else
	{
		#ifdef ENABLE_DEBUG_CONSOLE
			std::cout << "Controller update starting" << std::endl;
		#endif
		struct Controller_MemMap* ControllerMem_ptr = &((*RTOS_MEM).ControllerMem);	

	/*
		if (motor_val < 400)
		{
			motor_val++;
			(*ControllerMem_ptr).Motor_Enable[0] = 1;
		}
		
		else
			(*ControllerMem_ptr).Motor_Enable[0] = 0;
	
		std::cout << motor_val << std::endl;
	*/
		(*ControllerMem_ptr).Motor_Speeds[0] = 390;
		
		
		#ifdef ENABLE_DEBUG_CONSOLE
			std::cout << "Controller update ending\n"  << std::endl;
		#endif
	}
}
