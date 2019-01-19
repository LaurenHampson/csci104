#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <cstring>
#include "querysearch.h"
#include "webpage.h"
#include "parser.h"
#include "lowercase.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc<4)
	{
		//std::cout << "No Index File" << std::endl;

		return -1;
	}

	QuerySearch* searcher = new QuerySearch();
	Parser* parse = new Parser();

	std::ifstream input(argv[1]);
	
	searcher->pageParser(input, parse);
	
	std::ifstream inQuery(argv[2]);

	std::ofstream output(argv[3]);

	std::string line;

	while(getline(inQuery, line))
	{
		//vector<string> split;
		searcher->query(line, output);

	}
		delete parse;
	delete searcher;
	input.close();
	inQuery.close();
	output.close();


	return 1;

	}

	
