#ifndef UI_H
#define UI_H

#include <cstdint>

struct UI_MemMap
{
	uint8_t		test;
};
#define UI_MEMMAP_SIZE	sizeof(UI_MemMap)

void UI_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err);
											  
void UI_Update(struct RTOS_SHARED_MEM* RTOS_MEM, uint32_t RTOSTime);


#endif
