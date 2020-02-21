/*
 * ReadFile.hpp
 *
 *  Created on: Feb 21, 2020
 *      Author: jochemlt
 */

#ifndef READFILE_HPP_
#define READFILE_HPP_

#include <vector>
#include <string>
#include <queue>


class FileReader {
public:
	FileReader(const std::string& inputFile);
	virtual ~FileReader();
	void readFile();
	const std::queue<std::pair<std::string, std::string> >& getInputQueue() const;

private:
	std::string inputFile;
	std::queue<std::pair<std::string, std::string>> inputQueue;
};

#endif /* READFILE_HPP_ */
