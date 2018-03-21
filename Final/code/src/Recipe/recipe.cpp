#include "Recipe/recipe.h"
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
}



Recipe::Recipe(std::string n, std::vector<Ingredient> ing, std::vector<std::string> dir)
{
    FileName = n;
    Ingredients = ing;
    Directions = dir;
}



std::string Recipe::getFileName(void)
{
    return FileName;
}



void Recipe::addIngredient(Ingredient ing)
{
	Ingredients.push_back(ing);
}



void Recipe::addSpice(Ingredient ing)
{
	Spices.push_back(ing);
}



void Recipe::addDirection(std::string dir)
{
	Directions.push_back(dir);
}



std::vector<Ingredient> Recipe::getIngredients()
{
	return Ingredients;
}



std::vector<std::string> Recipe::getDirections()
{
	return Directions;
}


void Recipe::display()
{
	std::cout << "Spices:" << std::endl;
	for(int i = 0; i < Spices.size(); i++)
	{
		Spices[i].display();
		std::cout << std::endl;
	}
	std::cout << std::endl;
		
	
	std::cout << "Other Ingredients:" << std::endl;
	for(int i = 0; i < Ingredients.size(); i++)
	{
		Ingredients[i].display();
		std::cout << std::endl;
	}
	std::cout << std::endl;
	
	
	std::cout << "Directions:" << std::endl;
	for(int i = 0; i < Directions.size(); i++)
	{
		std::cout << "Step " << i+1 << ": " << Directions[i] << std::endl;
		std::cout << std::endl;
	}
}
