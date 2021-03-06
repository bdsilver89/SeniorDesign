#include "recipe/recipe.h"
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <cstdio>


std::vector<std::string> getParsedRecipes(void)
{
    std::vector<std::string> result;
    DIR *dir = opendir(RECIPE_PATH);
    struct dirent *dp;
    while ((dp = readdir(dir)) != NULL)
    {
        std::string name = dp->d_name;
        if (name.find(".txt") != std::string::npos)
            result.push_back(name);
    }
    return result;
}




Recipe::Recipe(std::string n)
{
    FileName = n;
    FilePath = RECIPE_PATH + n + ".txt";
}



Recipe::~Recipe(void)
{
    //std::remove(FilePath);
}



std::string Recipe::getName(void)
{
    return FileName;
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
        File << I.getMeasurement() << "\n\n"; 
        File.close();
    }

    else
    {
        std::cout << "Could not save recipe" << std::endl;
    }
}




void Recipe::changeRecipeName(std::string n)
{
    
}