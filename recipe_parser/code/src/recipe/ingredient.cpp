#include <iostream>
#include "recipe/ingredient.h"



Ingredient::Ingredient(double a, std::string m, std::string t)
{
    Amount = a;
    Measurement = m;
	Spice = t;
}

/**
 * [Ingredient::display description]
 */
void Ingredient::display(void)
{
	std::cout << "The amount is: " << Amount << std::endl;
	std::cout << "The measurement type is: " << Measurement << std::endl;
	std::cout << "The spice is: " << Spice << std::endl;
}


/**
 * [Ingredient::getAmount description]
 * 
 * @return {double} [description]
 */
double Ingredient::getAmount(void)
{
	return Amount;
}


/**
 * [Ingredient::getMeasurement description]
 * @return {int} [description]
 */
std::string Ingredient::getMeasurement(void)
{
	return Measurement;
}


/**
 * [Ingredient::getType description]
 * @return {int} [description]
 */
std::string Ingredient::getType(void)
{
	return Spice;
}
