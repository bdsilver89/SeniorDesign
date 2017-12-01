#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>
#include <vector>


const std::vector<std::string> MEASURE_LIST {
	"oz",
	"tbsp",
	"tsp",
	"cup"
};


typedef enum
{
	MEASURE_OZ,
	MEASURE_TBSP,
    MEASURE_TSP,
	MEASURE_CUP
} MEASURE_TYPE;



class Ingredient
{
private:
	double Amount;
	int Measurement;
	std::string Spice;

public:
	Ingredient(double a, int m, std::string t);

	void display(void);

	double getAmount(void);

	int getMeasurementNum(void);

    std::string getMeasurementStr(void);

	std::string getType(void);
};

#endif