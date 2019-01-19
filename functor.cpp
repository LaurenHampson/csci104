#include "functor.h"
#include <string>
#include <sstream>
#include <map>
#include <iostream>

using namespace std;


		bool NumStrComp::operator()(const string& lhs, const string& rhs)
		{
			//initialize map with proper values for each character
				lookUp.insert(std::make_pair('0',0 ));
				lookUp.insert(std::make_pair('1',1 ));
				lookUp.insert(std::make_pair('2',2 ));
				lookUp.insert(std::make_pair('3',3 ));
				lookUp.insert(std::make_pair('4',4 ));
				lookUp.insert(std::make_pair('5',5 ));
				lookUp.insert(std::make_pair('6',6 ));
				lookUp.insert(std::make_pair('7',7 ));
				lookUp.insert(std::make_pair('8',8 ));
				lookUp.insert(std::make_pair('9',9 ));
				lookUp.insert(std::make_pair('a',10 ));
				lookUp.insert(std::make_pair('A',10 ));
				lookUp.insert(std::make_pair('b',11 ));
				lookUp.insert(std::make_pair('B',11 ));
				lookUp.insert(std::make_pair('c',12 ));
				lookUp.insert(std::make_pair('C',12 ));
				lookUp.insert(std::make_pair('d',13 ));
				lookUp.insert(std::make_pair('D',13 ));
				lookUp.insert(std::make_pair('e',14 ));
				lookUp.insert(std::make_pair('E',14 ));
				lookUp.insert(std::make_pair('f',15 ));
				lookUp.insert(std::make_pair('F',15 ));
				lookUp.insert(std::make_pair('g',16 ));
				lookUp.insert(std::make_pair('G',16 ));
				lookUp.insert(std::make_pair('h',17 ));
				lookUp.insert(std::make_pair('H',17 ));
				lookUp.insert(std::make_pair('i',18 ));
				lookUp.insert(std::make_pair('I',18 ));
				lookUp.insert(std::make_pair('j',19 ));
				lookUp.insert(std::make_pair('J',19 ));
				lookUp.insert(std::make_pair('k',20 ));
				lookUp.insert(std::make_pair('K',20 ));
				lookUp.insert(std::make_pair('l',21 ));
				lookUp.insert(std::make_pair('L',21 ));
				lookUp.insert(std::make_pair('m',22 ));
				lookUp.insert(std::make_pair('M',22 ));
				lookUp.insert(std::make_pair('n',23 ));
				lookUp.insert(std::make_pair('N',23 ));
				lookUp.insert(std::make_pair('o',24 ));
				lookUp.insert(std::make_pair('O',24 ));
				lookUp.insert(std::make_pair('p',25 ));
				lookUp.insert(std::make_pair('P',25 ));
				lookUp.insert(std::make_pair('q',26 ));
				lookUp.insert(std::make_pair('Q',26 ));
				lookUp.insert(std::make_pair('r',27 ));
				lookUp.insert(std::make_pair('R',27 ));
				lookUp.insert(std::make_pair('s',28 ));
				lookUp.insert(std::make_pair('S',28 ));
				lookUp.insert(std::make_pair('t',29 ));
				lookUp.insert(std::make_pair('T',29 ));
				lookUp.insert(std::make_pair('u',30 ));
				lookUp.insert(std::make_pair('U',30 ));
				lookUp.insert(std::make_pair('v',31 ));
				lookUp.insert(std::make_pair('V',31 ));
				lookUp.insert(std::make_pair('w',32 ));
				lookUp.insert(std::make_pair('W',32 ));
				lookUp.insert(std::make_pair('x',33 ));
				lookUp.insert(std::make_pair('X',33 ));
				lookUp.insert(std::make_pair('y',34 ));
				lookUp.insert(std::make_pair('Y',34 ));
				lookUp.insert(std::make_pair('z',35 ));
				lookUp.insert(std::make_pair('Z',35 ));
			
			//parse through both the lhs and rhs by each character and add its value according to the
			//map to the sum


			int sum1 = 0;
			int sum2 = 0;

			stringstream leftss;
			leftss << lhs;
			char a;
			std::map<char,int>::iterator it;
			while (leftss>>a)
			{
			

				it = lookUp.find(a);

				if (it != lookUp.end())
				{
					sum1 += it->second;
				}

			}

			leftss.clear();
			leftss.str("");

			stringstream rightss;
			rightss << rhs;
			char b;

			while (rightss>>b)
			{
				
				it = lookUp.find(b);

				if (it != lookUp.end())
				{
					sum2 += it->second;
				}
			}

			rightss.clear();
			rightss.str("");

			//if the sums are different, the work is done
			if (sum1 > sum2)
			{
				return false;
			}

			else if (sum1 < sum2)
			{
				return true;
			}
			
			//if the sums are equal we need to sort lexicographically
			else
			{
				bool checker = false;
				
				
				leftss << lhs;
				rightss << rhs;

				char x;
				char y;

				int size1 = lhs.length();
				int size2 = rhs.length();

				int len = 0;
				if(size1 >= size2)
				{
					len = size2;
				}

				else
				{
					len = size1;
				}

				int i = 0;

				// if at any point x>y return false, and if at any point x <y return true
				while (checker == false && i < len)
				{
					leftss>>x;
					rightss>>y;

					if (x > y)
					{
						
						checker = true;
						leftss.clear();
						leftss.str("");
						rightss.clear();
						rightss.str("");

						return false;

						break;
					}

					if (x<y)
					{
						checker = true;
						leftss.clear();
						leftss.str("");
						rightss.clear();
						rightss.str("");

						return true;

						break;	
					}

					i++;

				}
	
			//check one last time, if the strings are completley equal, return false
				if (checker == false && size1 == size2)
				{
					leftss.clear();
					leftss.str("");
					rightss.clear();
					rightss.str("");

					return false;
				}
				else if (checker == false && size1 < size2)
				{
					leftss.clear();
					leftss.str("");
					rightss.clear();
					rightss.str("");

					return true;
				}
				else 
				{
					leftss.clear();
					leftss.str("");
					rightss.clear();
					rightss.str("");

					return false;
				}

				
				
			}


		}


