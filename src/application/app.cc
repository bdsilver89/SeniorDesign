#include <iostream>
#include <string>
#include <stdlib.h>
#include "parser.h"


int main(int argc, const char *argv[])
{
    std::cout << "\n\nSenior Design SW Test Program"     << std::endl;
    std::cout << "Author: Brian Silver, Kyle Emanuele\n" << std::endl;


    std::string in;
    int choice;
    Parser P;    

    while(1)
    {
        std::cout << "Press '1' to parse a new recipe"      << std::endl;
        std::cout << "Press '2' to read in existing recipe" << std::endl;
        std::cout << "Anything else to quit"                << std::endl;
        std::cin  >> choice;

        switch (choice)
        {
            case 1:
                std::cout << "What is the path to the file?" << std::endl;
                std::cin  >> in;
                P.parseNewFile(in);
                break;

            case 2:
                P.parseSavedFile();
                break;

            default:
                exit(1);
                break;

        }

        std::cout << "========================================" << std::endl;
    }
    return 0;
}