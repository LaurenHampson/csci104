#include <fstream>

#include <iostream>

#include "stackstr.h"

//#include <stack>

#include <map>

#include <string>

#include <sstream>

#include <stdlib.h>



using namespace std;

// > remove first character of the string unless it is only one characer
// < remove end character of string unless the string is only one character
// + append second string ot the end of the first string
// r- rermove the first instance of the second string from the first string 
// (the first string is returned unmodified if there is no match)

/*Any string of 1 or more letters a-z (lower-case only) is a string expression.
If Y1, Y2, ..., Yk are string expressions (for k > 1) then the following are string expressions: 
	<Y1
	>Y1
	(Y1-Y2)
	(Y1+Y2+Y3+...+Yk)*/

//only lower ase letters
// dont worry about precendence

// white space betweeen expressions

/*

(<<dagobah -(>>yoda+go )) // evaluates to b
<> <<<((eve + boo+buzz)  -  >< <nemo) // evaluates to eboo
<>((<<mario + >>zelda)- ><samus) // evaluates to arld
><<de // evaluates to d
((<mccoy+sulu)    // missing parenthesis
(leonardo-foot+splinter)   // mixing operators
(+pikachu+charizard)    // extra +
(clARk + bruCE)    // the strings use capital letters

*/

// check if valid
//then operate on it


// takes two parameters --> input filename in which the formula is stored, second is the output filename


//malformed if invalid
	// check parentheses number
	// check upper case or lower case
	// check number of total strings
	// check if more + than strings or if they are =
	//check if empty

//return string if valid

// dont use recursion

string toString (char c)
{
	stringstream ss;
	string s;

	char a = c;
	ss << a;
	ss>>s;

	return s;
}

int malformed(string &str)
// if not malformed return 0
// if malformed return -1
{
	//check if empty
	stringstream ss(str);
	if (ss.str().size() == 0)
	{
		return -1;
	}
	//check for the right amount of parentheses
	StackStr* s = new StackStr;
	stringstream word(str);
	int len = word.str().size();

	for (int i = 0; i < len; i++)
	{
		char c;
		word >> c;
		
		
		if (s->empty() && c == ')')
		{
			delete s;
			return -1;
		}
		else if (c == '(')
		{
			
			s->push("(");
		}
		else if (c == ')' && s->top()!= "(")
		{
			delete s;
			return -1;
		}

		else if (c == ')' && s->top()== "(")
		{
			s->pop();
		}
		
	}

	delete s;


	// check for capital letters
	/*StackStr* s2 = new StackStr;
	stringstream word2(str);
	int len2 = word2.str().size();

	for (int i = 0; i < len2; i++)
	{
		char c;
		word2 >> c;
		
		if (c < 'a' || c>'z' )
		{
			cout << "line 144" << endl;

			delete s2;
			return -1;
		}
		
	}


	delete s2;*/
	// check if mixed operators in parentheses
		StackStr* s3 = new StackStr;

	stringstream word3(str);
	int len3 = word3.str().size();

	for (int i = 0; i < len3; i++)
	{
		char c;
		word3 >> c;
		string sC = "" + toString(c);
			
		
		s3->push(sC);

		if (c == '+' && (s3->empty() || s3->top() == "(" || s3->top() == "-"))
		{
			delete s3;
			return -1;
		}

		else if (c == '-' && (s3->empty() || s3->top() == "(" || s3->top() == "+" ))
		{
			delete s3;
			return -1;
		}
		
	}

	delete s3;
	return 0;

}

