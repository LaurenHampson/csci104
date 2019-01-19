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
#include <algorithm>
#include <vector>
#include "setutility.h"

using namespace std;



void QuerySearch::candidateExpand(std::set<std::string>& set, std::ofstream& output, const float restartProb, float iters)
{
	//expand the set of the query adding the incoming and outgoing links of each element to the prexisting set as well
	std::set<std::string> tempSet = set;
	std::set<std::string>::iterator pass = tempSet.begin();
	while(pass != tempSet.end())
	{
		std::map<std::string, WebPage *>::iterator finder = fileWebPageMap.find(*pass);
				std::set<std::string> sets = (finder->second)->incomingLinks();
		std::set<std::string>::iterator temp = sets.begin();
		while (temp != sets.end())
		{
			set.insert(*temp);
			temp++;
		}

			std::set<std::string> sets2 = (finder->second)->outgoingLinks();
		std::set<std::string>::iterator temp2 = sets2.begin();
		while (temp2 != sets2.end())
		{

			set.insert(*temp2);
			temp2++;
		}

		pass++;
	}

//below is a loop that instantiates the in degree and  out degree map of each element in set, used later in PR
	std::set<std::string>::iterator deg = set.begin();
	while(deg!=set.end())
	{

		int inNum = 0;
		int outNum = 0;


		std::map<std::string, WebPage *>::iterator wps = fileWebPageMap.find(*deg);
		(wps->second)->outAdd(*deg);
		(wps->second)->incomingLink(*deg);


		std::set<std::string> outs = (wps->second)->outgoingLinks();


			std::set<std::string>::iterator linker = outs.begin();

		while(linker!=outs.end())
		{
			std::set<std::string>::iterator finder = set.find(*linker);
			if (finder != set.end())
			{
				outNum += 1;

			}

			linker++;


		}

		std::set<std::string> ins = (wps->second)->incomingLinks();


		
		linker = ins.begin();
		while(linker!=ins.end())
		{

			std::set<std::string>::iterator finder = set.find(*linker);
			if (finder != set.end())
			{

				inNum += 1;
			}

			linker++;
		}


	
		inOutDegMap.insert(std::make_pair(*deg, std::make_pair(inNum, outNum)));

		deg++;
	}

	float initProb = (1/((double)set.size()));
	// the initial proability for each node

	std::set<std::string>::iterator count = set.begin();
	//initialize the page name to probability map updated in each recursize call of PR
	while(count!=set.end())
	{

		pageProbMap.insert(std::make_pair(*count, initProb));
		count ++;
	}


	//output << set.size() << std::endl;

	pageRank(set, restartProb, iters, initProb);
	


	std::vector<std::pair<float, std::string> > tempProb;

	//instantiate a vector equivalent to the probability map in order to sort through it using <algorithm>
	std::map<std::string, float>::iterator iter = pageProbMap.begin();
	while(iter!= pageProbMap.end())
	{
		tempProb.push_back(std::make_pair(iter->second, iter->first));
		iter++;
	}


	std::sort(tempProb.begin(), tempProb.end());
	std::reverse(tempProb.begin(), tempProb.end());
	output << tempProb.size() << std::endl;
	for (unsigned int i = 0; i < tempProb.size(); i++)//output rank files to the output file
	{
		output << tempProb[i].second << std::endl;//<< " " <<  tempProb[i].first << std::endl;
	}

	//output << std::endl;			

	pageProbMap.clear();
	tempProbMap.clear();
	inOutDegMap.clear();
	return;

}

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

void QuerySearch::pageRank(const std::set<std::string> set, const float prob, float steps, const float initProb)//std::map<std::string, float>& temp, std::map<std::string, float>& prob,)
{
	if (steps == 0.0)
	{
		return;
	}
	float probs = 1 - prob;

	float chances = prob * initProb;

	std::set<std::string>::iterator it1 = set.begin();
	//get first element of the set

	while(it1 != set.end())//for each element of the set
	{
		float sum = 0; // new sum for summation, later added to temporary probability map


		std::map<std::string, WebPage *>::iterator wps = fileWebPageMap.find(*it1);
		//find the webpage object of each element in the set in order too get its incoming links


		std::set<std::string> tempSet = (wps->second)->incomingLinks();
		//iterate throguh the inc links making sure they too are in the candidate set
		std::set<std::string>::iterator it2 = tempSet.begin();

		while(it2!= tempSet.end())
		{
			std::set<std::string>::iterator setFin = set.find(*it2);

			if (setFin != set.end())
				{
				std::map<std::string, float>::iterator it3 = pageProbMap.find(*it2);
				

				std::map<std::string, pair< int, int > >::iterator it4 = inOutDegMap.find(it3->first);

				int outDeg = (it4->second).second;
				//find its out degree

				float tempProd = ((it3->second) /((double) outDeg));
				//aply to the formula, update the summation

				sum +=tempProd;
			}
			
			it2++;
		}

		sum = sum*(probs);
		sum = sum + chances;
		//final steps of the formula
		tempProbMap.insert(std::make_pair(*it1, sum));
		//add to a temp map in orde rto avoid messing up the previous probabilities

		it1++;
	}

	pageProbMap.clear();
	std::map<std::string, float>::iterator it5 = tempProbMap.begin();
	while (it5 != tempProbMap.end())
	{

		pageProbMap.insert(std::make_pair(it5->first, it5->second));
		//update final probability map

		it5++;
	}



	tempProbMap.clear();
	//recurse;

	pageRank(set, prob, (steps-1), initProb);

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

						if (iter == wordFilesMap.end())
						{
							std::set<std::string> str;
							str.insert(name);
							wordFilesMap.insert(std::make_pair(word, str));	
						}

						else 
						{
							iter->second.insert(name);
							
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

void QuerySearch::search(const std::string n, std::ofstream &output, const float restartProb, const float iters)
{

	std::map<std::string, std::set<std::string> >::iterator it = wordFilesMap.find(n);
	std::set<std::string> words = it->second;

	
	if (words.size() == 0)
	{
		output << words.size() << std::endl;
		return;
	}
  
	else
	{
		
		candidateExpand(words, output, restartProb, iters);
	}
	return;


}


void QuerySearch::andQ(std::vector<string> &q, std::ofstream &output, const float restartProb, const float iters)
{
	std::set<std::string> set = searcher(lowerCase(q[1]));
	
	if (q.size()>2)
	{for (unsigned int i = 1; i < q.size(); i++)
		{
			std::set<std::string> temp = searcher(lowerCase(q[i]));
			
				
				set = setIntersect(set, temp);
			
			
		}
	}
	if (set.size() == 0)
	{
		output << set.size() << std::endl;
		return;
	}

	else
	{
		candidateExpand(set, output, restartProb, iters);
	}
	return;
		
		
}
	
void QuerySearch::orQ(std::vector<string> &q, std::ofstream &output , const float restartProb, const float iters)
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
		if (set.size() == 0)
	{
		output << set.size() << std::endl;
		return;
	}

	else
	{
		
		candidateExpand(set, output, restartProb, iters);

	}
	return;
		
		
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

int QuerySearch::query (const std::string n, const float restartProb, const float iters, std::ofstream &output)	
{
	std::vector<string> split;

	splits(n, split, ' ');

	split[0] = lowerCase(split[0]);

	if (split.size() == 1)
	{
		search(split[0], output, restartProb, iters);
		return 0;
	}

	if (split[0] == "and")
	{
		andQ(split, output, restartProb, iters);
		return 0;
	}
	
	if (split[0] == "or")
	{
		orQ(split, output, restartProb, iters);
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