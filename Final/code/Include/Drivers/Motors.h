#ifndef MOTORS_H
#define MOTORS_H

#include <cstdint>

struct Motors_MemMap
{
	uint8_t		i2caddr;
};
#define MOTORS_MEMMAP_SIZE	sizeof(Motors_MemMap)


void Motor_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err);
											  
void Motor_Update(struct RTOS_SHARED_MEM* RTOS_MEM, uint32_t RTOSTime);


#endif
