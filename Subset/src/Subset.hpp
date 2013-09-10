#pragma once

#include <DynamicBitset.hpp>

template<typename T>
class Subset
{
	public:
	Subset(T* Set, size_t Size) : _count(0), _size(Size), _subset(), _set(Set)
	{
		_subset.resize(_size);
	}
	
	void insert(T* Element)
	{
		// Submited element wasn't in subset
		if(!_subset.get(Element - _set))
		{
			++_count;
			_subset.set(Element - _set, true);
		}
	}
	
	void remove(T* Element)
	{
		// Submited element was in subset
		if(_subset.get(Element - _set))
		{
			--_count;
			_subset.set(Element - _set, false);
		}
	}	
	
	bool contains(T* Element) const
	{
		return _subset.get(Element - _set);
	}
	
	bool empty() const
	{
		return _count == 0;
	}
	
	size_t count() const
	{
		return _count;
	}
	
	private:
	size_t			_count;
	size_t			_size;
	DynamicBitset	_subset;
	T*				_set;
};
