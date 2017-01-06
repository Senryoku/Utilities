#pragma once

#define SKIPLIST_DEBUG 1

#include <cstdlib>

template<typename Data>
class defaultComparatorSkipList
{
	public:
	bool operator()(const Data& D1, const Data& D2)
	{
		return D1 < D2;
	}
};

template<typename Data, typename Comparator = defaultComparatorSkipList<Data> >
class SkipList
{
	public:
	class Node
	{
		public:
		Data	_data;
		Node**	_next;
		
		Node(const Data& D = Data(), Node** N = NULL) : _data(D), _next(N) {}
		~Node() { delete[] _next; }
	};
	
	class iterator
	{
		public:
		iterator(Node* N = NULL) { _ptr = N; }
		Data& operator*() const { return _ptr->_data; }
		iterator& operator++() { _ptr = _ptr->_next[0]; return *this; }
		iterator& operator=(const iterator& it) { _ptr = it._ptr; }
		iterator& operator=(Node* N) { _ptr = N; }
		bool operator!=(const iterator& it) { return _ptr != it._ptr; }
		private:
		Node*	_ptr;
	};
	
	SkipList(Comparator C = Comparator());
	~SkipList();

	const Comparator& getComparator() const { return _comp; }
	size_t getLevel() const { return _lvl; }
	size_t getMaxLevel() const { return _maxLevel; }
	void setMaxLevel(size_t Lvl) { if(Lvl > _lvl) _maxLevel = Lvl; }
	float getProbability() const { return _probability; }
	void setProbability(float P) { _probability = P; }
	
	iterator begin() const { return iterator(_first[0]); }
	iterator end() const { return iterator(NULL); }
	
	bool empty() const { return _count == 0; }
	size_t size() const { return _count; }
	
	void insert(const Data &D);
	void erase(iterator I);
	size_t erase(const Data &D);
	void clear();

	iterator find(const Data &D) const;
	size_t count(const Data &D) const;

#if SKIPLIST_DEBUG == 1
	template<typename D, typename C>
	friend std::ostream& operator<<(std::ostream& out, const SkipList<D, C>& SL);
	void debugDisplay(std::ostream& out);
#endif

	protected:
	Comparator	_comp;
	Node**		_first;
	size_t		_count;
	size_t		_lvl;
	size_t		_maxLevel;
	float		_probability;
	
	size_t randomLevel();
	void updateLevel(size_t Lvl);
};

template<typename Data, typename Comparator>
SkipList<Data, Comparator>::SkipList(Comparator C) : _comp(C), _count(0), _lvl(0), _maxLevel(63), _probability(0.5f)
{
	_first = new Node*[1];
	_first[0] = NULL;
}

template<typename Data, typename Comparator>
SkipList<Data, Comparator>::~SkipList()
{
	clear();
	delete[] _first;
}

template<typename Data, typename Comparator>
size_t SkipList<Data, Comparator>::randomLevel()
{
	size_t Level = 0;
	while(static_cast<double>(rand() % 100)/100.f < _probability && Level < _maxLevel)
		++Level;
	return Level;
}

template<typename Data, typename Comparator>
void SkipList<Data, Comparator>::updateLevel(size_t Lvl)
{
	Node** tmp = new Node*[Lvl + 1];
	for(size_t i = 0; i <= _lvl; ++i)
		tmp[i] = _first[i];
	for(size_t i = _lvl + 1; i <= Lvl; ++i)
		tmp[i] = NULL;
	_first = tmp;
	_lvl = Lvl;
}
	
template<typename Data, typename Comparator>
void SkipList<Data, Comparator>::insert(const Data &D)
{
	size_t insertLevel = randomLevel();
	if(insertLevel > _lvl) updateLevel(insertLevel);
	
	Node* prev = NULL;
	Node* tmp = _first[_lvl];
	Node** tmpTab = new Node*[insertLevel + 1]; // Sauvegarde des Nodes à modifier, il deviendra la liste des suivants.
	for(int i = _lvl; i >= 0; --i)
	{
		while(tmp != NULL && _comp(tmp->_data, D))
		{
			prev = tmp;
			tmp = tmp->_next[i];
		}
		
		if(tmp == NULL)
		{
			if(static_cast<size_t>(i) <= insertLevel)
				tmpTab[i] = prev;
			if(prev == NULL && i > 0)
			{
				tmp = _first[i - 1];
			} else {
				tmp = prev;
			}
		//} else if(tmp->_data == D) { // Elément déjà inséré
		} else if(!_comp(D, tmp->_data)) {
			delete[] tmpTab;
			return;
		} else {
			if(static_cast<size_t>(i) <= insertLevel)
				tmpTab[i] = prev;
			if(prev == NULL && i > 0)
				tmp = _first[i - 1];
			else
				tmp = prev;
		}
	}
	Node* newNode = new Node(D, tmpTab);
	for(size_t i = 0; i <= insertLevel; ++i)
	{
		Node* tmpNode = tmpTab[i];
		if(tmpNode != NULL)
		{
			tmpTab[i] = tmpNode->_next[i];
			tmpNode->_next[i] = newNode;
		} else {
			tmpTab[i] = _first[i];
			_first[i] = newNode;
		}
	}
	++_count;
}

