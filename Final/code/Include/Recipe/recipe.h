#ifndef RECIPE_H
#define RECIPE_H

#include <cstdint>
#include <vector>
#include <string>
#include "Recipe/ingredient.h"

#define RECIPE_PATH "./../../../saved_recipes/"


/**
 * TODO:
 * 1. add ingredient(s) to file
 * 2. remove ingredient(s) from file
 * 3. modify ingredients in a file
 */




/**
 * [getParsedRecipes description]
 * @return [description]
 */
std::vector<std::string> getParsedRecipes(void);



class Recipe
{
private:
    std::string FileName;
    std::vector<Ingredient> Ingredients;

public:
	Recipe() {}
	
    Recipe(std::string n);

    ~Recipe();

    /**
     * [getName description]
     * @return  [description]
     */
    std::string getName(void);
    
        
    
     /**
     * [addIngredient description]
     */
    void addIngredient(Ingredient ing);   
    


     /**
     * [display description]
     */
    void display(void); 

    

    /**
     * [readFile description]
     */
    void readFile(void);
    
    
    
    /**
     * Change to write a single Ingredient and a list of
     * ingredients
     * also a write for text or something?
     */
    
   
    /**
     * [clearFile description]
     */
    void clearFile(void);



    /**
     * [writeFile description]
     * @param I [description]
     */
    void writeFile(Ingredient I);



    /**
     * [changeRecipeName description]
     * @param n [description]
     */
    void changeRecipeName(std::string n);
};


#endif
