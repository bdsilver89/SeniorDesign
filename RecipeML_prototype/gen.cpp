#include <iostream>
#include <fstream>
#include <vector>
#include "ingredient.h"


void displayXML(std::string inputFilePath)
{
	std::string line;
	std::ifstream InputFile(inputFilePath);

	if (InputFile.is_open())
	{
	    while (getline(InputFile, line))
        {	
            std::cout << line << std::endl;
        }
    InputFile.close();
    }

    else
    {
        std::cout << "Could not open XML file" << std::endl;
    }
}


void writeRecipe(std::string name, std::vector<Ingredient> list)
{
	std::string filePath = name;
	filePath.append(".xml");
    std::ofstream File(filePath);
    if (File.is_open())
    {
    	File << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    	File << "<!DOCTYPE recipeml PUBLIC \"-//FormatData//DTD RecipeML 0.5//EN\"\n";
    	File << "\t\"http://www.formatdata.com/recipeml.recipeml.dtd\">\n";
    	File << "<?xml-stylesheet href=\"dessert1.css\" type=\"text/css\"?>\n";
		File << "<recipeml version=\"0.5\">\n";
		File << "\t<recipe>\n";
		File << "\t\t<head>\n";
		File << "\t\t\t<title>";
		File << name << "</title>\n";
		File << "\t\t</head>\n";
		File << "\t\t<ingredients>\n";

	    for(std::vector<Ingredient>::iterator i = list.begin(); i != list.end(); ++i)
	    {
	        File << "\t\t\t<ing>\n";
	        File << "\t\t\t\t<amt>\n";
	        File << "\t\t\t\t\t<qty>" << (*i).getAmount() << "</qty>\n";
	        File << "\t\t\t\t\t<unit>" << (*i).getMeasurement() << "</unit>\n";
	        File << "\t\t\t\t</amt>\n";
	        File << "\t\t\t\t<item>" << (*i).getSpice() << "</item>\n";
	        File << "\t\t\t</ing>\n";
	    }

		File << "\t\t</ingredients>\n";

		File << "\t</recipe>\n";
		File << "</recipeml>";
        File.close();
    }

    else
    {
        std::cout << "Could not write recipe" << std::endl;
    }
}



int main(int argc, char const *argv[])
{
	std::vector<Ingredient> IngredientList;
	std::string input;
	std::cout << "Which recipe to write?" << std::endl;
	std::cin  >> input;

	Ingredient A(2  , "cups", "flour");
	Ingredient B(1  , "tsp" , "salt");
	Ingredient C(0.5, "oz"  , "butter");

	IngredientList.push_back(A);
	IngredientList.push_back(B);
	IngredientList.push_back(C);


	writeRecipe(input, IngredientList);

	//displayXML(input);
	return 0;
}




