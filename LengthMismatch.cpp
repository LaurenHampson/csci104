#include "LengthMismatch.h"

#include <string>
#include <sstream>

#include <stdexcept>



LengthMismatch::LengthMismatch(int x, int y) //throw()
{
	std::string a;
	std::string b;

	std::stringstream one;
	std::stringstream two;

	one << x;
	one >> a;

	two << y;
	two >> b;

	one.clear();
	one.str("");
	two.clear();
	two.str("");
	
	 msg = ("Input data structures have lengths " + a + " and " + b );
}