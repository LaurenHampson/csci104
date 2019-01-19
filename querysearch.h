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
		int query (const std::string n,  const float restartProb, const float iters,  std::ofstream &output);
		void search(const std::string n, std::ofstream &output, const float restartProb, const float iters);
		std::set<std::string> searcher(const std::string n);
		void pageRank(const std::set<std::string> set, const float prob, float steps, const float initProb);
		void andQ(std::vector<std::string> &q, std::ofstream &output, const float restartProb, const float iters);
		void orQ(std::vector<std::string> &q, std::ofstream &output, const float restartProb, const float iters);
		void inc(std::string n, std::ofstream &output);
		void out(std::string n, std::ofstream &output);
		void print(const std::string n, std::ofstream &output);
		void candidateExpand(std::set<std::string>& set, std::ofstream& output, const float restartProb, float iters);
	
	private:
		std::map<std::string, std::set<std::string> > wordFilesMap; 
		std::map<std::string, WebPage *> fileWebPageMap;
		std::map<std::string, float> pageProbMap;
		std::map<std::string, float> tempProbMap;
		std::map<std::string, std::pair<int, int> > inOutDegMap; 
};

#endif