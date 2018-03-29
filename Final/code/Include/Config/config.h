#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
#include <string>
#include <vector>

#define NUM_SPICE_VIALS 3

struct Config_MemMap
{
	std::vector<std::string> Vials;		// list of current vial spices
	// need to add modifying function for it
};



// This file will contain device config paramaters
// such as what spices are loaded into the machine
// and other user settings


#endif
