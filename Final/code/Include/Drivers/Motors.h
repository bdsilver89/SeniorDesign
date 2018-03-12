#ifndef MOTORS_H
#define MOTORS_H

#include <cstdint>

struct Motors_MemMap
{
	uint8_t		i2caddr;
};
#define MOTORS_MEMMAP_SIZE	sizeof(Motors_MemMap)


/**
 * [Motor_Init description]
 * @param RTOS_MEM [description]
 * @param err      [description]
 */
void Motor_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err);
							


/**
 * [Motor_Update description]
 * @param RTOS_MEM [description]
 * @param RTOSTime [description]
 */
void Motor_Update(struct RTOS_SHARED_MEM* RTOS_MEM, uint32_t RTOSTime);


#endif
