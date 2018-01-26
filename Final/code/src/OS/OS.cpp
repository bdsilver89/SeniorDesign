#include "OS/OS.h"
#include "OS/tasks.h"
#include <time.h>
#include <signal.h>
#include <iostream>

unsigned int RTOSTickCtr = 0;

void RTOSTmrSignal(int signum)
{
    RTOSTickCtr++;
    if (RTOSTickCtr % 10 == 0)
    {
        for (int i = 0; i < NUM_TASKS; i++)
            task_ptr[i]();
        std::cout << std::endl;
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