#include <iostream>
#include <list>

#include <time.h>

#include "DynamicBitset.hpp"

void debugDisplay(const DynamicBitset& DB)
{
	for(unsigned int i = 0; i < DB.count(); ++i)
		std::cout << DB.get(i) << " ";
	std::cout << std::endl;
}

int main(int argc, char** argv)
{
	DynamicBitset DB;
	
	DB.push_back(true);
	debugDisplay(DB);
	DB.push_back(false);
	debugDisplay(DB);
	DB.push_back(true);
	debugDisplay(DB);
	DB.push_back(false);
	debugDisplay(DB);
	DB.push_back(true);
	debugDisplay(DB);
	
	DB.resize(32);
	debugDisplay(DB);
	DB.resize(64, true);
	debugDisplay(DB);
	
	
	return 0;
}
