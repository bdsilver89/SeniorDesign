#include "OS/OS.h"
#include "OS/OSTasks.h"
#include <cstdint>
#include <time.h>
#include <signal.h>
#include <iostream>
#include <stdlib.h>

#define ENABLE_DEBUG_CONSOLE

// variable to hold sum total of RTOS clock ticks (1 tick = 1 timer interrupt)
uint32_t RTOSTickCtr = 0;

// flag to determine if the RTOS timer has overflowed yet or not
uint8_t  RTOSTimerFlag = 0;



// main OS loop
void OSRun(void)
{
    while(1)
    {
        RTOSTickCtr++;
        
        // Complete all tasks from the update list
        for (int i = 0; i < NUM_TASKS; i++)
        {
            (void)Task_List[i].RTOSTask(Task_List[i].MEM, RTOSTickCtr);
        }
        
        // Clear timer overflow flag
        RTOSTimerFlag = 0;
        
        // Wait for timer reset by servicing background tasks
        while(RTOSTimerFlag == 0)
        { 
			// background tasks like GUI servicing
        }
    }
}




// Signaled through SIGALRM to change the timer overflow state
void RTOSTmrSignal(int signum)
{
	// Timer has overflowed before task list clears flag
    if(RTOSTimerFlag == 1)
    {
		#ifdef ENABLE_DEBUG_CONSOLE
			std::cout << "OS Timer ticked before task processing done" << std::endl;
		#endif
    }

	// Task list completed and cleared flag
    else
    {
        RTOSTimerFlag = 1;
    }
}



// setup the RTOS timer
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


// call any initialization tasks before the RTOS loop starts
void OSTaskInitialize(void)
{
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Starting initialization" << std::endl;
	#endif
	uint8_t err_val;
	
	// run all init tasks from the list
	for (int i = 0; i < NUM_INIT; i++)
	{
		(void)Init_List[i].RTOSInitTask(Init_List[i].MEM, &err_val);
		
		// error catching
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

