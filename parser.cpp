#include "parser.h"
#include <fstream>
#include <ctype.h>
#include <queue>
#include <set>
#include <iostream>
#include <string>


#include "lowercase.h"

using namespace std;

	Parser::Parser()
	{

	}
	Parser::~Parser()
	{

	}

	void addLink(std::ifstream& in, std::set<std::string>& words, std::set<std::string>& links)
	{
		string output = "";
		char c;
		
		while(in.get(c))
				{
					if ((isdigit(c)) || (isupper(c)) || (islower(c)))
					{
						output+= c;
					}
					
					else if (c == ']')
					{
						

						words.insert(lowerCase(output));
						output = "";

						break;
					}
					else if (output != "" && isspace(c))
					{
						while(in.get(c) && isspace(c))
						{

						}
						words.insert(lowerCase(output));

						output = "";
						if ((isdigit(c)) || (isupper(c)) || (islower(c)))
						{
						
							output += c;
						}
					}
					else if (output != "")
					{
						words.insert(lowerCase(output));
						output = "";
					}

					
				

				}
			
				in.get(c);
					
					if (c == '(') // start reading link
					{
						string link = "";

						getline(in, link, ')');

						links.insert(link);
						link = "";
						return;
						
					}

			}
		
		
	void Parser::parse(std::string filename, std::set<std::string>& words, std::set<std::string>& links) //update the contents of a webpage
	{
		ifstream in(filename);

		
		string output = "";
		char c;

		//uses markdown format to get any outgoing links from each input file

		while(in.get(c))
		{

			if ((isdigit(c)) || (isupper(c)) || (islower(c)))
			{
				output += c;
				continue;
			}
			
			else if (output != "" && isspace(c))
			{
				while(in.get(c) && isspace(c))
				{

				}
				words.insert(lowerCase(output));
				output = "";
				if ((isdigit(c)) || (isupper(c)) || (islower(c)))
				{
				
					output += c;
				}
			}
			else if (output != "")
			{
				words.insert(lowerCase(output));
				output = "";
			}
			if (c == '[')
			{
				
				addLink(in, words, links);
			}
			


		}

		if (output!= "")
		{
			words.insert(lowerCase(output));
		}
			in.close();
		}

