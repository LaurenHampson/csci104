#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <stack>
#include <set>
#include <sstream>
#include <cstring>


using namespace std;


void configure(std::ifstream& input, std::map<std::string, std::string>& crawlfiles);

std::string findLink(std::string s) // use to find the link , used esentially the same code as my parser.cpp
{
	stringstream ss;
	ss << s;
	std::string link = "";
	char c;
	while (ss >> c)
	{
		if (c == '[')
		{
			ss >> c;
			while (c!= '(')
			{
				ss >> c;
			}
			ss >> c;
			while (c != ')')
			{
				link += c;
				ss >> c;
			}
		}
	}

	return link;
}
void DFS(std::ifstream& in, std::set<std::string>& found, std::vector<std::string>& links) // a DFS crawl through the files in a set
{	
	std::string line;
	
	while(getline(in, line))
	{

		std::string link = findLink(line);

		std::set<std::string>::iterator it = found.find(link);
		if(it == found.end())
		{
			found.insert(link);
			links.push_back(link);
			std::ifstream temp(link);
			DFS(temp, found, links);
			temp.close();
		}
	}	
	
	

	return;
}

int main(int argc, char *argv[])
{
	std::ifstream input;
	if (argc<2) //default config file if no argument passed in
	{
		input.open("config.txt");
		
	}

	else//open the input argument
	{
		input.open(argv[1]);
	}
	
	std::map<std::string, std::string> crawlfiles;
	
	configure(input, crawlfiles); // configure

	std::map<std::string, std:: string>::iterator it = crawlfiles.find("INDEX_FILE");
	string indexFile = "";
	if (it != crawlfiles.end())
		indexFile = (it->second);
	std::ifstream index(indexFile);//read in index file

	it = crawlfiles.find("OUTPUT_FILE");

	string outputFile = "";
	if (it!= crawlfiles.end())
		outputFile = it->second;

	std::ofstream output(outputFile); // read in output file

	std::set<std::string> found;
	std::vector<string> links;
	
	std::string line;
	while (getline(index, line))
	{
		links.push_back(line);
		std::ifstream in(line);
		DFS(in, found, links); // call crawler on each elemnt of the input 
		in.close();
	}
	
	for (unsigned int i = 0; i < links.size(); i++)
	{
		output << links[i] << std::endl;
	}


	
	index.close();
	output.close();


	return 0;

	}


void configure(std::ifstream& input, std::map<std::string, std::string>& crawlfiles)
{
std::string temp;
	while(std::getline(input, temp))
	{


	

		std::string file = "";
			std::string fileType = "";
		bool typeFound = false;

	
		stringstream ss(temp);
		char c;

		while (ss >>c)
		{
			if (c == '#') // if you see a comment exit that loop through/move to next
			{
				break;
			}
			
			if(isspace(c)) // if it is a space go to the next character
			{
				continue;
			}

			if(c == '=') // if you see an equal, now you can get the input file name
			{
				typeFound = true;
				continue;
			}



			if(typeFound == false) // if you havent found the equal sign yet, continue to update the string name of the stream file
			{
				fileType += c;
			}
			else //if you have found the equal, update the string name
			{
				if(!isspace(c)) // check to make sure it isnt a space
					file += c;
			}

		}

		crawlfiles.insert(std::make_pair(fileType, file));

	

	}


}		