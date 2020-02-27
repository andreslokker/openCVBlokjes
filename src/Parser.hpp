/*
 * Parser.h
 *
 *  Created on: Feb 27, 2020
 *      Author: jochemlt
 */

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <string>

class Parser
{
public:
	Parser();
	virtual ~Parser();
	std::pair<std::string, std::string> parseString(std::string input);
};

#endif /* PARSER_H_ */
