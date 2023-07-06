#include "./vector.h"
#include <iostream>


int main()
{
	utils::vector<int> s(1, 2);
	s.push_back(1);
	for (size_t i = 0; i < s.size(); i++)
	{
		std::cout << s[i] << " ";
	} 
	return 0;
}
