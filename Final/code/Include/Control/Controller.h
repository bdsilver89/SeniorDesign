#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <cstdint>

#define NUM_MOTORS 4

struct PID_Controller
{
	int16_t			PID_val[NUM_MOTORS];			
	uint16_t		Target_Positions[NUM_MOTORS];
	uint16_t		Current_Positions[NUM_MOTORS];
	int16_t			Error[NUM_MOTORS];
	int16_t			Last_Error[NUM_MOTORS];
	int16_t			Integral[NUM_MOTORS];
	int16_t			Derivative[NUM_MOTORS];
	int16_t			Kp[NUM_MOTORS];
	int16_t			Ki[NUM_MOTORS];
	int16_t			Kd[NUM_MOTORS];	
};
#define PID_CONTROLLER_SIZE	sizeof(PID_Controller)


struct Controller_MemMap
{
	int8_t					currentRecipeIndex;
	int8_t					currentContainerIndex;
	uint8_t					Motor_Enable[NUM_MOTORS];
	uint16_t				Motor_Speeds[NUM_MOTORS];
	struct PID_Controller	PID;
};
#define CONTROLLER_MEMMAP_SIZE	sizeof(Controller_MemMap)


/**
 * [Controller_Init description]
 * @param RTOS_MEM [description]
 * @param err      [description]
 */
void Controller_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err);



/**
 * [Controller_Update description]
 * @param RTOS_MEM [description]
 * @param RTOSTime [description]
 */
void Controller_Update(struct RTOS_SHARED_MEM* RTOS_MEM, uint32_t RTOSTime);



#endif
