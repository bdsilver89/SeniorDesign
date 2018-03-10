#ifndef RECIPE_H
#define RECIPE_H

#include <cstdint>
#include <vector>
#include <string>
#include "ingredient.h"

#define RECIPE_PATH "./saved_recipes/"

std::vector<std::string> getParsedRecipes(void);



class Recipe
{
private:
    std::string FilePath;
    std::string FileName;

public:
    Recipe(std::string n);

    ~Recipe();

    std::string getName(void);

    void readFile(void);
    
    /**
     * Change to write a single Ingredient and a list of
     * ingredients
     * also a write for text or something?
     */
    
    void clearFile(void);

    void writeFile(Ingredient I);

    void changeRecipeName(std::string n);

    /**
     * read to saved file
     *
     * write to saved file
     *
     * delete a file
     *
     * change recipe name
     */
};


#endif
