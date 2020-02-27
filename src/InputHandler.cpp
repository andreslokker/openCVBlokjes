#include "InputHandler.hpp"
#include <fstream>
#include <iostream>

InputHandler::InputHandler(std::mutex* inputQueueMutex) : inputQueueMutex(inputQueueMutex), thread1(&InputHandler::run, this) {

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
    inputQueueMutex->lock();
    inputQueue.push(std::make_pair(shape, color));
    inputQueueMutex->unlock();
}

void InputHandler::readFile(const std::string& filename) {
    std::ifstream myfile(filename);
	std::string input;
	if (myfile.is_open()) {
		while (std::getline(myfile, input)) {
            parseLine(input);
		}
	}
}

void InputHandler::readCommandLine() {
    std::string input;
    std::getline(std::cin, input);
    parseLine(input);
}

void InputHandler::run() {
    while(true) {
        readCommandLine();
    }
}


 std::queue<std::pair<std::string, std::string> >& InputHandler::getInputQueue() {
    return inputQueue;
 }