template<typename Data, typename Comparator>
void SkipList<Data, Comparator>::erase(iterator I)
{
	erase(*I);
}

template<typename Data, typename Comparator>
size_t SkipList<Data, Comparator>::erase(const Data &D)
{
	/// @todo A vérifier
	Node* found = NULL;
	Node* prev = NULL;
	Node* tmp = _first[_lvl];
	for(int i = _lvl; i >= 0; --i)
	{
		while(tmp != NULL && _comp(tmp->_data, D))
		{
			prev = tmp;
			tmp = tmp->_next[i];
		}
		
		if(tmp == NULL)
		{
			if(prev == NULL && i > 0)
				tmp = _first[i - 1];
			else
				tmp = prev;
		} else if((found != NULL && tmp == found) || !(_comp(D, tmp->_data))) {
			found = tmp; // Cas found == NULL
			if(prev == NULL)
			{
				_first[i] = tmp->_next[i];
				if(i > 0) tmp = _first[i - 1];
			} else {
				prev->_next[i] = tmp->_next[i];
				tmp = prev;
			}
		} else {
			if(prev == NULL && i > 0)
				tmp = _first[i - 1];
			else
				tmp = prev;
		}
	}
	if(found != NULL)
	{
		delete found;
		_count--;
	}
	return 0;
}

template<typename Data, typename Comparator>
void SkipList<Data, Comparator>::clear()
{
	Node* tmp = _first[0];
	Node* tmp2 = NULL;
	while(tmp != NULL)
	{
		tmp2 = tmp;
		tmp = tmp->_next[0];
		delete tmp2;
	}
	for(size_t i = 0; i <= _lvl; ++i)
		_first[i] = NULL;
	_count = 0;
}


template<typename Data, typename Comparator>
typename SkipList<Data, Comparator>::iterator SkipList<Data, Comparator>::find(const Data &D) const
{
	Node* prev = NULL;
	Node* tmp = _first[_lvl];
	for(int i = _lvl; i >= 0; --i)
	{
		while(tmp != NULL && _comp(tmp->_data, D))
		{
			prev = tmp;
			tmp = tmp->_next[i];
		}
		
		if(tmp == NULL)
		{
			if(prev == NULL && i > 0)
			{
				tmp = _first[i - 1];
			} else {
				tmp = prev;
			}
		//} else if(tmp->_data == D) {
		} else if(!_comp(D, tmp->_data)) {
			return iterator(tmp);
		} else {
			if(prev == NULL && i > 0)
				tmp = _first[i - 1];
			else
				tmp = prev;
		}
	}
	return iterator(NULL);
}

template<typename Data, typename Comparator>
size_t SkipList<Data, Comparator>::count(const Data &D) const
{
	return (find(D) == end()) ? 0 : 1;
}

#if SKIPLIST_DEBUG == 1
template<typename Data, typename Comparator>
std::ostream& operator<<(std::ostream& out, const SkipList<Data, Comparator>& SL)
{
	out << "SkipList Debug Display (Count : " << SL._count << ") : ";
	for(typename SkipList<Data, Comparator>::iterator it = SL.begin(); it != SL.end(); ++it)
		out << *it << " ";
	out << std::endl;
	return out;
}

template<typename Data, typename Comparator>
void SkipList<Data, Comparator>::debugDisplay(std::ostream& out)
{
	out << std::endl << " ============ DebugDisplay SkipList ============ " << std::endl
		<< "(" << _count << " element(s), " << _lvl + 1 << " niveau(x))" << std::endl;
	for(int i = _lvl; i >= 0; i--)
	{
		Node* N = _first[i];
		if(N != NULL)
		{
			out << "Level " << i << " : \t";
			Node* M = _first[0];
			while(M != NULL)
			{
				if(N == M)
				{
					out << N->_data << "\t";
					N = N->_next[i];
				} else {
					out << "-\t";
				}
				M = M->_next[0];
			}
			out << std::endl;
		}
	}
	out << " ============================================== " << std::endl << std::endl;
}
#endif