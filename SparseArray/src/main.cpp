#include <cstdlib>
#include <iostream>
#include <string>

#include "SparseArray.hpp"

int main(int argc, char** argv)
{
	SparseArray<std::string> SA;
	
	std::cout << SA;
	SA.insert(25, "Vingt-cinq");
	std::cout << SA;
	SA.insert(56, "Cinquante-six");
	std::cout << SA;
	SA.insert(25, "Vingt-cinq bis");
	std::cout << SA;
	SA.insert(28, "Vingt-huit");
	std::cout << SA;
	SA.insert(6887, "Beaucoup");
	std::cout << SA;
	SA.remove(28);
	std::cout << SA;
	SA.insert(4, "Quatre");
	std::cout << SA;
	SA.insert(658, "BeaucoupMaisMoins");
	std::cout << SA;
	SA[2344] = "Test";
	std::cout << SA;
	
	std::cout << "2344th element : " << SA[2344] << std::endl;
	
	return EXIT_SUCCESS;
}
