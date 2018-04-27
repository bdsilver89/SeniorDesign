#include "Control/Controller.h"
#include "OS/OSMemMap.h"
#include <iostream>
#include <vector>
#include <string>

// #define ENABLE_DEBUG_CONSOLE

// MACRO for threshold of acceptable weight to continue
#define THRESHOLD 2

void Controller_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err)
{
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Controller init task starting" << std::endl;
	#endif
	struct Controller_MemMap* ControllerMem_ptr = &((*RTOS_MEM).ControllerMem);
	
	for (int i = 0; i < NUM_MOTORS; i++)
	{
		(*ControllerMem_ptr).Motor_Speeds[i] = 0;
		(*ControllerMem_ptr).Motor_Enable[i] = 0;
	}

	(*ControllerMem_ptr).currentRecipeIndex = -1;
	(*ControllerMem_ptr).currentContainerIndex = -1;

	*err = 0;
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Controller init task ending\n"  << std::endl;
	#endif
}



void Controller_Update(struct RTOS_SHARED_MEM* RTOS_MEM, uint32_t RTOSTime)
{
	struct UI_MemMap* UIMem_ptr = &((*RTOS_MEM).UIMem);
	struct Controller_MemMap* ControllerMem_ptr = &((*RTOS_MEM).ControllerMem);

	if((*UIMem_ptr).startDispensingFlag == 1)
	{
		#ifdef ENABLE_DEBUG_CONSOLE
			std::cout << "Controller update starting" << std::endl;
		#endif
		
		struct Weight_MemMap* WeightMem_ptr = &((*RTOS_MEM).WeightDriverMem);	
		struct Parser_MemMap* RecipeMem_ptr = &((*RTOS_MEM).ParserMem);		
		struct Config_MemMap* ConfigMem_ptr = &((*RTOS_MEM).ConfigMem);	
	
	
		// first spice to be dispensed
		if((*ControllerMem_ptr).currentRecipeIndex == -1)
		{
			(*ControllerMem_ptr).currentRecipeIndex = 0;
			uint8_t foundFlag = 0;
			std::string name = ((*RecipeMem_ptr).currentRecipe).Spices[0].getType();
			for(int i = 0; i < NUM_SPICE_VIALS; i++)
			{
				std::string cont = (*ConfigMem_ptr).Containers[i];
				if(!cont.compare(name))
				{
					//found a match
					foundFlag = 1;
					(*ControllerMem_ptr).currentContainerIndex = i;
				}
			}
		}
		
		else
		{
			
			if(((*RecipeMem_ptr).currentRecipe).Spices[(*ControllerMem_ptr).currentRecipeIndex].PourTime > 0)
			{
				((*RecipeMem_ptr).currentRecipe).Spices[(*ControllerMem_ptr).currentRecipeIndex].PourTime--;
				std::cout << "Dispensing: " << ((*RecipeMem_ptr).currentRecipe).Spices[(*ControllerMem_ptr).currentRecipeIndex].PourTime << std::endl;
				(*ControllerMem_ptr).Motor_Enable[(*ControllerMem_ptr).currentContainerIndex] = 1;
				(*ControllerMem_ptr).Motor_Speeds[(*ControllerMem_ptr).currentContainerIndex] = 355;
			}
			else
			{
				(*ControllerMem_ptr).Motor_Enable[(*ControllerMem_ptr).currentContainerIndex] = 0;
				
				if((*ControllerMem_ptr).currentRecipeIndex < (((*RecipeMem_ptr).currentRecipe).Spices).size()-1)
				{
					(*ControllerMem_ptr).currentRecipeIndex++;
					uint8_t foundFlag = 0;
					std::string name = ((*RecipeMem_ptr).currentRecipe).Spices[(*ControllerMem_ptr).currentRecipeIndex].getType();
					std::cout << name << std::endl;
					for(int i = 0; i < NUM_SPICE_VIALS; i++)
					{
						std::string cont = (*ConfigMem_ptr).Containers[i];
						if(!cont.compare(name))
						{
							//found a match
							foundFlag = 1;
							(*ControllerMem_ptr).currentContainerIndex = i;
						}
					}
				}

				else
				{
					(*ControllerMem_ptr).currentRecipeIndex = -1;
					(*UIMem_ptr).startDispensingFlag = 0;
					std::cout << "Done with all dispensing" << std::endl;
				}
			}
		}
		
		
				

		
		#ifdef ENABLE_DEBUG_CONSOLE
			std::cout << "Controller update ending\n"  << std::endl;
		#endif
	}
	
	else
	{
		(*ControllerMem_ptr).Motor_Enable[0] = 0;
		(*ControllerMem_ptr).Motor_Enable[1] = 0;
	}
}
