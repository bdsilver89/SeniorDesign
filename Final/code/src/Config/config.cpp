#include "Config/config.h"
#include "OS/OSMemMap.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


// #define ENABLE_DEBUG_CONSOLE 


void Config_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err)
{
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Config init task starting" << std::endl;
	#endif
	
	struct Config_MemMap* ConfigMem_ptr = &((*RTOS_MEM).ConfigMem);
    std::string line;
    std::ifstream File("./config.txt");
    if (File.is_open())
    {
		for(int i = 0; i < NUM_SPICE_VIALS; i++)
		{
			std::getline(File, line);
			(*ConfigMem_ptr).Containers.push_back(line);
		}
	}
	File.close();


	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Config init task ending\n" << std::endl;
	#endif
}


							  
void Config_Update(struct RTOS_SHARED_MEM* RTOS_MEM, uint32_t RTOSTime)
{
	struct UI_MemMap* UIMem_ptr = &((*RTOS_MEM).UIMem);

	if((*UIMem_ptr).changeContainerFlag == 1)
	{
		#ifdef ENABLE_DEBUG_CONSOLE
			std::cout << "Config update task starting" << std::endl;
		#endif

		//task update code	
		struct Config_MemMap* ConfigMem_ptr = &((*RTOS_MEM).ConfigMem);


		(*UIMem_ptr).changeContainerFlag = 0;
		//Check for flags in the UI section to see if a new spice has been put in
		
		//update the config.txt file ONLY IF there has been a change
				
			
		#ifdef ENABLE_DEBUG_CONSOLE
			std::cout << "Config update task ending\n" << std::endl;
		#endif
	}
}
