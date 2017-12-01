#include <iostream>
#include <string>
#include <stdlib.h>
#include "recipe/parser.h"


int main(int argc, const char *argv[])
{
    std::string in;
    int choice1, choice2;
    Parser P;  
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "Senior Design SW Test Program"     << std::endl;
    std::cout << "Author: Brian Silver, Kyle Emanuele\n" << std::endl;  

    while(1)
    {
        std::cout << "Press '1' to select a recipe" << std::endl;
        std::cout << "Press '2' to edit"            << std::endl;
        std::cout << "Anything else to quit"        << std::endl;
        std::cin  >> choice1;

        switch (choice1)
        {
            case 1:
                std::cout << "Press '1' for a new recipe"   << std::endl;
                std::cout << "Press '2' for a saved recipe" << std::endl;
                std::cin  >> choice2;

                switch(choice2)
                {
                    case 1:
                        std::cout << "Which recipe file?" << std::endl;
                        std::cin >> in;
                        P.parseNewFile(in);
                        break;

                    case 2:
                        std::cout << "Which recipe?" << std::endl;
                        std::cin >> in;
                        P.parseSavedFile(in);
                        break;
                }
                break;

            case 2:
                std::cout << "Device config stuff" << std::endl;
                break;

            default:
                exit(1);
                break;

        }

        std::cout << "========================================" << std::endl;
    }
    return 0;
}