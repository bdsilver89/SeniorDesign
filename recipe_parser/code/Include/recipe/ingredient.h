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
	Ingredient(double a, std::string m, std::string t);

	void display(void);

	double getAmount(void);

	std::string getMeasurement(void);

	std::string getType(void);
};

#endif