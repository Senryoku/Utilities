#pragma once

#define DYNAMICBITSET_BOOL_PER_CHAR 8

class DynamicBitset
{
	public:
	DynamicBitset();
	DynamicBitset(const DynamicBitset& DB);
	~DynamicBitset();
	
	unsigned int count() const { return _count; }
	
	bool operator[](unsigned int idx) const;
	bool get(unsigned int idx) const;
	
	void set(unsigned int idx, bool b);
	void push_back(bool b);
	
	void resize(unsigned int s, bool b = true);
	void reserve(unsigned int s);
	
	private:
	char*			_data;
	unsigned int	_size;
	unsigned int	_count;
};
