#include "Control/Controller.h"
#include "OS/OSMemMap.h"
#include <iostream>

// #define ENABLE_DEBUG_CONSOLE

uint16_t motor_val = 370;


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



void Controller_Update(struct RTOS_SHARED_MEM* RTOS_MEM, uint32_t RTOSTime)
{
	struct UI_MemMap* UIMem_ptr = &((*RTOS_MEM).UIMem);
	struct Controller_MemMap* ControllerMem_ptr = &((*RTOS_MEM).ControllerMem);	

	if((*UIMem_ptr).startControlFlag == 1)
	{
		#ifdef ENABLE_DEBUG_CONSOLE
			std::cout << "Controller update starting" << std::endl;
		#endif
		
		/*if (motor_val < 410)
		{
			motor_val++;
			(*ControllerMem_ptr).Motor_Enable[0] = 1;
			(*ControllerMem_ptr).Motor_Enable[1] = 1;
		}
	
		(*ControllerMem_ptr).Motor_Speeds[0] = motor_val;
		(*ControllerMem_ptr).Motor_Speeds[1] = 780 - motor_val;
		*/

		(*ControllerMem_ptr).Motor_Enable[0] = 1;
		(*ControllerMem_ptr).Motor_Enable[1] = 1;
		
		(*ControllerMem_ptr).Motor_Speeds[0] = 370;
		(*ControllerMem_ptr).Motor_Speeds[1] = 410;	
		
		
		// PID Control Loop
		/*
		struct PID_Controller *PID_ptr;
		for (int i = 0; i < NUM_MOTORS; i++)
		{
			Current_Positions[i] = read_current_position(i);	// replace with info from GUI
			Error[i] = Target_Positions[i] - Current_Positions[i];
			Integral[i] += Error[i];
			Derivative[i] = Error[i] - Last_Errors[i];
			
			PID_val[i] = (Kp[i] * Error[i]) + (Ki[i] * Integral[i]) + (Kd[i] * Derivative[i]);
		}
		*/	
		
		#ifdef ENABLE_DEBUG_CONSOLE
			std::cout << "Controller update ending\n"  << std::endl;
		#endif
	}
	
	else
	{
		(*ControllerMem_ptr).Motor_Enable[0] = 0;
		(*ControllerMem_ptr).Motor_Enable[1] = 0;
	}
}