string evaluateExpression(string &str)
{
	StackStr* s1 = new StackStr;
	stringstream word1(str);
	int len1 = word1.str().size();


		bool notWord = false;
		
		for ( int k = 0; k < len1; k++)
		{
			char cs;
			word1 >>cs;
			if (cs <'a' || cs > 'z')
			{
				notWord = true;
			}
		}
		
		if(notWord == false)
		{
			delete s1;
			return str;
		}

	delete s1;

StackStr* s = new StackStr;
	stringstream word(str);
	int len = word.str().size();

	string tempWord = "";
	string result = "";

	int i = 0;
	while(i < len)
	{
		char c;
		word >> c;

		if (c>='a' && c<='z')
		{
			
			
			//while(c >= 'a' && c <= 'z')//&&(s->top()== "("||(cs >= 'a' && cs <='z')|| s->top() == "+" || s->top() == "-" || s->top() == ">" || s->top() == "<") && i < len)
			//{
				tempWord+= toString(c);
				i++;
				word >> c;

			//}

			

			 while(((s->top()!= "(") && (s->top() !=")") && (s->top() != "+" ) &&( s->top() != "-" ))&&( tempWord.size() > 1) && (i))
			{
				if (c == '<')
				{
					len--;
					tempWord = tempWord.substr(0, tempWord.size()-2);
				}
				else 
				{
					len--;
					tempWord = tempWord.substr(1, tempWord.size()-2);
				}	
			}

		
			if (result == "")
			{
				result += tempWord;
				s->push(result);
				tempWord = "";
			}

			else
			{
				if (s->top() == "+")
				{
					result+=tempWord;	
				}
				else if (s->top() == "-")
				{
					for (unsigned int i = 0; i <result.size(); i++)
					{	
						if (tempWord.size()>=1)
						{
							for(unsigned int x = 0; x < tempWord.size(); x++ )
							{
								if (result[i] == tempWord[x])
								{
									if (i == 0)
									{
										result = result.substr(1,result.size()-2);
										if (x == 0)
										{
											tempWord = tempWord.substr(1,result.size()-2);
										}
										else if (x == tempWord.size()-1)
										{
											tempWord = tempWord.substr(0, tempWord.size()-2);
										}
										else
										{
											tempWord = tempWord.substr(0, x) +tempWord.substr(x+1, tempWord.size()-(x+2));
										}
									}

									else if (i == result.size()-1)
									{
										result = result.substr(0, result.size()-2);
										
										if (x == 0)
										{
											tempWord = tempWord.substr(1,result.size()-2);
										}
										else if (x == tempWord.size()-1)
										{
											tempWord = tempWord.substr(0, tempWord.size()-2);
										}
										else
										{
											tempWord = tempWord.substr(0, x) +tempWord.substr(x+1, tempWord.size()-(x+2));
										}
									}

									else
									{
										result = result.substr(0, i) + result.substr(i+1,result.size()-(i+2));
										if (x == 0)
										{
											tempWord = tempWord.substr(1,result.size()-2);
										}
										else if (x == tempWord.size()-1)
										{
											tempWord = tempWord.substr(0, tempWord.size()-2);
										}										
										else
										{
											tempWord = tempWord.substr(0, x) +tempWord.substr(x+1, tempWord.size()-(x+2));
										}
									}
								
								}
							}
						}
					}
					
				}

			}

		}

			else

			{
				string sC = "";
				sC+= c;
				s->push(sC);

				i++;
			}
				
		}

	
		

		
			
	while (!s->empty())
	{
		
		if (s->top() == ">" && result.size()>1)
		{
			result = result.substr(1, result.size()-2);
		}
		else if (s->top() == "<" && result.size() >1)
		{
			result = result.substr(0, result.size()-2);
		
		}
			
		s->pop();
	}

	delete s;

return result;

	


	}

	

	







int main(int argc, char *argv[])
{
	// check argument count
	if (argc < 3)
	{
		cout << "Not enough arguments " << endl;
		return 0;
	}

	ifstream input(argv[1]);

	if (input.fail())
	{
		cout << "Invalid input file, can not open" << endl;
		return 0;
	}

	ofstream output(argv[2]);
	if (output.fail())
	{
		cout << "Invalid output file, can not open" << endl;
		return 0;
	}

	string myline;

	while(getline (input, myline))
	{

		stringstream ss(myline);
		string s = ss.str();

		if (s.size() == 0)
		{
			output << "Malformed" << endl;
		}

		
		else

		{
			int x = malformed(s);
		
			if (x == -1)
			{
				output << "Malformed" << endl;
			}
	
			else 
			{
				string str = evaluateExpression(s);
	
				output << str << endl;
			}
		}
	}

	return 0;


}