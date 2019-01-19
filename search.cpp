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

std::vector<std::string> splits(const std::string s, std::vector<string>& temp, char delimiter);
void configure(std::ifstream& input, std::map<std::string, std::string>& files);

int main(int argc, char *argv[])
{
	std::ifstream in;
	if (argc<2) // if no file name is passed in use the designated file in your directory
	{
		in.open("config.txt");
		
	}

	else // open the file passed in
	{
		in.open(argv[1]);
	}

	std::map<std::string, std::string> files;
	
	configure(in, files);// configure the input argument

	std::map<std::string, std::string>::iterator it = files.find("INDEX_FILE");
	string indexFile = "";
	if (it != files.end())
	{
		indexFile = (it->second); // find the name of the index file
	}

	std::ifstream index(indexFile);

	it = files.find("OUTPUT_FILE");

	string outputFile = "";
	if (it!= files.end())
	{
		outputFile = it->second; // find the name of the output file
	}

	std::ofstream output(outputFile);

	it = files.find("QUERY_FILE");
	string queryFile = "";
	if (it!= files.end())
	{
		queryFile = it->second;// find the name of the query file
	}


	std::ifstream query(queryFile);

	
	

	it = files.find("RESTART_PROBABILITY");
	
	float restartProb;
	if(it != files.end())
	{
		stringstream ss;
		string probStr = it->second;
		ss << probStr;

		

		ss >> restartProb; // get the restart probability

		ss.str("");
		ss.clear();
	}

	
	it = files.find("STEP_NUMBER");
	float iters;

	if (it!= files.end())
	{
		stringstream ss;
		string stepNum = it -> second;
		ss << stepNum;

		
		ss >> iters; // get the number of times to update the probabilitity

		ss.str("");
		ss.clear();
	}

	



	QuerySearch* searcher = new QuerySearch();
	Parser* parse = new Parser();

	
	searcher->pageParser(index, parse);
	
	
	std::string line;

	while(getline(query, line)) // do each query in the query input file
	{
		int num = searcher->query(line, restartProb, iters, output);
		if (num == -1)
		{
			output << "Invalid Query" << std::endl;
		}

	}
	delete parse;
	delete searcher;
	in.close();
	index.close();
	output.close();
	query.close();


	return 0;

	}

void configure(std::ifstream& input, std::map<std::string, std::string>& files)
{
std::string temp;
	while(std::getline(input, temp))
	{


		std::string fileType = "";
		bool typeFound = false;

		std::string file = "";

	
		stringstream ss(temp);
		char c;

		while (ss >>c)
		{
			if (c == '#') // if you hit a comment, there is no longer a need to keep reading the line
			{
				break;
			}
			
			if(isspace(c))//if the current character is a space go to the next character and ignore it
			{
				continue;
			}

			if(c == '=')//if you reach an equals sign, you have found the string name of a stream file
			{
				typeFound = true;
				continue;
			}



			if(typeFound == false)//if you havent found the string file yet, update the word the fileName maps to (e.g. INDEX_FILE --> index.txt)
			{
				fileType += c;
			}
			else // if you have already found the equals sign, you now have to update the name of the file stream
			{
				if(!isspace(c)) // make sure you are not adding random spaces to the output file name
					file += c;
			}

		}

		files.insert(std::make_pair(fileType, file)); // add to the files map passed in

	

	}


}		