#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

class Parser
{
public:
    Parser(void);

	void displayFile(std::string inputFilePath);

	std::vector<std::string> split(std::string, std::string);

    int getMeasurement(std::vector<std::string>::const_iterator s);

    double getAmount(std::vector<std::string>::const_iterator s);

    bool checkAmountType(std::vector<std::string>::const_iterator s);

    bool checkMeasureType(std::vector<std::string>::const_iterator s);

	void parseNewFile(std::string inputFilePath);

    void parseSavedFile(void);
};


#endif