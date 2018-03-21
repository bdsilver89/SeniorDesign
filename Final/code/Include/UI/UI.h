#ifndef UI_H
#define UI_H

#include <cstdint>

struct UI_MemMap
{
	uint8_t		readRecipeFlag;
	uint8_t		writeRecipeFlag;
	uint8_t		startDispensingFlag;
};
#define UI_MEMMAP_SIZE	sizeof(UI_MemMap)


/**
 * [UI_Init description]
 * @param RTOS_MEM [description]
 * @param err      [description]
 */
void UI_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err);



/**
 * [UI_Update description]
 * @param RTOS_MEM [description]
 * @param RTOSTime [description]
 */
void UI_Update(struct RTOS_SHARED_MEM* RTOS_MEM, uint32_t RTOSTime);


#endif
