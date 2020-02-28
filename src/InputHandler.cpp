#include "InputHandler.hpp"
#include <fstream>
#include <iostream>

InputHandler::InputHandler(ArgumentParser* argumentParser) : argumentParser(argumentParser) {
}

InputHandler::~InputHandler() {

}

void InputHandler::parseLine(const std::string& line) {
    if(line.find("#") != std::string::npos) {
        return;
    }
    std::string input = line.substr(0, line.length());
    int count = 0;
    for (int i = 0; i < input.length(); i++) {
        if (isspace(input.at(i))) {
            count++;
        }
    }
    std::string shape;
    std::string color;
    if(count == 0) {
        shape = input;
    } else if (count == 1) {
        shape = input.substr(0, input.find(" "));
        color = input.substr(input.find(" ") + 1);
    } else if (count == 2) {
        shape = input.substr(0, input.find(" ") + input.find(" ") + 2);
        color = input.substr(input.find(" ") + input.find(" ") + 3);

    }
    
    if(shape != "" || color != "") {
        inputVectorMutex.lock();
        inputVector.push_back(std::make_pair(shape, color));
        inputVectorMutex.unlock();
    }
}

void InputHandler::readFile(const std::string& filename) {
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