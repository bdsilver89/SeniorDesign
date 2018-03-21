#ifndef OSMEMMAP_H
#define OSMEMMAP_H

#include "Drivers/Motors.h"
#include "Drivers/Weight.h"
#include "Control/Controller.h"
#include "UI/UI.h"
#include "Recipe/parser.h"
#include "Config/config.h"

// struct definition for shared memory in RTOS environment
struct RTOS_SHARED_MEM
{
	struct Config_MemMap		ConfigMem;
	struct UI_MemMap			UIMem;
	struct Parser_MemMap		ParserMem;	
	struct Controller_MemMap	ControllerMem;	
	struct Motors_MemMap		MotorDriverMem;
	struct Weight_MemMap		WeightDriverMem;
};
#define RTOS_SHARED_MEM_SIZE	sizeof(RTOS_SHARED_MEM)

#endif
