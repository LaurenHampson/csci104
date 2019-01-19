#include "lliststr.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

void add (int pos, string str, LListStr* list)
{
	list->insert(pos, str);
	return;
}

void replace (int pos, string str, LListStr* list)
{
	list->set(pos, str);
	return;
}

void act (int pos, LListStr* list)
{
	
	if (list->size()>1 && pos == list->size()-1)
	{
		cout << "Assassinated: " << list->get(0) << endl;
		list->remove(0);
		act(pos, list);
	}
	else if (list->size() > 1 && (pos) <= (list->size())-2 && pos+1 <= list->size()-1 )
	{
	
		cout << "Assassinated: " << list->get(pos+1) << endl;
		list->remove(pos+1);
		act(pos, list);
	}

	return;

}

int main(int argc, char* argv[])
{
    if (argc < 2) {
	   cerr << "Please provide an input and output file" << endl;
	   return -1;
    }

    ifstream input(argv[1]);

    LListStr* list = new LListStr();

    string line;
    stringstream ss;
    while (getline(input, line))
   	{ 	
  	  	string cmmd;
  	  	ss << line;
  	  	ss >> cmmd;

  	  	if (cmmd == "ACT")
  	  	{
  	  		int pos;
  	  		ss >> pos;
  	  		act(pos, list);
  	  	}
  	  	if (cmmd == "REPLACE")
  	  	{
  	  		int pos;
  	  		string str;
  	  		ss >> pos >> str;
  	  		replace(pos, str, list);
  	  	}
  	  	if (cmmd == "ADD")
  	  	{
  	  		int pos;
  	  		string str;
  	  		ss >> pos >> str;

  	  		add(pos, str, list);
  	  	}

  	  	ss.clear();

    }

    if (list->size() == 1)
    {
    	cout << "Winner: " << list->get(0) <<endl;
    }

    else 
    {
    	cout << "Remaining Players: " << list->size() << endl;
    	for (int i = 0; i < list->size(); i++)
    	{
    		cout << list->get(i) << endl;
    	}
    }

    delete list;

 }

