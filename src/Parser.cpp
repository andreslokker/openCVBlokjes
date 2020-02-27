/*
 * Parser.cpp
 *
 *  Created on: Feb 27, 2020
 *      Author: jochemlt
 */

#include "Parser.h"
#include <iostream>

Parser::Parser()
{
	// TODO Auto-generated constructor stub

}

Parser::~Parser()
{
	// TODO Auto-generated destructor stub
}

std::pair<std::string, std::string> Parser::parseString(std::string input)
{
	int count = 0;
	for (int i = 0; i < input.length(); i++)
	{
		if (isspace(input.at(i)))
		{
			count++;
		}
	}
	std::string shape;
	std::string color;

	if (count == 1)
	{
		bool shapeFound = false;
		for (unsigned short i = 0; i < input.length(); i++)
		{
			if (!shapeFound && !isspace(input.at(i)))
			{
				shape += input.at(i);
			}
			else if (shapeFound)
			{
				color += input.at(i);
			}
			else if (isspace(input.at(i)))
			{
				shapeFound = true;
			}
		}
		std::cout << "shape: " << shape << " color: " << color << std::endl;
	}
	else if (count == 2)
	{
		bool shapeFound = false;
		bool firstWhitespaceFound = false;
		for (unsigned short i = 0; i < input.length(); i++)
		{
			if (!shapeFound)
			{

				if (isspace(input.at(i)) && firstWhitespaceFound)
				{
					shapeFound = true;
				}
				if (isspace(input.at(i)))
					firstWhitespaceFound = true;
				shape += input.at(i);
			}
			else if (shapeFound)
			{
				color += input.at(i);
			}
		}
		std::cout << "shape: " << shape << " color: " << color << std::endl;
	}
	return std::pair<std::string, std::string>(shape, color);
}
