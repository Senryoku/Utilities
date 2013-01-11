#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>

#include "AVL.hpp"

int main(int argc, char** argv)
{
	clock_t start, end;
	srand(time(NULL));
	AVL<double> Cerisier;

	unsigned int NB = 1000000;
	start = clock();
	for(unsigned int i = 0; i < NB; i++)
	{
		Cerisier.insert((double)(rand()%100000)/10);
	}
	end = clock();
	std::cout << NB << " insertions en " << (double) (end - start) / (double) CLOCKS_PER_SEC << " seconde(s)" << std::endl;
	
	if(NB <= 100) Cerisier.toGraph("Graph.gv");
	
	std::ofstream File("Test.txt");
	if(File.good())
	{
		File << "# NbElements Temps(s)" << std::endl;
		Cerisier.clear();
		unsigned int Incr = 100;
		unsigned int Max = 10000;
		unsigned int NbInsert = 1000000;
		for(unsigned int Curr = 0; Curr <= Max; Curr = Curr + Incr)
		{
			for(unsigned int i = Curr; i < Curr + Incr; i++)
				while(Cerisier.insert(i));
			
			start = clock();
			for(unsigned int i = 0; i < NbInsert; i++)
			{
				Cerisier.insert((double)(rand()%(Curr + Incr)));
			}
			end = clock();
			std::cout << Curr << " " << (double) (end - start) / (double) CLOCKS_PER_SEC << std::endl;	
			File << Curr << " " << (double) (end - start) / (double) CLOCKS_PER_SEC << std::endl;	
		}
		File.close();
	} else std::cout << "Erreur ouverture fichier." << std::endl;
	
	return EXIT_SUCCESS;
}
