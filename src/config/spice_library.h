#ifndef SPICE_LIBRARY_H
#define SPICE_LIBRARY_H

#include <string>
#include <vector>

#define NUM_SPICES 5

std::vector<std::string> SPICE_LIST {
	"salt",
	"paprika",
	"oregano",
    "pepper",
    "garlic powder"
};



/**
 * TODO
 * Consider putting this into a class
 * The class would have functions to add
 * and remove spices from the list
 * and provide a way to safely access the list
 */

class SpiceLibrary
{
public:
    SpiceLibrary();
    
};

#endif