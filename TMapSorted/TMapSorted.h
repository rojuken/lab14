#ifndef TMAPSORTED_H
#define TMAPSORTED_H

#include "TMap.h"

template<class TK, class TV>
class TMapSorted : public TMap<TK, TV>
{
public:
	TMapSorted(int _size = 1000);
	TMapSorted(int _size, TNode<TK, TV>* m);
	TMapSorted(const TMapSorted& p);

	virtual TV& operator[](TK i);
	virtual TV Find(TK k);
	virtual void Delete(TK k);
	virtual void Add(TK k, TV v);

};

template<class TK, class TV>
inline TMapSorted<TK, TV>::TMapSorted(int _size): TMap<TK,TV>::TMap(_size)
{
}

template<class TK, class TV>
inline TMapSorted<TK, TV>::TMapSorted(int _size, TNode<TK, TV>* m)
{
	this->mas = new TNode<TK, TV>[_size];
	for (int i = 0; i < _size; i++)
		this->mas[i] = m[i];

	TNode<TK, TV> tmp;
	for (int i = _size - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (this->mas[j] < this->mas[j + 1])
			{
				tmp = this->mas[j];
				this->mas[j] = this->mas[j + 1];
				this->mas[j + 1] = tmp;
			}
		}
	}
}

template<class TK, class TV>
inline TMapSorted<TK, TV>::TMapSorted(const TMapSorted& p) : TMap<TK,TV>::TMap(p)
{
}

template<class TK, class TV>
inline TV& TMapSorted<TK, TV>::operator[](TK i)
{
	int l = 0;
	int r = this->count;

	while (r - l > 1)
	{
		int x = (l + r) / 2;
		if (this->mas[x].key == i)
			return this->mas[x].val;
		if (this->mas[x].key > i)
			r = x;
		else
			l = x;
	}
	if (this->mas[l].key == i)
		return this->mas[l].val;
	else
		throw new std::exception;
}

template<class TK, class TV>
inline TV TMapSorted<TK, TV>::Find(TK k)
{
	int l = 0;
	int r = this->count;
	int x;
	while (l < r)
	{
		x = (l + r) / 2;
		if (k == this->mas[x].key)
			return this->mas[x].val;
		if (k < this->mas[x].key)
			r = x;
		else
			l = x;
	}
	throw - 1;
}

template<class TK, class TV>
inline void TMapSorted<TK, TV>::Delete(TK k)
{
	int index = -1;
	int l = 0;
	int r = this->count;
	while (r - l > 1)
	{
		int x = (l + r) / 2;
		if (this->mas[x].key == k)
		{
			index = x;
			break;
		}
		if (this->mas[x].key > k)
			r = x;
		else
			l = x;
	}
	if (index == -1)
	{
		if (l == 0)
			index = l;
		else if (r == this->count)
			index = r;
		else
			index = l;
	}
	if (this->mas[index].key != k)
		throw -1;

	for (int i = index; i < this->count - 1; i++)
		this->mas[i] = this->mas[i + 1];

	this->count--;
}

template<class TK, class TV>
inline void TMapSorted<TK, TV>::Add(TK k, TV v)
{
	int index = -1;
	TNode<TK, TV> node(k, v);
	int l = 0;
	int r = this->count;
	while (r - l > 1)
	{
		int x = (l + r) / 2;
		if (this->mas[x] == node)
		{
			index = x;
			break;
		}
		if (this->mas[x] > node)
			r = x;
		else
			l = x;
	}
	if (index == -1)
	{
		if (l == 0 && r == this->count)
		{
			if (this->mas[l] > node)
				index = l;
			else
				index = r;
		}
		else
			if (l == 0)
				index = l;
			else if (r == this->count)
				index = r;
			else
				index = l;
	}
	this->count++;

	if (this->count >= this->size)
		TMap<TK, TV>::Resize(2 * this->size);

	for (int i = this->count - 1; i > index; i--)
		this->mas[i] = this->mas[i - 1];
	this->mas[index] = node;
}

#endif