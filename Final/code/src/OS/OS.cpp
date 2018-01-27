#include "OS/OS.h"
#include "OS/OSTasks.h"
#include <cstdint>
#include <time.h>
#include <signal.h>
#include <iostream>
#include <stdlib.h>

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
            nanosleep((const struct timespec[]){{0, 1}}, NULL);
        }
    }
}

void RTOSTmrSignal(int signum)
{
    if(RTOSTimerFlag == 1)
    {
        std::cout << "OS Timer ticked before task processing done" << std::endl;
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
	for (int i = 0; i < NUM_INIT; i++)
	{
		(void)Init_List[i].RTOSTask(Init_List[i].MEM, RTOSTickCtr);
	}
}


void OSInitialize(void)
{
	OSTaskInitialize();
	OSTickInitialize();
}

