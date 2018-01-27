#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <cstdint>

struct Controller_MemMap
{
	uint16_t		Motor0_Speed;
};

void Controller_Update(struct RTOS_SHARED_MEM* RTOS_MEM,
											 		   uint32_t RTOSTime);



#endif