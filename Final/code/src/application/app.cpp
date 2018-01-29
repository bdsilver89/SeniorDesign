#include <iostream>
#include <cstdint>
#include "OS/OS.h"

#define ENABLE_DEBUG_CONSOLE


int main()
{
	#ifdef ENABLE_DEBUG_CONSOLE
		uint8_t start;
		std::cout << "AutoSpice: The Automatic Spice Mixer"	<< std::endl;
		std::cout << "\tSenior Design 2017F-2018S"			<< std::endl;
		std::cout << "\tSW Team: "							<< std::endl;
		std::cout << "\t\tBrian Silver"						<< std::endl;
		std::cout << "\t\tKyle Emanuele"					<< std::endl;
		std::cout << "\tAdvisor: Prof. Bryan Ackland"		<< std::endl;
		std::cout << std::endl;
		std::cout << "Press any button to begin"			<< std::endl;
		std::cin	>> start;
		std::cout << "------------------------------------"	<<std::endl;
	#endif
	OSInitialize();
	OSRun();
	return 0;
}
