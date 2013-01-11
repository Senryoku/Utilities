#pragma once

#include <functional>
#include <iostream>
#include <cstring> // memcpy

/*
 Implantation générique du type Tableau Dynamique
 L'interface est largement inspirée du std::vector...
*/

template<typename Data>
class DynArray
{
	public:
	typedef Data* iterator;
	
	/** @brief Constructeur
	 *
	 * Pas le même comportement que la norme !
	 * @param S Taille à RESERVER, aucun élément n'est inséré à la construction
	 * @param D Element par défaut (utilisé par resize)
	 * @see resize
	**/
	DynArray(size_t S = 1, const Data& D = Data());
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
};

template<typename Data>
void DynArray<Data>::swap(size_t I1, size_t I2)
{
	Data tmp = _data[I1];
	_data[I1] = _data[I2];
	_data[I2] = tmp;
}
	
template<typename Data>
DynArray<Data>::DynArray(size_t S, const Data& D) : _default(D), _count(0), _capacity(S)
{
	_data = new Data[S];
}

template<typename Data>
DynArray<Data>::DynArray(const DynArray<Data>& V) : _default(V._default), _count(V._count), _capacity(V._capacity)
{
	_data = new Data[V._capacity];
	memcpy(_data, V._data, V._capacity*sizeof(Data));
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
	delete[] _data;
}

template<typename Data>
void DynArray<Data>::push_back(const Data &D)
{
	if(_capacity <= _count)
		reserve(2*_capacity);

	_data[_count] = D;
	_count++;	
}

template<typename Data>
void DynArray<Data>::reserve(size_t S)
{
	if(S <= _capacity) return;
	Data* tmp = new Data[S];
	for(size_t i = 0; i < _count; ++i)
		tmp[i] = _data[i];
	delete[] _data;
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
		_data[i] = _default;
	_count = S;
}

template<typename Data>
void DynArray<Data>::shrink_to_fit()
{
	Data* tmp = new Data[_count];
	for(size_t i = 0; i < _count; ++i)
		tmp[i] = _data[i];
	delete[] _data;
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
	while(I < _count - 1)
	{
		_data[I] = _data[I + 1];
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
		*it2 = *it;
		++it;
		++it2;
	}
	_count--;
}

template<typename Data>
void DynArray<Data>::clear()
{
	// Appel explicite aux destructeurs pour éviter la réallocation
	for(size_t i = 0; i < _count; ++i)
		_data[i].~Data();
	_count = 0;
}
