#pragma once

#include <functional>
#include <iostream>
#include <initializer_list>

/*
 Implantation générique du type Tableau Dynamique
 L'interface est largement inspirée du std::vector...
*/

template<typename Data>
class DynArray
{
	public:
	typedef Data*	iterator;
	typedef Data	value_type;
	
	/** @brief Constructeur
	 *
	 * Pas le même comportement que la norme !
	 * @param S Taille à RESERVER, aucun élément n'est inséré à la construction
	 * @param D Element par défaut (utilisé par resize)
	 * @see resize
	**/
	DynArray(size_t S = 1, const Data& D = Data());
	DynArray(const std::initializer_list<Data>& L);
	DynArray(const DynArray<Data>& V);
	DynArray<Data>& operator=(const DynArray<Data>& V);
	virtual ~DynArray();

	bool empty() const { return _count == 0; }
	size_t size() const { return _count; }
	Data& operator[](size_t I) const { return _data[I]; }
	iterator begin() { return _data; }
	iterator end() { return _data + _count; }
	
	void push_back(const Data &D);
	
	void reserve(size_t S);
	void resize(size_t S);
	void shrink_to_fit();

	void swap(DynArray& V);
	
	void erase(size_t I);
	void erase(iterator it);
	void clear();

	protected:
	Data		_default;
	Data*		_data;
	size_t		_count;
	size_t		_capacity;

	void swap(size_t I1, size_t I2);
	
	private:
	void explicit_destruct();
};

template<typename Data>
void DynArray<Data>::swap(size_t I1, size_t I2)
{
	Data tmp = _data[I1];
	_data[I1] = _data[I2];
	_data[I2] = tmp;
}
	
template<typename Data>
DynArray<Data>::DynArray(size_t S, const Data& D) : 
	_default(D), 
	_data(static_cast<Data*>(operator new[](S * sizeof(Data)))), // Reserve memory without calling default constructor
	_count(0), 
	_capacity(S)
{
}

template<typename Data>
DynArray<Data>::DynArray(const std::initializer_list<Data>& L) : 
	_default(Data()), 
	_data(static_cast<Data*>(operator new[](L.size() * sizeof(Data)))), 
	_count(0), 
	_capacity(L.size())
{
	for(auto it = L.begin(); it != L.end(); ++it)
		push_back(*it);
}
		
template<typename Data>
DynArray<Data>::DynArray(const DynArray<Data>& V) : 
	_default(V._default), 
	_data(static_cast<Data*>(operator new[](V._capacity * sizeof(Data)))),
	_count(V._count),
	_capacity(V._capacity)
{
	for(size_t i = 0; i < V.size(); ++i)
		push_back(V[i]);
}

template<typename Data>
DynArray<Data>& DynArray<Data>::operator=(const DynArray<Data>& V)
{
	this->clear();
	_default = V._default;
	for(size_t i = 0; i < V.size(); ++i)
		push_back(V[i]);
	return *this;
}

template<typename Data>
DynArray<Data>::~DynArray()
{
	explicit_destruct();
	operator delete[](_data);
}

template<typename Data>
void DynArray<Data>::push_back(const Data &D)
{
	if(_capacity <= _count)
		reserve(2*_capacity);

	new(_data + _count) Data(D); // placement-new
	++_count;	
}

template<typename Data>
void DynArray<Data>::reserve(size_t S)
{
	if(S <= _capacity) return;
	Data* tmp = static_cast<Data*>(operator new[](S * sizeof(Data)));
	for(size_t i = 0; i < _count; ++i)
		new(tmp + i) Data(_data[i]);
	explicit_destruct();
	operator delete[](_data);
	_data = tmp;
	_capacity = S;
}

template<typename Data>
void DynArray<Data>::resize(size_t S)
{
	if(S <= _count) return;
	
	if(S > _capacity)
		reserve(S);
	
	for(size_t i = _count; i < S; ++i)
		new(_data + i) Data(_default);
	_count = S;
}

template<typename Data>
void DynArray<Data>::shrink_to_fit()
{
	Data* tmp = static_cast<Data*>(operator new[](_count * sizeof(Data)));
	for(size_t i = 0; i < _count; ++i)
		new(tmp + i) Data(_data[i]);
	explicit_destruct();
	operator delete[](_data);
	_data = tmp;
	_capacity = _count;
}

template<typename Data>
void DynArray<Data>::swap(DynArray<Data>& V)
{
	Data* tmp = _data;
	_data = V._data;
	V._data = tmp;
	
	size_t tmp_s = _count;
	_count = V._count;
	V._count = tmp_s;
	
	tmp_s = _capacity;
	_capacity = V._capacity;
	V._capacity = tmp_s;
}

template<typename Data>
void DynArray<Data>::erase(size_t I)
{
	_data[I].~Data();
	--_count;
	while(I < _count)
	{
		new(_data + I) Data(_data[I + 1]);
		_data[I + 1].~Data();
		++I;
	}
}

template<typename Data>
void DynArray<Data>::erase(iterator it)
{
	it->~Data();
	iterator it2 = it;
	++it;
	while(it != end())
	{
		new(it2) Data(*it);
		it->~Data();
		++it;
		++it2;
	}
	--_count;
}

template<typename Data>
void DynArray<Data>::clear()
{
	// Appel explicite aux destructeurs pour éviter la réallocation
	explicit_destruct();
	_count = 0;
}

// Private

template<typename Data>
void DynArray<Data>::explicit_destruct()
{
	for(size_t i = 0; i < _count; ++i)
		_data[i].~Data();
}
