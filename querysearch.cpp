#include "querysearch.h"
#include "lowercase.h"
#include "webpage.h"
#include <stdio.h>
#include <ctype.h>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <exception>
#include <set>
#include <map>
#include <iterator>
#include <vector>
#include "setutility.h"

using namespace std;


QuerySearch::QuerySearch()
{

}

QuerySearch:: ~QuerySearch()
{
	std::map<std::string, WebPage *>::iterator iter = fileWebPageMap.begin();
	while(iter != fileWebPageMap.end())
	{
		delete iter->second;
		iter++;
	}
	fileWebPageMap.clear();
	wordFilesMap.clear();
}


		void QuerySearch::pageParser (std::ifstream &input, Parser* parser) 
		{
					
			std::string name;

			while(std::getline(input, name))
			{
					std::set<std::string> words;
					std::set<std::string> links;


					parser->parse(name, words, links);
					WebPage* page = new WebPage(name);
					page->getWords(words);
					page->outgoingLink(links);

					fileWebPageMap.insert(std::make_pair(name, page));

					std::set<std::string>:: iterator x;
					for (x = words.begin(); x!= words.end(); x++)
					{
						std::string word = *x;
						word = lowerCase(word);
						std::map<std::string, std::set<std::string> >::iterator iter = wordFilesMap.find(word);

						if (iter != wordFilesMap.end())
						{
							iter->second.insert(name);
						}

						else 
						{
							std::set<std::string> str;
							str.insert(name);
							wordFilesMap.insert(std::make_pair(word, str));
						}
					}
					words.clear();
					links.clear();
				
			}
			std::map<std::string, WebPage *>::iterator it;
			
			for (it = fileWebPageMap.begin(); it !=fileWebPageMap.end(); it++)
			{
				std::set<string> outgoing = it->second->outgoingLinks();
				std::set<std::string>::iterator out = outgoing.begin();
				
				while(out !=outgoing.end())
				{
					std::map<std::string, WebPage *>::iterator inc = fileWebPageMap.find(*out);
					if (inc != fileWebPageMap.end())
					{
						(inc->second)->incomingLink(it->first);
					}
					out++;
				}
				outgoing.clear();
			}



		}

void QuerySearch::search(const std::string n, std::ofstream &output)
{
	int count = 0;
	vector<string> pages;

	std::map<std::string, WebPage *>::iterator it;
			
		for (it = fileWebPageMap.begin(); it !=fileWebPageMap.end(); it++)
		{
			std::set<std::string> outSet = it->second->printWords();
			if (outSet.find(n) != outSet.end())
			{
				pages.push_back(it->first);
				count++;
			}
			
		}

	output<< count << endl;

	for (unsigned int i = 0; i < pages.size(); i++)
	{
		output<<pages[i]<< endl;
		
	}
	return;


}

std::set<std::string> QuerySearch::searcher(const std::string n)
{
	
	set<string> pages;


	std::map<std::string, std::set<std::string> >::iterator it = wordFilesMap.find(n);

	if (it != wordFilesMap.end())
	{
		pages = it->second;
	}
		

		return pages;

}

void QuerySearch::andQ(std::vector<string> &q, std::ofstream &output)
{
	std::set<std::string> set = searcher(lowerCase(q[1]));
	
	if (q.size()>2)
	{for (unsigned int i = 1; i < q.size(); i++)
		{
			std::set<std::string> temp = searcher(lowerCase(q[i]));
			
				
				set = setIntersect(set, temp);
			
			
		}
	}

		std::set<string>::iterator it;
				output << set.size() << std::endl;
				for (it = set.begin(); it != set.end(); it++)
				{
					output << *it << std::endl;
				}
				
		
		
}
	
void QuerySearch::orQ(std::vector<string> &q, std::ofstream &output)
{
	std::set<std::string> set;
	for (unsigned int i = 1; i < q.size(); i++)
		{
			std::set<std::string> temp = searcher(lowerCase(q[i]));
			if(i ==1)
				{
					set = temp;
				}
				set = setUnion(set, temp);
		}

		std::set<string>::iterator it;
				output << set.size() << std::endl;
				for (it = set.begin(); it != set.end(); it++)
				{
					output << *it << std::endl;
				}
		
	}

void QuerySearch::inc(std::string n, std::ofstream &output)
{
	std::map<std::string, WebPage *>::iterator it = fileWebPageMap.find(n);
	
	if (it != fileWebPageMap.end())
	{
		

		std::set<string> incoming = it->second->incomingLinks();
		std::set<std::string>::iterator out = incoming.begin();
		output << incoming.size() << std::endl;
		while (out != incoming.end())
		{
			output << *out << std::endl;
			out++;
		}
	}	

	return;
}

void QuerySearch::out(std::string n, std::ofstream &output)
{

	std::map<std::string, WebPage *>::iterator it = fileWebPageMap.find(n);
	
	if (it != fileWebPageMap.end())
	{
		std::set<string> outgoing = it->second->outgoingLinks();
		std::set<std::string>::iterator out = outgoing.begin();
		output << outgoing.size() << std::endl;
		while (out != outgoing.end())
		{
			output << *out << std::endl;
			out++;
		}
	}	

	return;
}

std::vector<std::string> splits(const std::string s, std::vector<string>& temp, char delimiter) {

  	std::stringstream ss;

   	ss << s;

   	std::string line;



  	while(getline(ss, line, delimiter))
  	{

   		temp.push_back(line);

   	}

   	ss.str("");
   	ss.clear();

   	return temp;

}

std::vector<std::string> printsplits(const std::string s, std::vector<string>& temp) {

  	std::stringstream ss;

   	ss << s;

   	std::string line;


while(getline(ss, line, '('))
  	{

   		temp.push_back(line);
   		ss.ignore(256, ')');
   		
   		
   	}
  

   	ss.str("");
   	ss.clear();

   	return temp;

}


	void QuerySearch::print(const std::string n, std::ofstream &output)
	{
		output << n << std::endl;
		std::ifstream in(n);
		std::string line;
		while(std::getline(in, line))
		{
			std::vector<string> split;

			printsplits(line, split);

			for (unsigned int i = 0; i <split.size(); i++)
			{
				output << split[i];
			}

			
			output << std::endl;
		}
		
		
		

			in.close();
	}

int QuerySearch::query (const std::string n, std::ofstream &output)	
{
	std::vector<string> split;

	splits(n, split, ' ');

	split[0] = lowerCase(split[0]);

	if (split.size() == 1)
	{
		search(split[0], output);
		return 0;
	}

	if (split[0] == "and")
	{
		andQ(split, output);
		return 0;
	}
	
	if (split[0] == "or")
	{
		orQ(split, output);
		return 0;
	}
	
	if (split[0] == "incoming")
	{
		inc(split[1], output);
		return 0;
	}
	if(split[0] == "outgoing")
	{
		out(split[1], output);
		return 0;
		
	}
	

if (split[0] == "print")
	{
		print(split[1], output);
		return 0;
	}

	return -1;
	
}