#include "OSMemMap.h"

#include <stdlib.h>
#include <cstdint>

#define NUM_INIT	3 
#define NUM_TASKS	3

// Shared memory structure for all tasks
struct RTOS_SHARED_MEM MemMap;

// type declaration for update style task handles
typedef void (*UPDATE_TASK_HANDLE)(struct RTOS_SHARED_MEM* RTOS_MEM,
                            uint32_t RTOSTime);

// type declaration for update style task list entry
typedef struct task
{
    UPDATE_TASK_HANDLE            RTOSTask;
    struct RTOS_SHARED_MEM   *MEM;
} RTOS_TASK;

// type declaration for initialization style task handles
typedef void (*INIT_TASK_HANDLE)(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err);

// type declaration for initialization style task entry
typedef struct init
{
    INIT_TASK_HANDLE            RTOSInitTask;
    struct RTOS_SHARED_MEM   *MEM;
} RTOS_INIT_TASK;


//List of all initialization tasks to run before the OS cycle starts
RTOS_INIT_TASK Init_List[NUM_INIT] = {
    {&Controller_Init, 		&(MemMap)},
    {&Motor_Init, 			&(MemMap)},
    {&Weight_Init,			&(MemMap)}
};


// List of all tasks to run in one OS cycle
RTOS_TASK Task_List[NUM_TASKS] = {
    {&Controller_Update,	&(MemMap)},
    {&Motor_Update,			&(MemMap)},
    {&Weight_Update,		&(MemMap)},
};