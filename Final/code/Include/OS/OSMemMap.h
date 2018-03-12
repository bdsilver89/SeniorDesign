#ifndef OSMEMMAP_H
#define OSMEMMAP_H

#include "Drivers/Motors.h"
#include "Drivers/Weight.h"
#include "Control/Controller.h"
#include "UI/UI.h"
#include "Recipe/Parser.h"


// struct definition for shared memory in RTOS environment
struct RTOS_SHARED_MEM
{
	struct Motors_MemMap			MotorDriverMem;
	struct Weight_MemMap			WeightDriverMem;
	struct Controller_MemMap		ControllerMem;
	struct UI_MemMap				UIMem;
	struct Parser_MemMap			ParserMem;
};
#define RTOS_SHARED_MEM_SIZE	sizeof(RTOS_SHARED_MEM)

#endif
