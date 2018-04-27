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
    std::vector<std::string> Directions;

public:
    std::vector<Ingredient> Spices;

	Recipe() {}
	
    Recipe(std::string n);
    
    Recipe(std::string n, std::vector<Ingredient> ing, std::vector<std::string> dir);

    ~Recipe() {}

     /**
     * [display description]
     */
    void display(void); 



     /**
     * [addIngredient description]
     */
    void addIngredient(Ingredient ing);   


     /**
     * [addSpice description]
     */
    void addSpice(Ingredient ing);   
    
    
     /**
     * [addDirection description]
     */
	void addDirection(std::string dir);


    /**
     * [getName description]
     * @return  [description]
     */
    std::string getFileName(void);
    
    
        
     /**
     * [getIngredients description]
     * @return  [description]
     */
	std::vector<Ingredient> getIngredients();
	

     /**
     * [getDirections description]
     * @return  [description]
     */
	std::vector<std::string> getDirections();
	
	
};

#endif
