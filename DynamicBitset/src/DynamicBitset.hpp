#pragma once

#include <initializer_list>

class DynamicBitset
{
public:
	class bool_wrapper
	{
	public:
		bool_wrapper(DynamicBitset& db, std::size_t idx);
		inline operator bool()        const { return _db->get(_idx); }
		inline void operator=(bool b) const { _db->set(_idx, b); }
	private:
		DynamicBitset* _db = nullptr;
		std::size_t    _idx = 0;
	};
	
	DynamicBitset();
	DynamicBitset(const DynamicBitset& db);
	DynamicBitset(DynamicBitset&& db);
	DynamicBitset(const std::initializer_list<bool>& L);
	~DynamicBitset();

	inline std::size_t size()      const { return _size; }
	inline std::size_t capacity()  const { return _buff_size * bit_per_char; }
	inline bool empty()            const { return _size == 0; }
	
	bool get(std::size_t idx) const;
	inline bool operator[](std::size_t idx)   const { return get(idx); }
	inline bool_wrapper operator[](std::size_t idx) { return {*this, idx}; }
	
	void set(std::size_t idx, bool b);
	void push_back(bool b);
	inline void clear() { _size = 0; }
	
	void resize(std::size_t s, bool b = false);
	void reserve(std::size_t s);
	
	class const_iterator
	{
	public:
		const_iterator(const DynamicBitset& db, std::size_t idx);
		inline const_iterator& operator++()              { ++_idx; return *this; }
		inline const_iterator operator++(int)            { auto r{*this}; ++(*this); return r; }
		inline bool operator*()                    const { return _db->get(_idx); }
		inline bool operator==(const_iterator& it) const { return _db == it._db && _idx == it._idx; } 
		inline bool operator!=(const_iterator& it) const { return !(*this == it); } 
	private:
		const DynamicBitset* _db = nullptr;
		std::size_t          _idx = 0;
	};
	
	inline const_iterator begin()  const { return cbegin(); }
	inline const_iterator end()    const { return cend(); }
	inline const_iterator cbegin() const { return const_iterator(*this, 0); }
	inline const_iterator cend()   const { return const_iterator(*this, _size); }
	
	class iterator
	{
	public:
		iterator(DynamicBitset& db, std::size_t idx);
		inline iterator& operator++()              { ++_idx; return *this; }
		inline iterator operator++(int)            { auto r{*this}; ++(*this); return r; }
		inline bool_wrapper operator*()      const { return bool_wrapper{*_db, _idx}; }
		inline bool operator==(iterator& it) const { return _db == it._db && _idx == it._idx; } 
		inline bool operator!=(iterator& it) const { return !(*this == it); } 
	private:
		DynamicBitset* _db = nullptr;
		std::size_t    _idx = 0;
	};
	
	inline iterator begin() { return iterator(*this, 0); }
	inline iterator end()   { return iterator(*this, _size); }
	
	static constexpr std::size_t bit_per_char = sizeof(char);
	
private:
	std::size_t	_buff_size  = 0;
	std::size_t	_size = 0;
	char*		_data  = nullptr;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation

DynamicBitset::DynamicBitset() :
	_buff_size{1},
	_size{0},
	_data{new char[_buff_size]}
{
}

DynamicBitset::DynamicBitset(const std::initializer_list<bool>& L) : 
	_buff_size(L.size() / bit_per_char + 1), 
	_size(L.size()),
	_data{new char[_buff_size]}
{
	int i = 0;
	for(const auto& it : L)
		set(i++, it);
}

DynamicBitset::DynamicBitset(const DynamicBitset& db) :
	_buff_size{db._buff_size},
	_size{db._size},
	_data{new char[_buff_size]}
{
	for(std::size_t i = 0; i < _buff_size; ++i)
		_data[i] = db._data[i];
}

DynamicBitset::DynamicBitset(DynamicBitset&& db) : 
	_buff_size{db._buff_size},
	_size{db._size},
	_data{db._data}
{
	db._data = nullptr;
	db._buff_size = 0;
	db._size = 0;
}

DynamicBitset::~DynamicBitset()
{
	delete[] _data;
}

void DynamicBitset::push_back(bool b)
{
	if(_size >= _buff_size * bit_per_char)
		reserve(bit_per_char * 2 * _buff_size);
	set(_size, b);
	++_size;
}

void DynamicBitset::set(std::size_t idx, bool b)
{
	if(b)
		_data[idx/bit_per_char] = _data[idx/bit_per_char] | (0x01 << idx % bit_per_char);
	else
		_data[idx/bit_per_char] = ~(~_data[idx/bit_per_char] | (0x01 << idx % bit_per_char));
}

bool DynamicBitset::get(std::size_t idx) const
{
	return _data[idx/bit_per_char] & (0x01 << idx % bit_per_char);
}

void DynamicBitset::reserve(std::size_t s)
{
	if(s <= _buff_size)
		return;
	char* tmp = new char[s/bit_per_char + 1];
	for(std::size_t i = 0; i < _buff_size; ++i)
		tmp[i] = _data[i];
	_data = tmp;
	_buff_size = s/bit_per_char + 1;
}

void DynamicBitset::resize(std::size_t s, bool b)
{
	if(s > _buff_size)
		reserve(s);
	for(std::size_t i = _size; i < _size + bit_per_char - (_size % bit_per_char); ++i)
		set(i, b);
	for(std::size_t i = _size/bit_per_char + 1; i < _buff_size; ++i)
		_data[i] = (b) ? ~0x00 : 0x00;
	_size = s;
}

DynamicBitset::bool_wrapper::bool_wrapper(DynamicBitset& db, std::size_t idx) :
	_db(&db),
	_idx(idx)
{
}

DynamicBitset::const_iterator::const_iterator(const DynamicBitset& db, std::size_t idx) :
	_db(&db),
	_idx(idx)
{
}

DynamicBitset::iterator::iterator(DynamicBitset& db, std::size_t idx) :
	_db(&db),
	_idx(idx)
{
}
