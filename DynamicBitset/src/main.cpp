#include <iostream>
#include <list>

#include <time.h>

#include "DynamicBitset.hpp"

void debugDisplay(const DynamicBitset& DB)
{
	std::cout << DB.count() << "\t" << DB.size() << "\t";
	for(unsigned int i = 0; i < DB.count(); ++i)
		std::cout << DB.get(i) << " ";
	std::cout << std::endl;
}

int main(int argc, char** argv)
{
	DynamicBitset DB;
	
	DB.push_back(true);
	if(!DB.get(0)) return 1;
	debugDisplay(DB);
	DB.push_back(false);
	if(DB.get(1)) return 1;
	debugDisplay(DB);
	DB.push_back(true);
	if(!DB.get(2)) return 1;
	debugDisplay(DB);
	DB.push_back(false);
	if(DB.get(3)) return 1;
	debugDisplay(DB);
	DB.push_back(true);
	if(!DB.get(4)) return 1;
	debugDisplay(DB);
	
	DB.resize(15);
	debugDisplay(DB);
	DB.reserve(20);
	debugDisplay(DB);
	DB.resize(32, true);
	debugDisplay(DB);
	
	
	return 0;
}
