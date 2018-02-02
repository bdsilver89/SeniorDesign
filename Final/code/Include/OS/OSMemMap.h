#ifndef OSMEMMAP_H
#define OSMEMMAP_H

#include "TestTask/task_a.h"
#include "TestTask/task_b.h"
#include "Drivers/Motors.h"
#include "Drivers/Weight.h"
#include "Control/Controller.h"


// struct definition for shared memory in RTOS environment
struct RTOS_SHARED_MEM
{
	struct TaskA_MemMap				A_Mem;
	struct TaskB_MemMap				B_Mem;
	struct Motors_MemMap			MotorDriverMem;
	struct Weight_MemMap			WeightDriverMem;
	struct Controller_MemMap		ControllerMem;
};
#define RTOS_SHARED_MEM_SIZE	sizeof(RTOS_SHARED_MEM)

#endif
