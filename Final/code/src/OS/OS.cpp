#include "OS/OS.h"
#include "OS/OSTasks.h"
#include <cstdint>
#include <time.h>
#include <signal.h>
#include <iostream>
#include <stdlib.h>

// #define ENABLE_DEBUG_CONSOLE


uint32_t RTOSTickCtr = 0;
uint8_t  RTOSTimerFlag = 0;

void OSRun(void)
{
    while(1)
    {
        RTOSTickCtr++;
        for (int i = 0; i < NUM_TASKS; i++)
        {
            (void)Task_List[i].RTOSTask(Task_List[i].MEM,
                                        RTOSTickCtr);
        }
        RTOSTimerFlag = 0;
        while(RTOSTimerFlag == 0)
        { 
				//service GUI until time runs out then do the output update      
        }
    }
}

void RTOSTmrSignal(int signum)
{
    if(RTOSTimerFlag == 1)
    {
		#ifdef ENABLE_DEBUG_CONSOLE
			std::cout << "OS Timer ticked before task processing done" << std::endl;
		#endif
    }

    else
    {
        RTOSTimerFlag = 1;
    }
}


void OSTickInitialize(void)
{
    timer_t RTOSTmr;
    struct itimerspec time_value;

    // Setup the timer for 100ms
    time_value.it_interval.tv_sec = 0;
    time_value.it_interval.tv_nsec = 100000000;

    time_value.it_value.tv_sec = 0;
    time_value.it_value.tv_nsec = 100000000;

    // Change the action of SIGALRM to call RTOSTmrSignal
    signal(SIGALRM, &RTOSTmrSignal);
    
    // Create timer object
    timer_create(CLOCK_REALTIME, NULL, &RTOSTmr);

    // Start the timer
    timer_settime(RTOSTmr, 0, &time_value, NULL);
}


void OSTaskInitialize(void)
{
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Starting initialization" << std::endl;
	#endif
	uint8_t err_val;
	for (int i = 0; i < NUM_INIT; i++)
	{
		(void)Init_List[i].RTOSInitTask(Init_List[i].MEM, &err_val);
		if (err_val == 1)
		{
			#ifdef ENABLE_DEBUG_CONSOLE
				std::cout << "ERROR: Task initialization failed." << std::endl;
			#endif
			exit(1);		
		}
	}
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Finished initilization" << std::endl;
		std::cout << "---------------------------------" << std::endl;
	#endif
}


void OSInitialize(void)
{
	OSTaskInitialize();
	OSTickInitialize();
}

