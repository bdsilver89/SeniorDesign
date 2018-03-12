#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <cstdint>
#include <string>
#include <vector>


/**
 * TODO:
 * Add types for ingredients and the measurements
 */



class Ingredient
{
private:
	double Amount;
	std::string Measurement;
	std::string Spice;

public:
	Ingredient(double a, std::string m, std::string t);

	/**
	 * [display description]
	 */
	void display(void);

	/**
	 * [getAmount description]
	 * @return  [description]
	 */
	double getAmount(void);

	/**
	 * [getMeasurement description]
	 * @return  [description]
	 */
	std::string getMeasurement(void);

	/**
	 * [getType description]
	 * @return  [description]
	 */
	std::string getType(void);
};

#endif
