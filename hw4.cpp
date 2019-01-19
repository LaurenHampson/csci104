#include "querysearch.h"
#include "lowercase.h"
#include "webpage.h"
#include <stdio.h>
#include <ctype.h>
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <exception>
#include <set>
#include <map>
#include <iterator>
#include <vector>

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
	
		void QuerySearch::pageParser (std::ifstream &input, Parser* parser) // read in new file from the input
		{
					
			std:: string name;
			while(std::getline(input, name))
			{
					std::set<std::string> words;
					std::set<std::string> links;

					parser->parse(name, words, links);

					WebPage* page = new WebPage(name);
					page->getWords(words);

					std::set<std::string>::iterator i;
					for (i = links.begin(); i != links.end(); i++)
					{
						page->outgoingLink(*i);
					}

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
			//std::set<std::string>::iterator out = it->second->printWords().find(n);
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
/*void QuerySearch::setMaker(const std::string n, std::set<string> &s )
{
	

	std::map<std::string, WebPage *>::iterator it = fileWebPageMap.begin();
			
		while( it !=fileWebPageMap.end())
		{
			std::set<std::string> outSet = it->second->printWords();
			//std::set<std::string>::iterator out = it->second->printWords().find(n);
			if (outSet.find(n) != outSet.end())
			{
				s.insert(it->first);
			}
			it++;
			
		}

}*/
std::set<string> QuerySearch::intersection(std::set<string> &s1, std::set<string> &s2)
{
	std::set<string> tempSet;
	std::set<string>::iterator it = s1.begin();

	while(it!=s1.end())
	{
		if (s2.count(*it)>0)
		{
			tempSet.insert(*it);
		}
		it++;
	}

	it = s2.begin();
	while(it!=s2.end())
	{
		if (s1.count(*it) > 0)
		{
			tempSet.insert(*it);
		}
		it++;
	}

	return tempSet;
		/*std::set<string>::iterator it;
		for (it = s2.begin(); it != s2.end(); it++)
		{
			std::set<string>::iterator temp = s1.find(*it);
			if (temp == s1.end())
			{
				s2.erase(it);
			}
		}
		return;*/
}
void QuerySearch::andQ(std::queue<string> &q, std::ofstream &output)
{
	
	std::set<string> intersect;

	std::map<std::string,std::set<std::string> >::iterator it = wordFilesMap.find(lowerCase(q.front()));
	if (it!= wordFilesMap.end())
	{
		intersect = it->second;
	}

	//setMaker(lowerCase(q.front()), intersect);
	q.pop();
	/*if (q.size() == 0)
	{
		std::set<string>::iterator it;
		output << intersect.size() << std::endl;
		for (it = intersect.begin(); it != intersect.end(); it++)
		{
			output << *it << std::endl;
		}

		return;
	}

	else
	{*/
		while(q.size() > 0)
		{
			std::set<string> tempSet;
			//setMaker(lowerCase(q.front()), tempSet);

	//std::set<string> tempSet;

	std::map<std::string,std::set<std::string> >::iterator it = wordFilesMap.find(lowerCase(q.front()));
	if (it!= wordFilesMap.end())
	{
		tempSet = it->second;
	}
			q.pop();
			intersect = intersection(tempSet, intersect);

		}
		if (q.size() == 0)
		{
			std::set<string>::iterator it;
			output << intersect.size() << std::endl;
			for (it = intersect.begin(); it != intersect.end(); it++)
			{
				output << *it << std::endl;
			}

			return;
		}
	//}

}
void QuerySearch::orQ(std::queue<string> &q, std::ofstream &output)
{
	std::set<string> intersect;
	while (q.size()>0)
	{
		std::map<std::string,std::set<std::string> >::iterator it = wordFilesMap.find(lowerCase(q.front()));
	if (it!= wordFilesMap.end())
	{
		intersect = it->second;
	}

	//setMaker(lowerCase(q.front()), intersect);
	
		q.pop();
	}

	if (q.size() == 0)
		{
			std::set<string>::iterator it;
			output << intersect.size() << std::endl;
			for (it = intersect.begin(); it != intersect.end(); it++)
			{
				output << *it << std::endl;
			}

			return;
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
		}
	}	

	return;
}

/*void QuerySearch::printPage(std::string n, std::ofstream &output)
{
	output << n << std::endl;


	while()
}*/

int QuerySearch::query (const std::string n, std::queue<string> &q, std::ofstream &output)	
{
	if (n == "and")
	{
		andQ(q, output);
		return 0;
	}
	if (n == "or")
	{
		orQ(q, output);
		return 0;
	}
	
	if (n == "incoming")
	{
		inc(q.front(), output);
		q.pop();
		return 0;

	}
	if (n == "outgoing")
	{
		out(q.front(), output);
		q.pop();
		return 0;
	}
	if (n == "print")
	{
		return 0;
	}
	
	return -1;
	
}