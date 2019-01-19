#include<queue>
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include <exception>
#include <cstdlib>
#include <utility>
#include <math.h>


using namespace std;

void aStar(std::priority_queue<pair<std::string, int> >& path, std::vector<std::string>& nodes, int& expansions);

int calculateHValue(std::string n)
{
    unsigned int count = 0;

	for(unsigned int i = 0; i < n.size(); i++)
    {
    	if(n[i] == 0)
    	{
    		count++;
    	}
    }
    return count;

}
bool isValid(std::string curr, std::string next)
{
    // Returns true if row number and column number
    // is in range
    unsigned int count = 0;
    for(unsigned int i = 0; i < curr.size(); i++)
    {
    	if(curr[i]!= next[i])
    	{
    		count++;
    	}
    }

    if (count > 1)
    {
    	return false;
    }
    else
    {
    	return true;
    }
}

bool isDestination(std::string curr)
{
	   unsigned int count = 0;

	for(unsigned int i = 0; i < curr.size(); i++)
    {
    	if(curr[i] == 1)
    	{
    		count++;
    	}
    }

    if (count == curr.size())
    {
    	return true;
    }

    else
    {
    	return false;
    }


}
 

int main(int argc, char *argv[])
{
	//std::ifstream in;
	if (argc<3) // if no file name is passed in use the designated file in your directory
	{
		std::cout << "Not Enough Arguments" << std::endl;		
	}

	std::ifstream in(argv[2]);

	std::stringstream ss;

	ss << argv[1];


	std::string startNode;

	ss >> startNode;

	ss.str("");
	ss.clear();
	

	std::vector<std::string> nodes;
	nodes.push_back(startNode);

	std::string line;
	while(getline(in, line))
	{
		ss << line; 

		std::string newLine;
		ss >> newLine;

		nodes.push_back(newLine);

		ss.str("");
		ss.clear();
	}

	//int expansions = 0;
	//int g = 0;
	std::priority_queue<pair<std::string, int> > path;
	path.push(std::make_pair(startNode, 0));

	//aStar(path, nodes, expansions);


	return 0;

	}
