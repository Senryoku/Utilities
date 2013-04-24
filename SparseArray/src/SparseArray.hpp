#pragma once

template<typename Data>
class SparseArray
{
	private:
	class Node
	{
		public:
		size_t	_idx;
		Data	_data;
		Node*	_next;
		
		Node(size_t Index, const Data& D = Data(), Node* N = NULL) : _idx(Index), _data(D), _next(N) {}
	};
	
	Node*	_first;
	size_t	_count;
	
	public:
	class iterator
	{
		public:
		iterator(Node* N = NULL) { _ptr = N; }
		Data& operator*() const { return _ptr->_data; }
		iterator& operator++() { _ptr = _ptr->_next; return *this; } 
		iterator& operator=(const iterator& it) { _ptr = it._ptr; }
		iterator& operator=(Node* N) { _ptr = N; }
		bool operator!=(const iterator& it) const { return _ptr != it._ptr; }
		size_t getIndex() const { return _ptr->_idx; }
		private:
		Node*	_ptr;
	};
	
	SparseArray() : _first(NULL), _count(0) {}
	SparseArray(const SparseArray& L);
	SparseArray& operator=(const SparseArray& L);
	~SparseArray();
	
	bool empty() const { return _count == 0; }
	size_t size() const { return _count; }
	Data& front() const { return _first->_data; }
	iterator begin() const { return iterator(_first); }
	iterator end() const { return iterator(NULL); }

	void insert(size_t Index, const Data& D);
	void remove(size_t Index);

	Data& operator[](size_t Index);
	
	void clear();
	
#ifndef _NDEBUG	
	template<typename D>
	friend std::ostream& operator<<(std::ostream& out, const SparseArray<D>& L);
#endif
};

template<typename Data>
SparseArray<Data>::SparseArray(const SparseArray<Data>& L) : _first(NULL), _count(L._count)
{
	Node* tmp = L._first;
	Node** ins = &_first;
	while(tmp != NULL)
	{
		*ins = new Node(tmp->_idx, tmp->_data);
		ins = &(*ins)->_next;
		tmp = tmp->_next;
	}
}

template<typename Data>
SparseArray<Data>& SparseArray<Data>::operator=(const SparseArray<Data>& L)
{
	clear();
	_count = L._count;
	Node* tmp = L._first;
	Node** ins = &_first;
	while(tmp != NULL)
	{
		*ins = new Node(tmp->_idx, tmp->_data);
		ins = &(*ins)->_next;
		tmp = tmp->_next;
	}
	return *this;
}
	
template<typename Data>
SparseArray<Data>::~SparseArray()
{
	Node *tmp1 = _first, *tmp2;
	while(tmp1 != NULL)
	{
		tmp2 = tmp1;
		tmp1 = tmp1->_next;
		delete tmp2;
	}
}

template<typename Data>
void SparseArray<Data>::remove(size_t Index)
{
	Node** tmp = &_first;
	while(*tmp != NULL && (*tmp)->_idx < Index)
		tmp = &(*tmp)->_next;
	if(*tmp != NULL) 
	{
		Node* del = *tmp;
		*tmp = (*tmp)->_next;
		delete del;
		--_count;
	}
}

template<typename Data>
void SparseArray<Data>::insert(size_t Index, const Data& D)
{
	Node** tmp = &_first;

	while(*tmp != NULL && (*tmp)->_idx < Index)
	{
		tmp = &(*tmp)->_next;
	}

	if(*tmp != NULL && (*tmp)->_idx == Index)
	{
		(*tmp)->_data = D;
	} else {
		*tmp = new Node(Index, D, *tmp);
		++_count;
	}
}

template<typename Data>
Data& SparseArray<Data>::operator[](size_t Index)
{
	Node** tmp = &_first;

	while(*tmp != NULL && (*tmp)->_idx < Index)
		tmp = &(*tmp)->_next;
	
	if(*tmp == NULL || (*tmp)->_idx != Index)
	{
		*tmp = new Node(Index, Data(), *tmp);
		++_count;
	}
	return (*tmp)->_data;
}
	
template<typename Data>
void SparseArray<Data>::clear()
{
	Node* tmp = _first;
	while(tmp != NULL)
	{
		Node* del = tmp;
		tmp = tmp->_next;
		delete del;
	}
	_first = NULL;
	_count = 0;
}

#ifndef _NDEBUG	
template<typename Data>
std::ostream& operator<<(std::ostream& out, const SparseArray<Data>& L)
{
	out << "SparseArray Debug Display (Count : " << L._count << ") : ";
	for(typename SparseArray<Data>::iterator it = L.begin(); it != L.end(); ++it)
		out << "[" << it.getIndex() << "]" << *it << " ";
	out << std::endl;
	return out;
}
#endif
