#include "UI/UI.h"
#include "OS/OSMemMap.h"
#include <iostream>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>


// #define ENABLE_DEBUG_CONSOLE 


void startRecipeRead(struct RTOS_SHARED_MEM* RTOS_MEM)
{
	struct UI_MemMap* UIMem_ptr = &((*RTOS_MEM).UIMem);
	(*UIMem_ptr).readRecipeFlag = 1;
}



void startRecipeWrite(struct RTOS_SHARED_MEM* RTOS_MEM)
{
	struct UI_MemMap* UIMem_ptr = &((*RTOS_MEM).UIMem);
	(*UIMem_ptr).writeRecipeFlag = 1;
}




void startDispensing(struct RTOS_SHARED_MEM* RTOS_MEM)
{
	struct UI_MemMap* UIMem_ptr = &((*RTOS_MEM).UIMem);
	(*UIMem_ptr).startDispensingFlag = 1;	
}


void stopCommands(struct RTOS_SHARED_MEM* RTOS_MEM)
{
	struct UI_MemMap* UIMem_ptr = &((*RTOS_MEM).UIMem);
	(*UIMem_ptr).readRecipeFlag = 0;
	(*UIMem_ptr).writeRecipeFlag = 0;
	(*UIMem_ptr).startDispensingFlag = 0;
}

int kbhit()
{
	struct timeval tv = {0L, 0L};
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	return select(1, &fds, NULL, NULL, &tv);
}

int getch()
{
	int r;
	unsigned char c;
	if ((r = read(0, &c, sizeof(c))) < 0)
		return r;
	else
		return c;
}



void UI_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err)
{
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "UI init task starting" << std::endl;
	#endif
	
	struct UI_MemMap* UIMem_ptr = &((*RTOS_MEM).UIMem);
	(*UIMem_ptr).readRecipeFlag = 0;
	(*UIMem_ptr).writeRecipeFlag = 0;
	(*UIMem_ptr).startDispensingFlag = 0;
	(*UIMem_ptr).changeContainerFlag = 0;
	
	std::cout << "Press '0' to start reading a recipe" << std::endl;
	std::cout << "Press '1' to write the current recipe" << std::endl;
	std::cout << "Press '2' to start cooking the current recipe" << std::endl;
	std::cout << "Press '3' to stop" << std::endl;

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
	
	
	char buffer[256];
	int point = 0;
	

	while(kbhit())
	{
		char cur = getch();
		if (point > 255)
			point = 255;
		if (cur != 13)
			buffer[point++] = cur;
		else
		{
			buffer[point] = '\0';
			point = 0;
		}
	}
	if(buffer[0] == '0')
		startRecipeRead(RTOS_MEM);
		
	else if (buffer[0] == '1')
		startRecipeWrite(RTOS_MEM);
	
	else if (buffer[0] == '2')
		startDispensing(RTOS_MEM);
	else if (buffer[0] == '3')
		stopCommands(RTOS_MEM);
	
			
		
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "UI update task ending\n" << std::endl;
	#endif	
}
