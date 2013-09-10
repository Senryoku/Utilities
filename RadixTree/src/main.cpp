#include "RadixTree.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
	RadixTree RT;
	
	RT.insert("Poirier");
	RT.insert("Poire");
	RT.insert("Framboisier");
	RT.insert("Framboise");
	RT.insert("Cerisier");
	RT.insert("Cerise");
	RT.insert("Fraise");
	RT.insert("Fraisier");
	RT.insert("Prune");
	RT.insert("Prunier");
	RT.insert("Parabolique");
	RT.insert("Para");
	RT.insert("Parachute");
	
	RT.remove("Para");
	RT.remove("Parachute");
	
	RT.toGraph("graph.gv");
	
	system("dot -Tpng \"graph.gv\" -o \"graph.png\"");
	
	std::list<std::string> List = RT.getWords();
	
	std::cout << "Words in the tree :" << std::endl;
	for(std::list<std::string>::iterator it = List.begin();
		it != List.end();
		++it)
	{
		std::cout << *it << std::endl;
	}
	
	RadixTree RT2;
	std::string word;
	std::cout << "Type words to add to the new Radix Tree (-word to remove word from the tree, /quit to quit, see the result in RT.png)" << std::endl;
	while(word != "/quit")
	{
		std::cin >> word;
		if(word != "/quit")
		{
			if(word[0] == '-')
			{
				RT2.remove(word.substr(1));
			} else {
				RT2.insert(word);
			}
			RT2.toGraph("RT.gv");
			system("dot -Tpng \"RT.gv\" -o \"RT.png\"");
		}
	}
	
	List = RT2.getWords();
	std::cout << "Final List :" << std::endl;	for(std::list<std::string>::iterator it = List.begin();
		it != List.end();
		++it)
	{
		std::cout << *it << std::endl;
	}
	
	//RT2.toGraph("RT.gv");
	//system("dot -Tpng \"RT.gv\" -o \"RT.png\"");
	
	return 0;
}