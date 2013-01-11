#pragma once

#include <fstream>

template<typename DataType>
class AVL
{
	private:
	class Node
	{
		public:
		DataType	_data;
		Node*		_left;
		Node*		_right;
		short int	_balance;
		
		Node(const DataType &D) : _data(D), _left(NULL), _right(NULL), _balance(0) {}
		Node(const Node &N);
		~Node() {}
		void deleteSubTree();
		inline const DataType& getData() { return _data; }
		inline void setData(const DataType& D) { _data = D; }
		inline Node* getLeft() { return _left; }
		inline Node* getRight() { return _right; }
	};
	
	Node* _root;
	
	unsigned int toGraph(Node* N, std::ofstream &File, unsigned int &Next);
	
	public:
	AVL();
	AVL(const AVL &T);
	~AVL();
	
	bool insert(const DataType &D);
	bool remove(const DataType &D); // TODO
	void clear();
	
	void updateBalance(Node* From, const Node* To);
	void leftRotation(Node** N);
	void rightRotation(Node** N);
	void doubleLeftRotation(Node** N);
	void doubleRightRotation(Node** N);
	
	void toGraph(const std::string &Path);
};

#include "AVL.tcc"