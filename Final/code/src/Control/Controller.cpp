#include "Control/Controller.h"
#include "OS/OSMemMap.h"
#include <iostream>
#include <vector>
#include <string>

// #define ENABLE_DEBUG_CONSOLE

// MACRO for threshold of acceptable weight to continue
#define THRESHOLD 0

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
	(*ControllerMem_ptr).doneFlag = 0;

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
	
		/* FINAL CONTROLLER:
		 * for each update until dispensing flag is 0
		 * do one quick read and update of the PID loop
		 * for the ONE motor related to the spice in the 
		 * SPICES list of the recipe.
		 * NEED TO CONVERT THE SPICE WEIGHT TO GRAMS
		 * if its done, set the UI dispensing flag to 0 again
		 */
			
		std::vector<Ingredient> IngList = ((*RecipeMem_ptr).currentRecipe).getSpices();

		// first spice to be dispensed
		if((*ControllerMem_ptr).currentRecipeIndex == -1)
		{
			(*ControllerMem_ptr).currentRecipeIndex = 0;
			uint8_t foundFlag = 0;
			std::string name = IngList[0].getType();
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
				
			// did not find ingredient in the containers
			if(foundFlag == 0)
			{
				std::cout << "Boi that spice doesn't exist" << std::endl;
				// TODO: ERROR stuff
			}
			std::cout << "DISPENSING" << std::endl;
			std::cout << "\tRecipe index: " << unsigned((*ControllerMem_ptr).currentRecipeIndex) << std::endl;
			std::cout << "\tContainer index: " << unsigned((*ControllerMem_ptr).currentContainerIndex) << std::endl;
			std::cout << std::endl;
			
			(*ControllerMem_ptr).Motor_Enable[(*ControllerMem_ptr).currentContainerIndex] = 1;
		
			(*ControllerMem_ptr).Motor_Speeds[(*ControllerMem_ptr).currentContainerIndex] = 360;
		}
		/*
		// not the first spice to be dispensed	
		else
		{
			double targetWeight = IngList[(*ControllerMem_ptr).currentRecipeIndex].getGrams();
			double currentWeight = (*WeightMem_ptr).weight;
		
			if ((targetWeight - currentWeight <= THRESHOLD) ||
				(targetWeight - currentWeight >= THRESHOLD))
			{
			
				// check for next ingredient or move on
				if((*ControllerMem_ptr).currentRecipeIndex < IngList.size()-1)
				{
					(*ControllerMem_ptr).currentRecipeIndex++;
				}
				/*
				uint8_t foundFlag = 0;
				std::string name = IngList[(*ControllerMem_ptr).currentRecipeIndex].getType();
				for(int i = 0; i < NUM_SPICE_VIALS; i++)
				{
					std::string cont = (*ConfigMem_ptr).Containers[i];
					if(!cont.compare(name))
					{
						//found a match
						foundFlag = 1;
						std::cout << "ING FOUND" << std::endl;
						(*ControllerMem_ptr).currentContainerIndex = i;
					}
				}
				
				// did not find ingredient in the containers
				if(foundFlag == 0)
				{
					std::cout << "Cant find the ingredient" << std::endl;
				}
			}
			else
			{
				(*ControllerMem_ptr).doneFlag = 1;
			}
		}
		
		
		else
		{
			//CONTROL LOOP
			std::cout << "DISPENSING" << std::endl;
			std::cout << "\tRecipe index: " << unsigned((*ControllerMem_ptr).currentRecipeIndex) << std::endl;
			std::cout << "\tContainer index: " << unsigned((*ControllerMem_ptr).currentContainerIndex) << std::endl;
			std::cout << std::endl;
			
			(*ControllerMem_ptr).Motor_Enable[(*ControllerMem_ptr).currentContainerIndex] = 1;
		
			(*ControllerMem_ptr).Motor_Speeds[(*ControllerMem_ptr).currentContainerIndex] = 360;
		}
		*/
		
		
		/* Test values to turn on the motors */
		// (*ControllerMem_ptr).Motor_Enable[0] = 1;
		// (*ControllerMem_ptr).Motor_Enable[1] = 1;
		
		// (*ControllerMem_ptr).Motor_Speeds[0] = 360;
		// (*ControllerMem_ptr).Motor_Speeds[1] = 360;	
		
		
		// TEST PID Control Loop
		/*
		struct PID_Controller *PID_ptr;
		for (int i = 0; i < NUM_MOTORS; i++)
		{
			Current_Positions[i] = read_current_position(i);	// replace with info from GUI
			Error[i] = Target_Positions[i] - Current_Positions[i];
			Integral[i] += Error[i];
			Derivative[i] = Error[i] - Last_Errors[i];
			
			PID_val[i] = (Kp[i] * Error[i]) + (Ki[i] * Integral[i]) + (Kd[i] * Derivative[i]);
		}
		*/	
		
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
