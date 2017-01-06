#pragma once

#include <functional>

#include "DynArray.hpp"

template<typename Data, typename Comparator = std::less<Data>>
class BinaryHeap : public DynArray<Data>
{
public:
	BinaryHeap(size_t S);
	BinaryHeap(Comparator C = Comparator(), size_t S = 1);
	~BinaryHeap();

	void push(const Data &D);
	const Data& top() { return DynArray<Data>::_data[0]; }
	void pop();

	template<typename D, typename C>
	friend std::ostream& operator<<(std::ostream& out, const BinaryHeap<D, C>& BH);

protected:
	Comparator	_comp;
	
	inline static size_t father(size_t I) { return I/2; }
	inline static size_t left(size_t I) { return I*2; }
	inline static size_t right(size_t I) { return I*2 + 1; }
};
	
template<typename Data, typename Comparator>
BinaryHeap<Data, Comparator>::BinaryHeap(size_t S) : DynArray<Data>(), _comp(Comparator())
{
	DynArray<Data>::reserve(S);
}

template<typename Data, typename Comparator>
BinaryHeap<Data, Comparator>::BinaryHeap(Comparator C, size_t S) : DynArray<Data>(), _comp(C)
{
	DynArray<Data>::reserve(S);
}

template<typename Data, typename Comparator>
BinaryHeap<Data, Comparator>::~BinaryHeap()
{
}

template<typename Data, typename Comparator>
void BinaryHeap<Data, Comparator>::push(const Data &D)
{
	if(DynArray<Data>::_capacity <= DynArray<Data>::_count)
		DynArray<Data>::reserve(2*DynArray<Data>::_capacity);

	size_t tmp = DynArray<Data>::_count;
	while(tmp > 0 && _comp(DynArray<Data>::_data[father(tmp)], D))
	{
		DynArray<Data>::_data[tmp] = DynArray<Data>::_data[father(tmp)];
		tmp = father(tmp);
	}
	DynArray<Data>::_data[tmp] = D;
	DynArray<Data>::_count++;	
}

template<typename Data, typename Comparator>
std::ostream& operator<<(std::ostream& out, const BinaryHeap<Data, Comparator>& BH)
{
	out << "BinaryHeap Debug Display (Count : " << BH._count << ", Capacity : " << BH._capacity << ") : ";
	for(size_t i = 0; i < BH._count; ++i)
		out << BH._data[i] << " ";
	out << std::endl;
	return out;
}

template<typename Data, typename Comparator>
void BinaryHeap<Data, Comparator>::pop()
{
	--DynArray<Data>::_count;
	DynArray<Data>::_data[0] = DynArray<Data>::_data[DynArray<Data>::_count];
	size_t tmp = 0;
	while(true)
	{
		if(DynArray<Data>::_count > right(tmp))
		{
			if(_comp(DynArray<Data>::_data[left(tmp)], DynArray<Data>::_data[right(tmp)]))
			{
				if(_comp(DynArray<Data>::_data[tmp], DynArray<Data>::_data[right(tmp)]))
				{
					this->swap(tmp, right(tmp));
					tmp = right(tmp);
				} else if(_comp(DynArray<Data>::_data[tmp], DynArray<Data>::_data[left(tmp)])) {
					this->swap(tmp, left(tmp));
					tmp = left(tmp);
				} else break;
			} else {
				if(_comp(DynArray<Data>::_data[tmp], DynArray<Data>::_data[left(tmp)]))
				{
					this->swap(tmp, left(tmp));
					tmp = left(tmp);
				} else if(_comp(DynArray<Data>::_data[tmp], DynArray<Data>::_data[right(tmp)])) {
					this->swap(tmp, right(tmp));
					tmp = right(tmp);
				} else break;
			}
		} else if(DynArray<Data>::_count > left(tmp)) {
				if(_comp(DynArray<Data>::_data[tmp], DynArray<Data>::_data[left(tmp)]))
				{
					this->swap(tmp, left(tmp));
					tmp = left(tmp);
				} else break;
		} else break;
	}
}
