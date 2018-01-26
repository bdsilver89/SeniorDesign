#include <iostream>
#include <string>
#include <stdlib.h>
#include "recipe/parser.h"
#include "hardware/motor.h"
#include "hardware/weight.h"

#include <vector>


int main(int argc, const char *argv[])
{
    std::string in;
    int choice;
    Parser P;  
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "Senior Design SW Test Application"     << std::endl;
    std::cout << "Author: Brian Silver, Kyle Emanuele\n" << std::endl;  

    while(1)
    {
        std::cout << "Press '1' to read a recipe"      << std::endl;
        std::cout << "Press '2' to write a new recipe" << std::endl;
        std::cout << "Anything else to quit"           << std::endl;
        std::cin  >> choice;

        switch (choice)
        {
            case 1:
                {
                    std::cout << "Which recipe?" << std::endl;
                    std::cin  >> in;
                    std::vector<Ingredient> Ing = P.parseFile(in);
                    for(std::vector<Ingredient>::iterator s = Ing.begin(); s != Ing.end(); ++s)
                    {
                        (*s).display();
                        std::cout << std::endl;
                    }

                    // 
                    // std::cout << "Press '1' for a new recipe"   << std::endl;
                    // std::cout << "Press '2' for a saved recipe" << std::endl;
                    // std::cin  >> choice2;

                    // switch(choice2)
                    // {
                    //     case 1:
                    //         std::cout << "Which recipe file?" << std::endl;
                    //         std::cin >> in;
                    //         P.parseNewFile(in);
                    //         break;

                    //     case 2:
                    //         std::cout << "Which recipe?" << std::endl;
                    //         std::cin >> in;
                    //         P.parseSavedFile(in);
                    //         break;
                    break;
                }

            case 2:
                {
                    std::vector<Ingredient> list;
                    for(int i = 0; i < 4; i++)
                    {
                        double amount;
                        std::string measurement;
                        std::string spice;
                        
                        std::cout << "What ingredient?" << std::endl;
                        // std::getline(std::cin, spice);
                        std::cin  >> spice;

                        std::cout << "What measurement?" << std::endl;
                        // std::getline(std::cin, measurement);
                        std::cin  >> measurement;

                        std::cout << "How much?" << std::endl;
                        std::cin  >> amount;

                        Ingredient I(amount, measurement, spice);
                        list.push_back(I);
                        std::cout << std::endl;
                    }
                    std::cout << "What is the name of the recipe?" << std::endl;
                    std::cin  >> in;
                    P.writeFile(in, list);
                    break;
                }

            default:
                exit(1);
                break;

        }

        std::cout << "========================================" << std::endl;
    }
    return 0;
}