#pragma once

#include <set>
#include <list>
#include <string>
#include <fstream>

class RadixTree {
	private:
	class Node;
	
	public:
	RadixTree();
	~RadixTree();
	
	std::list<std::string> getWords() const;
	
	void insert(const std::string& Str);
	void remove(const std::string& Str);
	
	bool contains(const std::string& Str) const;
	
	void toGraph(const std::string &Path) const;
	
	private:
	
	struct NodeComparator {
		bool operator() (const RadixTree::Node*& lhs, const RadixTree::Node*& rhs) const
		{
			return lhs->getStr() < rhs->getStr();
		}
	};
	
	class Node {
		public:
		Node(const std::string& Str);
		~Node();
		
		struct comparator {
			bool operator() (Node* lhs, Node* rhs) const
			{
				return lhs->getStr() < rhs->getStr();
			}
		};
		
		void add() { ++_count; }
		void rem() { if(_count > 0) --_count; }
		
		bool insert(const std::string& Str);
		void split(const std::string& Str, size_t i);
		
		void addChild(Node* N) { _child.insert(N); }
		
		bool contains(const std::string& Str) const;
		unsigned int getCount() const { return _count; }
		const std::string& getStr() const { return _str; }
		size_t getChildCount() const { return _child.size(); }
		const std::set<Node*, comparator>& getChildren() const { return _child; }
		
		unsigned int toGraph(std::ofstream &File, unsigned int& Num) const;
		
		void getWords(std::list<std::string>& List, const std::string& Str) const;
	
		private:
		unsigned int					_count;
		std::string						_str;
		std::set<Node*, comparator>		_child;
	};
	
	Node*			_root;
	unsigned int	_count;
};
