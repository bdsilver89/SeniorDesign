#include "Recipe/ingredient.h"
#include <iostream>



Ingredient::Ingredient(double a, std::string m, std::string t)
{
    Amount = a;
    Measurement = m;
	Spice = t;
}



void Ingredient::display(void)
{
	std::cout << "The amount is: " << Amount << std::endl;
	std::cout << "The measurement type is: " << Measurement << std::endl;
	std::cout << "The spice is: " << Spice << std::endl;
}



double Ingredient::getAmount(void)
{
	return Amount;
}



std::string Ingredient::getMeasurement(void)
{
	return Measurement;
}



std::string Ingredient::getType(void)
{
	return Spice;
}
