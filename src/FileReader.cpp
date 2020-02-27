/*
 * ReadFile.cpp
 *
 *  Created on: Feb 21, 2020
 *      Author: jochemlt
 */

#include "FileReader.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>


FileReader::FileReader()
{
}

FileReader::FileReader(const std::string& inputFile) :
		inputFile(inputFile)
{
}

FileReader::~FileReader()
{
}

void FileReader::readFile()
{
	std::ifstream myfile(inputFile);
	std::string input;
	if (myfile.is_open())
	{
		while (std::getline(myfile, input))
		{
			input = input.substr(0, input.find("#"));
			inputQueue.push(parser.parseString(input));
		}
	}
}


const std::queue<std::pair<std::string, std::string> >& FileReader::getInputQueue() const
{
	return inputQueue;
}
