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

FileReader::FileReader(const std::string& inputFile) : inputFile(inputFile) {
	// TODO Auto-generated constructor stub

}

FileReader::~FileReader() {
	// TODO Auto-generated destructor stub
}


void FileReader::readFile() {
	std::ifstream myfile(inputFile);
	std::string input;
	if (myfile.is_open()) {
		while (std::getline(myfile, input)) {
			input = input.substr(0, input.find("#"));
			int count = 0;
			for (int i = 0; i < input.length(); i++) {
				if (isspace(input.at(i))) {
					count++;
				}
			}
			std::string shape;
			std::string color;
			if (count == 1) {
				shape = input.substr(0, input.find(" "));
				color = input.substr(input.find(" ") + 1);
			} else if (count == 2) {
				shape = input.substr(0, input.find(" ") + input.find(" ") + 2);
				color = input.substr(input.find(" ") + input.find(" ") + 3);

			}
			inputQueue.push(std::make_pair(shape, color));
		}
	}
}

const std::queue<std::pair<std::string, std::string> >& FileReader::getInputQueue() const {
	return inputQueue;
}
