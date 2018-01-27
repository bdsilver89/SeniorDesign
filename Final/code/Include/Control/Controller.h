#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <cstdint>

#define NUM_MOTORS 5

struct Controller_MemMap
{
	uint16_t		Motor_Speeds[NUM_MOTORS];
};

void Controller_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err);

void Controller_Update(struct RTOS_SHARED_MEM* RTOS_MEM, uint32_t RTOSTime);



#endif
