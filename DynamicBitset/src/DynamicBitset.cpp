#include "DynamicBitset.hpp"

DynamicBitset::DynamicBitset() : _size(1), _count(0)
{
	_data = new char[1];
}

DynamicBitset::DynamicBitset(const DynamicBitset& DB) : _size(DB._size), _count(DB._count)
{
	_data = new char[_size + 1];
	for(unsigned int i = 0; i < _count; ++i)
		set(i, DB.get(i));
}

DynamicBitset::~DynamicBitset()
{
	delete[] _data;
}

void DynamicBitset::push_back(bool b)
{
	if(_count >= _size*DYNAMICBITSET_BOOL_PER_CHAR)
		reserve(DYNAMICBITSET_BOOL_PER_CHAR*2*_size);
	set(_count, b);
	++_count;
}

void DynamicBitset::set(unsigned int idx, bool b)
{
	if(b)
	{
		_data[idx/DYNAMICBITSET_BOOL_PER_CHAR] = _data[idx/DYNAMICBITSET_BOOL_PER_CHAR] | (0x01 << idx % DYNAMICBITSET_BOOL_PER_CHAR);
	} else {
		_data[idx/DYNAMICBITSET_BOOL_PER_CHAR] = ~(~_data[idx/DYNAMICBITSET_BOOL_PER_CHAR] | (0x01 << idx % DYNAMICBITSET_BOOL_PER_CHAR));
	}
}

bool DynamicBitset::get(unsigned int idx) const
{
	return _data[idx/8] & (0x01 << idx % 8);
}

void DynamicBitset::reserve(unsigned int s)
{
	char* tmp = new char[s/8 + 1];
	for(unsigned int i = 0; i < _count; ++i)
		set(i, get(i));
	_data = tmp;
	_size = s;
}

void DynamicBitset::resize(unsigned int s, bool b)
{
	reserve(s);
	for(unsigned int i = 0; i < (_size + 1)*8 - 1; ++i)
		set(i, b);
	_count = (_size + 1)*8 - 1;
}
