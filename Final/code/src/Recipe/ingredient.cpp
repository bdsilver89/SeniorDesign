#include "Recipe/ingredient.h"
#include <iostream>
#include <unordered_map>


std::unordered_map<std::string, double> SpicetoWeight = {
	{"salt", 5.69}
};

std::unordered_map<std::string, double> MeasuretoTeaspoon = {
	{"pinch", 0.125},
	{"pinches", 0.125},
	{"teaspoon", 1.0},
	{"teaspoons", 1.0},
	{"tablespoon", 3.0},
	{"tablespoons", 3.0},
	{"cup", 48.0},
	{"cups", 48.0}
};


Ingredient::Ingredient(double a, std::string m, std::string t)
{
    Amount = a;
    Measurement = m;
	Spice = t;
	Grams = -1.0;
}



void Ingredient::display(void)
{
	std::cout << "\tING: " << Spice << std::endl;
	std::cout << "\tAMT: " << Amount << std::endl;
	std::cout << "\tMEAS: " << Measurement << std::endl;
}



bool Ingredient::isSpice(void)
{
	std::unordered_map<std::string, double>::const_iterator got = SpicetoWeight.find(Spice);
	if(got != SpicetoWeight.end())
	{
		calculateGrams();
		return true;
	}
	else
		return false;

}



void Ingredient::calculateGrams(void)
{
	std::cout << Spice << std::endl;
	std::cout << Measurement << std::endl;
	std::unordered_map<std::string, double>::const_iterator got1 = SpicetoWeight.find(Spice);
	std::unordered_map<std::string, double>::const_iterator got2 = MeasuretoTeaspoon.find(Measurement);
	if(got1 != SpicetoWeight.end() && got2 != MeasuretoTeaspoon.end())
		Grams = Amount * got1->second * got2->second;
 
	std::cout << Grams << std::endl;
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

double Ingredient::getGrams(void)
{
	return Grams;
}
