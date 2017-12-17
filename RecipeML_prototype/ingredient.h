#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>
#include <vector>


class Ingredient
{
private:
	double Amount;
	std::string Measurement;
	std::string Spice;

public:
	Ingredient(double a, std::string m, std::string s)
	{
		Amount = a;
		Measurement = m;
		Spice = s;
	}

	double getAmount(void)
	{
		return Amount;
	}

    std::string getMeasurement(void)
    {
    	return Measurement;
    }

	std::string getSpice(void)
	{
		return Spice;
	}
};

#endif