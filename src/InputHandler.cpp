#include "InputHandler.hpp"
#include <fstream>
#include <iostream>

InputHandler::InputHandler(std::mutex* inputQueueMutex) :
		inputQueueMutex(inputQueueMutex), thread1(&InputHandler::run, this), mode("interactiveMode")
{

}

InputHandler::~InputHandler()
{

}

void InputHandler::parseLine(const std::string& line)
{
	if(line == "exit")
	{
		std::exit(0);
	}
	std::string input = line.substr(0, line.find("#"));
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
	}
	inputQueueMutex->lock();
	inputQueue.push(std::make_pair(shape, color));
	inputQueueMutex->unlock();
}

void InputHandler::readFile(const std::string& filename)
{
	std::ifstream myfile(filename);
	std::string input;
	if (myfile.is_open())
	{
		while (std::getline(myfile, input))
		{
			parseLine(input);
		}
	}
}

void InputHandler::readCommandLine()
{
	std::string input;
	std::getline(std::cin, input);
	parseLine(input);
}

void InputHandler::run()
{
	while (true)
	{
		if(mode == "interactiveMode") readCommandLine();
		if(mode == "batchMode") readFile(inputFile);

	}
}

std::queue<std::pair<std::string, std::string> >& InputHandler::getInputQueue()
{
	return inputQueue;
}

void InputHandler::setMode(const std::string& mode)
{
	this->mode = mode;
}

void InputHandler::setInputFile(const std::string& inputFile)
{
	this->inputFile = inputFile;
}
