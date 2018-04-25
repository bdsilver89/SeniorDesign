#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
#include <string>
#include <vector>

#define NUM_SPICE_VIALS 3

struct Config_MemMap
{
	std::vector<std::string> Containers;		// list of current vial spices
	// need to add modifying function for it
};
#define CONFIG_MEMMAP_SIZE	sizeof(Config_MemMap)


/**
 * [Config_Init description]
 * @param RTOS_MEM [description]
 * @param err      [description]
 */
void Config_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err);
	

/**
 * [Config_Update description]
 * @param RTOS_MEM [description]
 * @param RTOSTime [description]
 */
void Config_Update(struct RTOS_SHARED_MEM* RTOS_MEM, uint32_t RTOSTime);


#endif
