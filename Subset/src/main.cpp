#include <iostream>
#include <list>

#include <time.h>

#include "Subset.hpp"

void debugDisplay(const Subset& SS)
{
	std::cout << " " << SS.count() << "\t" << SS.size() << "\t";
	for(unsigned int i = 0; i < SS.count(); ++i)
		std::cout << SS.pop() << " ";
	std::cout << std::endl;
}

int main(int argc, char** argv)
{

	return 0;
}
