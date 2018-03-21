#include "UI/UI.h"
#include "OS/OSMemMap.h"
#include <iostream>

// #define ENABLE_DEBUG_CONSOLE


void UI_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err)
{
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "UI init task starting" << std::endl;
	#endif
	
	struct UI_MemMap* UIMem_ptr = &((*RTOS_MEM).UIMem);
	(*UIMem_ptr).readRecipeFlag = 0;
	(*UIMem_ptr).writeRecipeFlag = 0;
	(*UIMem_ptr).startDispensingFlag = 0;	


	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "UI init task ending\n" << std::endl;
	#endif
}


							  
void UI_Update(struct RTOS_SHARED_MEM* RTOS_MEM, uint32_t RTOSTime)
{
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "UI update task starting" << std::endl;
	#endif

	//task update code	
	struct UI_MemMap* UIMem_ptr = &((*RTOS_MEM).UIMem);
	if (RTOSTime == 10)
		(*UIMem_ptr).readRecipeFlag = 1;
		// (*UIMem_ptr).writeRecipeFlag = 1;

	else
		(*UIMem_ptr).readRecipeFlag = 0;
		// (*UIMem_ptr).writeRecipeFlag = 0;
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "UI update task ending\n" << std::endl;
	#endif	
}


