#include "RadixTree.hpp"

RadixTree::RadixTree() :
	_root(NULL),
	_count(0)
{
}

RadixTree::~RadixTree()
{
	delete _root;
}

std::list<std::string> RadixTree::getWords() const
{
	std::list<std::string> List;
	if(_root != NULL)
		_root->getWords(List, "");
	return List;
}

void RadixTree::insert(const std::string& Str)
{
	if(_root == NULL)
	{
		_root = new Node(Str);
		_root->add();
	} else {
		if(!_root->insert(Str)) { // Str have nothing in common with _root->getStr()
			Node* n = new Node("");
			Node* n2 = new Node(Str);
			n2->add();
			n->addChild(_root);
			n->addChild(n2);
			_root = n;
		}
	}
	++_count;
}

void RadixTree::remove(const std::string& Str)
{
	if(_root != NULL)
		if(_root->remove(Str))
			--_count;
}

void RadixTree::removeAll(const std::string& Str)
{
	if(_root != NULL)
		_count = _count - _root->removeAll(Str);
}

bool RadixTree::contains(const std::string& Str) const
{
	if(_root == NULL)
	{
		return false;
	} else {
		return _root->contains(Str);
	}
}

void RadixTree::toGraph(const std::string &Path) const
{
	if(_root == NULL) return;
	
	std::ofstream File(Path.c_str());
	if(File.good())
	{
		unsigned int Num = 0;
		File << "digraph RadixTree {" << std::endl;
		_root->toGraph(File, Num, "");
		File << "}" << std::endl;
		File.close();
	}
}
	
RadixTree::Node::Node(const std::string& Str) :
	_count(0),
	_str(Str)
{
}

RadixTree::Node::~Node()
{
	for(auto it = _child.begin(); it != _child.end(); ++it)
		delete *it;
}

bool RadixTree::Node::insert(const std::string& Str)
{
	// Strings have nothing in common : can't insert in this subtree
	if(_str.length() != 0 && (Str.length() == 0 || _str[0] != Str[0])) return false;
	
	size_t i = 0;
	while(i < _str.length() && i < Str.length() && _str[i] == Str[i])
		i++;
	
	if(i == _str.length() && i == Str.length()) {
		add();
		return true;
	} else {
		if(i < _str.length()) { // We'll have to split !
			split(Str, i);
			return true;
		} else if(i < Str.length()) { // One child may be the next node
			for(std::list<Node*>::iterator it = _child.begin();
				it != _child.end();
				++it)
			{
				if((*it)->insert(Str.substr(i)))
					return true;
			}
			// No suitable child has been found...
			Node* n = new Node(Str.substr(i));
			n->add();
			_child.push_back(n);
			return true;
		} 
	}
	
	return false; // Shouldn't happen...
}
		
void RadixTree::Node::split(const std::string& Str, size_t i)
{
	Node* n1 = new Node(_str.substr(i));
	
	_child.swap(n1->_child);
	n1->_count = _count;
	
	_str = _str.substr(0, i);
	_child.push_back(n1);
	
	if(i < Str.length())
	{
		Node* n2 = new Node(Str.substr(i));
		n2->add();
		_child.push_back(n2);
		_count = 0;
	} else {
		_count = 1;
	}
}

bool RadixTree::Node::remove(const std::string& Str) {
	///@todo Implements
	if(_str.length() != 0 && (Str.length() == 0 || _str[0] != Str[0])) return false;
	
	size_t i = 0;
	while(i < _str.length() && i < Str.length() && _str[i] == Str[i])
		i++;
	
	if(i == _str.length() && i == Str.length()) {
		rem();
		return true;
	} else {
		if(i < _str.length()) { // Str isn't in the tree
			return false;
		} else if(i < Str.length()) { // One child may be the next node
			for(std::list<Node*>::iterator it = _child.begin();
				it != _child.end();
				++it)
			{
				if((*it)->remove(Str.substr(i))) {
					if((*it)->getCount() == 0 && (*it)->getChildCount() == 0) {
						delete *it;
						_child.erase(it);
					}
					return true;
				}
			}
			// No suitable child has been found... Str isn't in the tree
			return false;
		} 
	}
	
	return false; // Shouldn't happen...
}


unsigned int RadixTree::Node::removeAll(const std::string& Str) {
	///@todo Implements
	if(_str.length() != 0 && (Str.length() == 0 || _str[0] != Str[0])) return 0;
	
	size_t i = 0;
	while(i < _str.length() && i < Str.length() && _str[i] == Str[i])
		i++;
	
	if(i == _str.length() && i == Str.length()) {
		unsigned int n = _count;
		_count = 0;
		return n;
	} else {
		if(i < _str.length()) { // Str isn't in the tree
			return 0;
		} else if(i < Str.length()) { // One child may be the next node
			for(std::list<Node*>::iterator it = _child.begin();
				it != _child.end();
				++it)
			{
				unsigned int n = (*it)->removeAll(Str.substr(i));
				if(n > 0) {
					if((*it)->getCount() == 0 && (*it)->getChildCount() == 0) {
						delete *it;
						_child.erase(it);
					}
					return n;
				}
			}
			// No suitable child has been found... Str isn't in the tree
			return 0;
		} 
	}
	
	return 0; // Shouldn't happen...
}

bool RadixTree::Node::contains(const std::string& Str) const
{
	///@todo Implements
	size_t i = 0;
	while(i < _str.length() && i < Str.length() && _str[i] == Str[i])
		i++;
		
	if(i < _str.length())
		return false;
		
	if(i == Str.length() && _count > 0)
		return true;
		
	for(std::list<Node*>::const_iterator it = _child.begin();
		it != _child.end();
		++it)
	{
		if((*it)->contains(Str.substr(i)))
			return true;
	}
	
	return false;
}
		
unsigned int RadixTree::Node::toGraph(std::ofstream &File, unsigned int& Num, const std::string& Str) const
{
	unsigned int myNum = Num, childNum;
	std::string nStr = Str + getStr();
	Num++;
	File << "	" << myNum << " [label=\"" << getStr() << " (" << getCount() << ")\"";
	if(getCount() > 0) File << " style=\"filled\" fillcolor=\"lightskyblue\"";
	File << "];" << std::endl;
	for(std::list<Node*>::const_iterator it = _child.begin();
		it != _child.end();
		++it)
	{
		childNum = (*it)->toGraph(File, Num, nStr);
		File << "	" << myNum << " -> " << childNum;
		if((*it)->getCount() > 0) File << " [label=\"" << nStr + (*it)->getStr() << "\"]";
		File << std::endl;
	}
	return myNum;
}

void RadixTree::Node::getWords(std::list<std::string>& List, const std::string& Str) const
{
	std::string cStr = Str + _str;
	
	if(_count > 0)
		List.push_back(cStr);
	
	for(std::list<Node*>::const_iterator it = _child.begin();
		it != _child.end();
		++it)
	{
		(*it)->getWords(List, cStr);
	}
}
