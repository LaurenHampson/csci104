
#include <set>
#include <string>

template<class T>
 std::set<T> setIntersect(const std::set<T> &s1, std::set<T>& s)
{
	typename std::set<T> tempSet;
	typename  std::set<T>::iterator it = s1.begin();

	while(it!=s1.end())
	{
		if (s.count(*it)>0)
		{
			tempSet.insert(*it);
		}
		it++;
	}

	
	return tempSet;
		
}
template<class T>
 std::set<T> setUnion(const std::set<T> &s1, std::set<T>& s)
{
	 typename std::set<T> tempSet;
	 typename std::set<T>::iterator it = s1.begin();

	while(it!=s1.end())
	{
		
			tempSet.insert(*it);
	
		it++;
	}

	it = s.begin();

	while (it!=s.end())
	{
		tempSet.insert(*it);
		it++;
	}

	return tempSet;
}

