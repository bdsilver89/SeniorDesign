#ifndef WEIGHT_H
#define WEIGHT_H

#include <cstdint>



struct Weight_MemMap
{
	uint8_t		i2caddr;
	uint16_t	weight;
	uint16_t	weight_LUT[2];		// some sort of LUT for weight/teaspoon?
};
#define WEIGHT_MEMMAP_SIZE	sizeof(Weight_MemMap)

void Weight_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err);
											  
void Weight_Update(struct RTOS_SHARED_MEM* RTOS_MEM, uint32_t RTOSTime);


#endif
