
#include <iostream>
#include "recipe/ingredient.h"



Ingredient::Ingredient(double a, int m, std::string t)
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
	std::cout << "The measurement type is: " << MEASURE_LIST[Measurement] << std::endl;
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
int Ingredient::getMeasurementNum(void)
{
	return Measurement;
}


std::string Ingredient::getMeasurementStr(void)
{
    return MEASURE_LIST[Measurement];
}


/**
 * [Ingredient::getType description]
 * @return {int} [description]
 */
std::string Ingredient::getType(void)
{
	return Spice;
}
