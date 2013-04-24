#pragma once

template<typename Data>
class List
{
	private:
	class Node
	{
		public:
		Data	_data;
		Node*	_next;
		
		Node(const Data& D = Data(), Node* N = NULL) : _data(D), _next(N) {}
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
		bool operator!=(const iterator& it) { return _ptr != it._ptr; }
		private:
		Node*	_ptr;
	};
	
	List() : _first(NULL), _count(0) {}
	List(const List& L);
	List& operator=(const List& L);
	~List();
	
	bool empty() const { return _count == 0; }
	size_t size() const { return _count; }
	Data& front() const { return _first->_data; }
	iterator begin() const { return iterator(_first); }
	iterator end() const { return iterator(NULL); }
	
	void pop_front();
	void push_front(const Data& D);

	void clear();
	
	template<typename D>
	friend std::ostream& operator<<(std::ostream& out, const List<D>& L);
};

template<typename Data>
List<Data>::List(const List<Data>& L) : _first(NULL), _count(L._count)
{
	Node* tmp = L._first;
	Node** ins = &_first;
	while(tmp != NULL)
	{
		*ins = new Node(tmp->_data);
		ins = &(*ins)->_next;
		tmp = tmp->_next;
	}
}

template<typename Data>
List<Data>& List<Data>::operator=(const List<Data>& L)
{
	clear();
	_count = L._count;
	Node* tmp = L._first;
	Node** ins = &_first;
	while(tmp != NULL)
	{
		*ins = new Node(tmp->_data);
		ins = &(*ins)->_next;
		tmp = tmp->_next;
	}
	return *this;
}
	
template<typename Data>
List<Data>::~List()
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
void List<Data>::pop_front()
{
	Node* tmp = _first;
	_first = tmp->_next;
	delete tmp;
	--_count;
}

template<typename Data>
void List<Data>::push_front(const Data& D)
{
	_first = new Node(D, _first);
	++_count;
}

template<typename Data>
void List<Data>::clear()
{
	while(!empty())
		pop_front();
}
	
template<typename Data>
std::ostream& operator<<(std::ostream& out, const List<Data>& L)
{
	out << "List Debug Display (Count : " << L._count << ") : ";
	for(typename List<Data>::iterator it = L.begin(); it != L.end(); ++it)
		out << *it << " ";
	out << std::endl;
	return out;
}
