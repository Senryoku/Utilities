/*******************************************************************
 * RadixTree
 * Quick implementation of a (kindof) RadixTree of std::string
 * Yoann 'Senryoku' Maret-Verdant
 *******************************************************************/

This is a Work in Progress !!!

Not a RadixTree per se as words doesn't have to be leaves and can be inserted multiples times.
This counting solution thus allow a Inner Node to have a single child as a empty child isn't needed
for this node to be considered as a entire word. Classic RadixTrees impose to their Inner Nodes to
have at least two children.

/** Deprec **/ 
(Uses std::list now)
The std::set for the children isn't usefull with this implementation...
A simple std::list would do the trick for now, but a more sophisticated data structure could 
be usefull to speed up the search of candidate children for insertion/constaining test/removal.
However, the number of children for a given node is limited by the number of characters available
in a worse case scenario and should far less in practical uses.
