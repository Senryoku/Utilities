#include "Wobble.hpp"
#include "Counter.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
	Wobble W(0.f, 10.f, 0.5f, 0.1f);
	
	for(unsigned int i = 0; i < 100; ++i)
		std::cout << W << std::endl;
	
	std::cout << std::endl << "Reseting..." << std::endl << std::endl;
	W.reset();
	
	for(unsigned int i = 0; i < 100; ++i)
		std::cout << W << std::endl;
	
	/*
	Counter C = Counter(2, 2, 8, 1);
	
	for(unsigned int i = 0; i < 100; ++i)
		std::cout << C.step() << std::endl;
	*/
	
	return 0;
}
