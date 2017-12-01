#include <iostream>
#include <fstream>
#include "parser.h"
#include "spice_library.h"
#include "ingredient.h"
#include "recipe.h"


Parser::Parser(void) {}



void Parser::displayFile(std::string inputFilePath)
{
	std::string line;
	std::ifstream InputFile(inputFilePath);

	if (InputFile.is_open())
	{
	    while (getline(InputFile, line))
        {	
            std::cout << line << std::endl;
        }
    InputFile.close();
    }

    else
    {
        std::cout << "Could not open file" << std::endl;
    }
}



std::vector<std::string> Parser::split(std::string str, std::string token) {
	std::vector<std::string> result;

	while(str.size())
	{
		int index = str.find(token);
		if (index != std::string::npos)
		{
			result.push_back(str.substr(0, index));
			str = str.substr(index + token.size());
		}

		else
		{
			result.push_back(str);
			str = "";
		}

	}
	return result;
}


/**
 * [getAmount description]
 * @param  {} s [description]
 * @return {int} [description]
 */
double Parser::getAmount(std::vector<std::string>::const_iterator s)
{
    double result = -1.0;
    std::string::size_type n = (*s).find('/');
    if (n != std::string::npos)
    {
        std::string str1 = (*s).substr(0,n);
        std::string str2 = (*s).substr(n+1);

        int num = std::atoi((str1).c_str());
        int den = std::atoi((str2).c_str());

        result = double(num) / double(den);
    }

    else
    {
        result = double(std::atoi((*s).c_str()));
    }

	return result;
}



/**
 * [getMeasurement description]
 * @param  {} s [description]
 * @return {int}  [description]
 */
int Parser::getMeasurement(std::vector<std::string>::const_iterator s)
{
    /**
     * TODO
     * Fix the measurement for plurals
     * i.e.
     *     cups --> cup
     *     tsps --> tsp
     *     etc.
     */
    
	for (int i = 0; i < 4; i++)
	{
        if (*s == MEASURE_LIST[i])
		{
			return i;
		}
	}
	return -1;
}


/**
 * [Parser::checkAmountType description]
 * @param  {} s [description]
 * @return {bool} [description]
 */
bool Parser::checkAmountType(std::vector<std::string>::const_iterator s)
{
    if ((*s).find('0') != std::string::npos ||
        (*s).find('1') != std::string::npos ||
        (*s).find('2') != std::string::npos ||
        (*s).find('3') != std::string::npos ||
        (*s).find('4') != std::string::npos ||
        (*s).find('5') != std::string::npos ||
        (*s).find('6') != std::string::npos ||
        (*s).find('7') != std::string::npos ||
        (*s).find('8') != std::string::npos ||
        (*s).find('9') != std::string::npos)
    {
        return true;
    }
    return false;
}



/**
 * [Parser::checkMeasureType description]
 * @param  s [description]
 * @return   [description]
 */
bool Parser::checkMeasureType(std::vector<std::string>::const_iterator s)
{
    for (int i = 0; i < 4; i++)
    {
        if ((*s).find(MEASURE_LIST[i]) != std::string::npos)
            return true;
    }
    return false;
}



/**
 * [Parser::parseFile description]
 */
void Parser::parseNewFile(std::string inputFilePath)
{
    std::string line;
	std::ifstream InputFile(inputFilePath);
    
    Recipe R("test");
    R.clearFile();

	if (InputFile.is_open())
	{
		while (getline(InputFile, line))
		{
			for (int i = 0; i < NUM_SPICES; i++)
			{
				if(line.find(SPICE_LIST[i]) != std::string::npos)
				{
					std::vector<std::string> splits = split(line, " ");
					
					double amount = 0.0;
					int measurement = 0;

					for(std::vector<std::string>::const_iterator s = splits.begin(); s != splits.end(); ++s)
					{                        
                        /* Check and parse number if it is not a measurement type */
                        bool isAmount = checkAmountType(s);
                        if (isAmount)
                        {
                            amount = getAmount(s);
                        }

                        /* Check Measure Type */
                        bool isMeasure = checkMeasureType(s);
                        if (!isAmount && isMeasure)
                        {
                            measurement = getMeasurement(s);
                        }
                    }
                    
                    /* Make new ingredient */
                    Ingredient I(amount, measurement, SPICE_LIST[i]);
                    R.writeFile(I);
                }
            }
        }
    InputFile.close();
    }

    else
    {
        std::cout << "Could not open file" << std::endl;
    } 
}



void Parser::parseSavedFile(void)
{
    std::vector<std::string> files = getParsedRecipes();
    for(std::vector<std::string>::const_iterator s = files.begin(); s != files.end(); ++s)
    {
        std::cout << *s << std::endl;
    }
}