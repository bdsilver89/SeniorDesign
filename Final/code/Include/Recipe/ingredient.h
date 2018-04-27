#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <cstdint>
#include <string>
#include <vector>


class Ingredient
{
private:
	double Amount;
	double Grams;
	std::string Measurement;
	std::string Spice;

public:
	double PourTime;	//in hundreds of milliseconds

	Ingredient(double a, std::string m, std::string t);

	/**
	 * [display description]
	 */
	void display(void);

	/**
	 * [calculateSpice description]
	 */
	void calculateSpice(void);

	/**
	 * [isSpice description]
	 * @return  [description]
	 */
	bool isSpice(void);

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
	
	/**
	 * [getGrams description]
	 * @return  [description]
	 */
	double getGrams(void);
	
};

#endif
