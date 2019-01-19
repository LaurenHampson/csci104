#ifndef QUERYSEARCH_H
#define QUERYSEARCH_H

#include <map>
#include <vector>
#include <string>
#include <queue>
#include "webpage.h"
#include "parser.h"
#include <stdio.h>
#include <ctype.h>
#include <cstring>
#include <string>
#include <exception>
#include <set>
#include <iterator>



class QuerySearch
{
	public:
		QuerySearch();
		~QuerySearch();
		
		void pageParser (std::ifstream &input, Parser* parser);
		int query (const std::string n,  std::ofstream &output);
		void search(const std::string n, std::ofstream &output);
		std::set<std::string> searcher(const std::string n);//, std::set<std::string> &strings);
	
		void andQ(std::vector<std::string> &q, std::ofstream &output);
		void orQ(std::vector<std::string> &q, std::ofstream &output);
		void inc(std::string n, std::ofstream &output);
		void out(std::string n, std::ofstream &output);
		void print(const std::string n, std::ofstream &output);
	
	private:
		std::map<std::string, std::set<std::string> > wordFilesMap; // maybe change from word to webpage
		std::map<std::string, WebPage *> fileWebPageMap;
};

#endif