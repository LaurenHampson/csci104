#include "lowercase.h"
#include <cstring>
#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <exception>
#include <set>
#include <iterator>

using namespace std;


// string lowerCase(string word)//make word lowercase for easier comparison
// {

// 	char *cstr = new char[word.length() + 1];
// 	std::copy(word.begin(), word.end(), cstr);

// 	cstr[word.length()] = '\0';
// 	//int n = sizeof(cstr) / sizeof(cstr[0]);
	
// 	char c;
// 	int i = 0;
// 	while(cstr[i])
// 	{
// 		c = cstr[i];
// 		//putchar(tolower(c));

// 		i++;
// 	}

// 	string str(cstr);

	
// 	delete [] cstr;

// 	return str;
// }

string lowerCase(string word)
{
	string temp = word;
	for(unsigned int i = 0; i < temp.size(); i++)
	{
		temp[i] = tolower(temp[i]);
	}
	return temp;
}