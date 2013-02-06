#pragma once

#include <initializer_list>

#define DYNAMICBITSET_BOOL_PER_CHAR 8

class DynamicBitset
{
	public:
	DynamicBitset();
	DynamicBitset(const std::initializer_list<bool>& L);
	DynamicBitset(const DynamicBitset& DB);
	~DynamicBitset();
	
	inline unsigned int count() const { return _count; }
	inline unsigned int sizeInByte() const { return _size; }
	inline unsigned int size() const { return _size*DYNAMICBITSET_BOOL_PER_CHAR; }
	
	//bool operator[](unsigned int idx) const;
	bool get(unsigned int idx) const;
	
	void set(unsigned int idx, bool b);
	void push_back(bool b);
	
	void resize(unsigned int s, bool b = false);
	void reserve(unsigned int s);
	
	private:
	char*			_data;
	unsigned int	_size;
	unsigned int	_count; // = 0;
};
