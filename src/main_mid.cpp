#include <string>
#include <iostream>

#include "midpoint_linked_list.hpp"

int main()
{
	midpoint_linked_list<int> mll;

	for(int i = 0; i < 9; ++i)
	{
		mll.append(i);
	}

	for(int i = 0; i < mll.size(); ++i)
	{
		std::cout << mll[i] << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	mll.append(999, 3);
	for(int i = 0; i < mll.size(); ++i)
	{
		std::cout << mll[i] << std::endl;
	}

	//std::cout << "check" << std::endl;
	//auto itr = mll.begin();
	//while(itr)
	//{
	//	std::cout << itr->t << std::endl;
	//	itr = itr->next;
	//}

}
