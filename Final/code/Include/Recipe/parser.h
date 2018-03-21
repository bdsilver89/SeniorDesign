#ifndef PARSER_H
#define PARSER_H

#include <cstdint>
#include <vector>
#include <string>
#include "Recipe/ingredient.h"
#include "Recipe/recipe.h"


struct Parser_MemMap
{
	std::string		Recipe_Path;
	std::string		rawfilename;
	std::string		filename;
	Recipe			currentRecipe;
};

#define PARSER_MEMMAP_SIZE	sizeof(Parser_MemMap)

/**
 * [Parser_Init description]
 * @param RTOS_MEM [description]
 * @param err      [description]
 */
void Parser_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err);
	


/**
 * [Parser_Update description]
 * @param RTOS_MEM [description]
 * @param RTOSTime [description]
 */
void Parser_Update(struct RTOS_SHARED_MEM* RTOS_MEM, uint32_t RTOSTime);



class Parser
{
public:
    Parser(void) {}
 
 	/**
 	 * [parseFile description]
 	 * @param fileName [description]
 	 * @param IngList  [description]
 	 * @return         [description]
 	 */
 	Recipe parseFile(std::string fileName);

 	/**
 	 * [writeFile description]
 	 * @param fileName [description]
 	 * @param IngList  [description]
 	 */
 	void writeFile(Recipe r);
};


extern Parser parser;

#endif
