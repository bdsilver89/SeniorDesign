#ifndef MOTORS_H
#define MOTORS_H

#include <cstdint>

struct Motors_MemMap
{
	uint8_t		i2caddr;
   uint16_t		high_pulse;
   uint16_t		low_pulse;
};

void Motor_Init(struct RTOS_SHARED_MEM* RTOS_MEM,
											  uint32_t RTOSTime);
											  
void Motor_Update(struct RTOS_SHARED_MEM* RTOS_MEM,
											  uint32_t RTOSTime);



#endif