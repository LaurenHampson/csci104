#ifndef WEBPAGE_H
#define WEBPAGE_H
#include <string>
#include <iostream>
#include <iterator>
#include <set>
#include <fstream>

class WebPage
{
	public:
		//WebPage();
		WebPage(std::string filename);
		~WebPage();
		void getWords(std::set<std::string>& words);
		const std::set<std::string>& printWords(); 
		void incomingLink (const std::string name);
		const std::set<std::string>& incomingLinks(); 
		void outgoingLink (std::set<std::string>& words);
		const std::set<std::string>&  outgoingLinks(); 		
		std::string filename();
		void filename(std::string name);
				void outAdd(std::string word);




	protected:
		std::set<std::string>  outgoing_;
		std::set<std::string>  incoming_;
		std::set<std::string> wordSet_;
		std::string filename_;

};

#endif