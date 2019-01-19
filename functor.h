#ifndef FUNCTOR_H
#define FUNCTOR_H

#include <string>
#include <map>



	struct NumStrComp
	{
		public:
			bool operator()(const std::string& lhs, const std::string& rhs);
			
		private:
			std::map<char, int> lookUp;
	};

#endif