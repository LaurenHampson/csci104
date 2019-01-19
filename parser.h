#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <set>
#include <fstream>
#include "webpage.h"




class Parser {

   
public:

	Parser();
	~Parser();

	void parse(std::string filename, std::set<std::string>& words, std::set<std::string>& links) ;



};

#endif