#include <iostream>
#include <string>
#include <fstream>

#include <sstream>
#include <stdlib.h>

void yoda(std::string str, int words)
{
	if (words > 0)
	{
		
		std::stringstream ss;
		ss << str;

		std::string prtstr;
		ss >> prtstr;

		str = ss.str();

		str = str.substr(prtstr.length()+1);
		yoda (str, words-1);

		std:: cout << prtstr << " " ;
	
	}

	
	return;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
	   std::cout << "Please provide an input file" << std::endl;
	   return -1;
    }

    std::ifstream input(argv[1]);
   
    int x;

    input >> x;

    std::string myline;
    std:: string s = "";
   for (int i = 0; i < x; i++)
   {
    	input >> myline;

   		s = s +myline + " ";
    }


    yoda(s, x);
    std:: cout<< std::endl;
    return 0;

}

