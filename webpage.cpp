
#include <queue>
#include <fstream>
#include <iostream>

#include <set>
#include <iterator>
#include <exception>
#include "webpage.h"
#include "parser.h"
#include "lowercase.h"

using namespace std;


/*		WebPage::WebPage() // constructor
		{

		}*/
		WebPage::WebPage(std::string filename) // webpage constructor if user passes in a file name
		{
			this->filename(filename);
		}
		WebPage::~WebPage() // destructor, nothing to do here
		{
			this->wordSet_.clear();
			this->incoming_.clear();
			this->outgoing_.clear();
			this->filename("");
		}
		void WebPage:: getWords(std::set<std::string>& words) // sets all of the words in a webpage to a set
		{
			//copy the sets differently
			std::set<std::string>::iterator i;
			for (i = words.begin(); i != words.end(); i++)
			{
				wordSet_.insert(lowerCase(*i));
			}
			//wordSet_ = words;
		}
		void WebPage::filename(std::string name) // set the file name of the web page if not given at contruction
		{
			filename_ = name;
		}

		std::string WebPage::filename() // print the filename of a webpage
		{
			return filename_;
		}
		const std::set<std::string>&  WebPage:: printWords()  // returns all words in a given webpage
		{
			return wordSet_;
		}
		void WebPage::incomingLink (const std::string name) // add new incoming link to a webpage
		{
			incoming_.insert(name);
		}
		const std::set<std::string>& WebPage::incomingLinks() //const; // return all incoming links for a given webpage
		{
			return incoming_;
			
		}
		void WebPage::outgoingLink (std::set<std::string>& words) // add new outgoing link to a webpages set
		{
			std::set<std::string>::iterator i;
			for (i = words.begin(); i != words.end(); i++)
			{
				outgoing_.insert(lowerCase(*i));
			}
		}
		const std::set<std::string>& WebPage::outgoingLinks() //const; // return all of the outgoing links from a given webpage
		{
			return outgoing_;			
		}	


		//check map
		//check intersect and union
		//check where i am passing information from one function to another