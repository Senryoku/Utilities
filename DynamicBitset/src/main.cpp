#include <iostream>
#include <list>

#include <time.h>

#include "DynamicBitset.hpp"

void debugDisplay(const DynamicBitset& DB)
{
	std::cout << " " << DB.size() << "\t" << DB.size() << "\t";
	for(const auto& b : DB)
		std::cout << b << " ";
	std::cout << std::endl;
}

int main(int argc, char** argv)
{
	std::cout << "---------------------------------------------------------------------------------"
	<< std::endl << " Count\tSize\tContent" << std::endl;
	std::cout << "---------------------------------------------------------------------------------"
	<< std::endl;
	
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
	}
	
	{
		int i = 0;
		auto arr = {true, true, false, false, true};
		DynamicBitset DB {arr};
		debugDisplay(DB);
		for(auto b : DB)
			if(b != arr.begin()[i++]) 
			{
				std::cerr << "[Line " << __LINE__ << "] Error on " << i << "." << std::endl;
				return 1;
			}
	}
	
	{
		int i = 0;
		auto arr = {false, true, false, false, true, true, false, false, true};
		DynamicBitset DB {arr};
		for(auto b : DB)
			if(b != arr.begin()[i++]) 
			{
				std::cerr << "[Line " << __LINE__ << "] Error on " << i << "." << std::endl;
				return 1;
			}
		debugDisplay(DB);
	}
	
	{
		DynamicBitset DB;
		DB.resize(5789, true);
		for(auto b : DB)
			if(!b) 
			{
				std::cerr << "[Line " << __LINE__ << "] Error." << std::endl;
				return 1;
			}
		DB.resize(647, true);
		for(auto b : DB)
			if(!b) 
			{
				std::cerr << "[Line " << __LINE__ << "] Error." << std::endl;
				return 1;
			}
		DB.resize(54, true);
		for(auto b : DB)
			if(!b) 
			{
				std::cerr << "[Line " << __LINE__ << "] Error." << std::endl;
				return 1;
			}
	}
	
	{
		DynamicBitset DB;
		DB.resize(6587, false);
		for(auto b : DB)
			if(b) 
			{
				std::cerr << "[Line " << __LINE__ << "] Error." << std::endl;
				return 1;
			}
		DB.resize(46874, false);
		for(auto b : DB)
			if(b) 
			{
				std::cerr << "[Line " << __LINE__ << "] Error." << std::endl;
				return 1;
			}
		DB.resize(56, false);
		for(auto b : DB)
			if(b) 
			{
				std::cerr << "[Line " << __LINE__ << "] Error." << std::endl;
				return 1;
			}
	}
	
	{
		DynamicBitset DB;
		for(int i = 14245; i >= 0; --i)
		{
			DB.resize(i);
			for(auto b : DB)
				(void) b;
		}
	}
	
	std::cout << "---------------------------------------------------------------------------------"
	<< std::endl;
	
	std::cout << "Tests succeeded." << std::endl;
	
	return 0;
}
