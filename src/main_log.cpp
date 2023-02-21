#include <iostream>
#include <string>
#include <memory>

#include "log_linked_list.hpp"

int main()
{
	log_linked_list<int> bar;

	std::cout << "before append:" << std::endl;
	std::cout << "\tsize: " << bar.size() << std::endl;
	std::cout << "\t [0]: " << bar[0] << std::endl;
	std::cout << std::endl;

	bar.append(420);

	std::cout << "after append:" << std::endl;
	std::cout << "\tsize: " << bar.size() << std::endl;
	std::cout << "\t [0]: " << bar[0] << std::endl;
	std::cout << std::endl;

	return 0;
}
