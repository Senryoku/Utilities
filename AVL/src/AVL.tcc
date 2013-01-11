template<typename DataType>
void AVL<DataType>::Node::deleteSubTree()
{
	if(_left != NULL) _left->deleteSubTree();
	if(_right != NULL) _right->deleteSubTree();
	delete this;
}
	
template<typename DataType>	
AVL<DataType>::AVL() : _root(NULL)
{
}

template<typename DataType>
AVL<DataType>::Node::Node(const Node &N) :	_data(N._data), _balance(N._balance)
{
	if(N._left != NULL)
		_left = new Node(*N._left);
	else 
		_left = NULL;
	if(N._right != NULL)
		_right = new Node(*N._right);
	else 
		_right = NULL;
}

template<typename DataType>
AVL<DataType>::AVL(const AVL &T)
{
	if(T._root != NULL)
		_root = new Node(*T._root);
	else _root = NULL;
}

template<typename DataType>
AVL<DataType>::~AVL()
{
	clear();
}

template<typename DataType>
void AVL<DataType>::updateBalance(Node* From, const Node* To)
{
	Node* tmp = From;
	while(tmp != To)
	{
		if(To->_data < tmp->_data)
		{
			--tmp->_balance;
			tmp = tmp->_left;
		} else {
			++tmp->_balance;
			tmp = tmp->_right;
		}
	}
}

template<typename DataType>
bool AVL<DataType>::insert(const DataType &D)
{
	Node** N = &_root;
	Node** LastUnbalanced = NULL;
	while(*N != NULL && (*N)->_data != D)
	{
		if((*N)->_balance == -1 || (*N)->_balance == 1) LastUnbalanced = N;
		if(D < (*N)->_data)
			N = &(*N)->_left;
		else
			N = &(*N)->_right;
	}
	if(*N == NULL)
	{
		*N = new Node(D);
		if(LastUnbalanced != NULL)
		{
			updateBalance(*LastUnbalanced, *N);
			if((*LastUnbalanced)->_balance == -2)
			{
				if((*LastUnbalanced)->_left->_balance == -1) // Left Left
					rightRotation(LastUnbalanced);
				else if((*LastUnbalanced)->_left->_balance == 1) // Left Right
					doubleRightRotation(LastUnbalanced);
			} else if((*LastUnbalanced)->_balance == 2) {
				if((*LastUnbalanced)->_right->_balance == 1) // Right Right
					leftRotation(LastUnbalanced);
				else if((*LastUnbalanced)->_right->_balance == -1) // Right Left
					doubleLeftRotation(LastUnbalanced);
			}
		} else {
			updateBalance(_root, *N);
		}
		return true;
	} else return false;
}

template<typename DataType>
bool AVL<DataType>::remove(const DataType &D)
{
	// A faire...
	Node** N = &_root;
	while(*N != NULL && (*N)->_data != D)
	{
		if(D < (*N)->_data)
			N = &(*N)->_left;
		else
			N = &(*N)->_right;
	}
	if(*N != NULL)
		;// ...
	else return false;
	
	return false;
}

template<typename DataType>
void AVL<DataType>::clear()
{
	_root->deleteSubTree();
	_root = NULL;
}

//#include <iostream>

template<typename DataType>
void AVL<DataType>::leftRotation(Node** N)
{
	//std::cout << "leftRotation" << std::endl;
	Node* tmp = (*N)->_right->_left;
	(*N)->_right->_left = *N;
	*N = (*N)->_right;
	(*N)->_left->_right = tmp;
	
	(*N)->_balance = 0;
	(*N)->_left->_balance = 0;
}

template<typename DataType>
void AVL<DataType>::rightRotation(Node** N)
{
	//std::cout << "rightRotation" << std::endl;
	Node* tmp = (*N)->_left->_right;
	(*N)->_left->_right = *N;
	*N = (*N)->_left;
	(*N)->_right->_left = tmp;
	
	(*N)->_balance = 0;
	(*N)->_right->_balance = 0;
}

template<typename DataType>
void AVL<DataType>::doubleLeftRotation(Node** N)
{
	//std::cout << "doubleLeftRotation" << std::endl;
	Node* tmp = *N;
	Node* tmp2 = (*N)->_right;
	*N = tmp2->_left;
	tmp->_right = (*N)->_left;
	(*N)->_left = tmp;
	tmp2->_left = (*N)->_right;
	(*N)->_right = tmp2;
	
	if((*N)->_balance == -1)
	{
		(*N)->_left->_balance = 0;
		(*N)->_right->_balance = 1;
	} else if((*N)->_balance == 1) {
		(*N)->_left->_balance = -1;
		(*N)->_right->_balance = 0;
	} else {
		(*N)->_left->_balance = 0;
		(*N)->_right->_balance = 0;
	}
	(*N)->_balance = 0;
}

template<typename DataType>
void AVL<DataType>::doubleRightRotation(Node** N)
{
	//std::cout << "doubleRightRotation" << std::endl;
	Node* tmp = *N;
	Node* tmp2 = (*N)->_left;
	*N = tmp2->_right;
	tmp->_left = (*N)->_right;
	(*N)->_right = tmp;
	tmp2->_right = (*N)->_left;
	(*N)->_left = tmp2;
	
	if((*N)->_balance == -1)
	{
		(*N)->_left->_balance = 0;
		(*N)->_right->_balance = 1;
	} else if((*N)->_balance == 1) {
		(*N)->_left->_balance = -1;
		(*N)->_right->_balance = 0;
	} else {
		(*N)->_left->_balance = 0;
		(*N)->_right->_balance = 0;
	}
	(*N)->_balance = 0;
}

template<typename DataType>
unsigned int AVL<DataType>::toGraph(Node* N, std::ofstream &File, unsigned int &Next)
{
	unsigned int id = Next;
	Next++;
	if(N == NULL)
	{
		File << "	" << id << " [shape=point]" << std::endl;
	} else {
		unsigned int l1 = toGraph(N->getLeft(), File, Next);
		unsigned int l2 = toGraph(N->getRight(), File, Next);
		File << "	" << id << " [label=\"" << N->getData() << " (" << N->_balance << ")\"];" << std::endl;
		File << "	" << id << " -> " << l1 << std::endl;
		File << "	" << id << " -> " << l2 << std::endl;
	}
	return id;
}

template<typename DataType>
void AVL<DataType>::toGraph(const std::string &Path)
{
	std::ofstream File(Path.c_str());
	if(File.good())
	{
		unsigned int Next = 0;
		File << "digraph AVL {" << std::endl;
		toGraph(_root, File, Next);
		File << "}" << std::endl;
		File.close();
	}
}
