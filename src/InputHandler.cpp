#include "InputHandler.hpp"
#include <fstream>
#include <iostream>

InputHandler::InputHandler(ArgumentParser* argumentParser) : argumentParser(argumentParser) {
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

	if (myfile.is_open()) {
		while (std::getline(myfile, input)) {
            parseLine(input);
		}
        finishedFileReading = true;
	}
}

void InputHandler::readCommandLine() {
    std::string input;
    std::getline(std::cin, input);
    if(!input.empty()) {
        inputVectorMutex.lock();
        inputVector.clear();
        inputVectorMutex.unlock();
        parseLine(input);
    }
}

void InputHandler::start() {
    threadPtr = std::make_unique<std::thread>(&InputHandler::run, this);
}

void InputHandler::run() {
    if(argumentParser->getMode() == Mode::BATCH) {
        readFile(argumentParser->getLocation());
    }
    while(true) {
        readCommandLine();
    }
}

 std::vector<std::pair<std::string, std::string> >& InputHandler::getInputVector() {
    return inputVector;
 }

 std::mutex& InputHandler::getMutex() {
    return inputVectorMutex;
 }

 bool InputHandler::getFinishedFileReading() {
    return finishedFileReading;
 }