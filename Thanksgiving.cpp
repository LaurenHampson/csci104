#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include <utility>
#include <stdexcept>
#include <algorithm>//Using algorithm class only on question 5 
#include "LengthMismatch.h"


using namespace std;

string sizeChecker (int a, int b)
{
	if (a != b ) // if the sizes arent equal, through an error
	{
		throw LengthMismatch(a,b);
	}

	return "";
}



std::vector<std::pair<int, int> > assignPlates(std::vector<int> turkeys, std::vector<int> potatoes) 
	{
		try
		{ 
			//check to make sure that the lengths of the input vectors are equal
			std::cout<<sizeChecker(turkeys.size(), potatoes.size());
		}
		catch(LengthMismatch& o)
		{
			//if not equal lengths, out put the error message and exit the program
			std::cout<< o.what() << std::endl;
			std::vector<std::pair<int, int> > results;

				return results;
			

		}
		//Algorithm library sort function, iterator for beginning, and iterator for end
		std::sort(turkeys.begin(), turkeys.end());
		std::sort(potatoes.begin(), potatoes.end());
		

		std::vector<std::pair<int, int> > result;
		vector<int> sums;

		for (unsigned int i = 0; i < turkeys.size(); i++)
		{
			//add results from turkeys in ascending orderr and results from potatoes in descending order
			//in order to add the smallest from turkeys and largest from potatoes and so on 
			result.push_back(std::make_pair(turkeys[i], potatoes[potatoes.size()-1-i]));
			sums.push_back(turkeys[i]+potatoes[potatoes.size()-1-i]);
			if (i>=1)
			{
				if (sums[i] != sums[i-1]) // check if the sums are equal, if they arent, return an empty vector
				{
					std::vector<std::pair<int, int> > results;

					return results;
				}
			}

		}

	
		//return the vector of the paired dishes
		return result;

	}


