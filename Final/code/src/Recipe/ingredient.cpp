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
	std::cout << "\tING: " << Spice << std::endl;
	std::cout << "\tAMT: " << Amount << std::endl;
	std::cout << "\tMEAS: " << Measurement << std::endl;
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
