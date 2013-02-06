#include "DynamicBitset.hpp"

DynamicBitset::DynamicBitset() : _size(1), _count(0)
{
	_data = new char[_size];
}

DynamicBitset::DynamicBitset(const std::initializer_list<bool>& L) : 
	_size(L.size()/DYNAMICBITSET_BOOL_PER_CHAR + 1), 
	_count(L.size())
{
	_data = new char[_size];
	int i = 0;
	for(auto it = L.begin(); it != L.end(); ++it)
		set(i++, *it);
}

DynamicBitset::DynamicBitset(const DynamicBitset& DB) : _size(DB._size), _count(DB._count)
{
	_data = new char[_size];
	for(unsigned int i = 0; i < _size; ++i)
		_data[i] = DB._data[i];
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
	return _data[idx/DYNAMICBITSET_BOOL_PER_CHAR] & (0x01 << idx % DYNAMICBITSET_BOOL_PER_CHAR);
}

void DynamicBitset::reserve(unsigned int s)
{
	char* tmp = new char[s/DYNAMICBITSET_BOOL_PER_CHAR + 1];
	for(unsigned int i = 0; i < _size; ++i)
		tmp[i] = _data[i];
	_data = tmp;
	_size = s/DYNAMICBITSET_BOOL_PER_CHAR + 1;
}

void DynamicBitset::resize(unsigned int s, bool b)
{
	reserve(s);
	for(unsigned int i = _count; i < _count + DYNAMICBITSET_BOOL_PER_CHAR - (_count % DYNAMICBITSET_BOOL_PER_CHAR); ++i)
		set(i, b);
	for(unsigned int i = _count/DYNAMICBITSET_BOOL_PER_CHAR + 1; i < _size; ++i)
		_data[i] = (b) ? ~0x00 : 0x00;
	_count = s;
}
