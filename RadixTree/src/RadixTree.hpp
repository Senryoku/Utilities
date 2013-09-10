#pragma once

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
	void removeAll(const std::string& Str);
	
	inline unsigned int getCount() const { return _count; }
	bool contains(const std::string& Str) const;
	
	void toGraph(const std::string& Path) const;
	
	private:
	
	class Node {
		public:
		Node(const std::string& Str);
		~Node();
		
		// Useless now
		struct comparator {
			bool operator() (Node* lhs, Node* rhs) const
			{
				return lhs->getStr() < rhs->getStr();
			}
		};
		
		inline void add() { ++_count; }
		inline void rem() { if(_count > 0) --_count; }
		
		bool insert(const std::string& Str);
		void split(const std::string& Str, size_t i);
		
		bool remove(const std::string& Str);
		unsigned int removeAll(const std::string& Str);
		
		inline void addChild(Node* N) { _child.push_back(N); }
		
		bool contains(const std::string& Str) const;
		inline unsigned int getCount() const { return _count; }
		inline const std::string& getStr() const { return _str; }
		inline size_t getChildCount() const { return _child.size(); }
		inline const std::list<Node*>& getChildren() const { return _child; }
		
		unsigned int toGraph(std::ofstream &File, unsigned int& Num, const std::string& Str) const;
		
		void getWords(std::list<std::string>& List, const std::string& Str) const;
	
		private:
		unsigned int					_count;
		std::string						_str;
		std::list<Node*>				_child;
	};
	
	Node*			_root;
	unsigned int	_count;
};
