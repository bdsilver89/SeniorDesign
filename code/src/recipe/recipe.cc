#include "recipe/recipe.h"
#include <fstream>
#include <iostream>
#include <dirent.h>


std::vector<std::string> getParsedRecipes(void)
{
    std::vector<std::string> result;
    DIR *dir = opendir(RECIPE_PATH);
    struct dirent *dp;
    while ((dp = readdir(dir)) != NULL)
    {
        std::string name = dp->d_name;
        result.push_back(name);
    }
    result.erase(result.begin(), result.begin() + 3);
    return result;
}




Recipe::Recipe(std::string n)
{
    FileName = n;
    FilePath = RECIPE_PATH + n + ".txt";
}


void Recipe::readFile(void)
{
    std::string line;
    std::ifstream File(FilePath);

    if (File.is_open())
    {
        while (getline(File, line))
        {   
            std::cout << line << std::endl;
        }
    File.close();
    }

    else
    {
        std::cout << "Could not open file: " << FilePath << std::endl;
    }
}



/**
 * TODO
 * This function adds onto the existing file
 * It needs a clearfile function
 * to erase everything inside of it
 * That would be called by the parser
 * in order to clear a file to writing to
 */

void Recipe::clearFile(void)
{
    std::ofstream File(FilePath, std::ofstream::out | std::ofstream::trunc);
    File.close();
}


void Recipe::writeFile(Ingredient I)
{
   std::ofstream File(FilePath, std::ios::app);
    if (File.is_open())
    {
        File << I.getType() << "\n";
        File << I.getAmount() << "\n";
        File << I.getMeasurementStr() << "\n\n"; 
        File.close();
    }

    else
    {
        std::cout << "Could not save recipe" << std::endl;
    }
}



void Recipe::deleteFile(void)
{

}



void Recipe::changeRecipeName(std::string n)
{
    
}