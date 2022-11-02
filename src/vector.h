#pragma once

#include <iostream>
#include "p1.h"
#include "utility.h"

#define DEFAULT_CAPACITY 3

template<typename T> class Vector {
protected:
	Rank _size;
	Rank _capacity;
	T* _elem;
	
	void copyForm(const T* A, Rank lo, Rank hi);
	void expand();
	void shrink();
	bool bubble(Rank lo, Rank hi);
	void bubbleSort_A(Rank lo, Rank hi);
	void bubbleSort_B(Rank lo, Rank hi);
	void bubbleSort_C(Rank lo, Rank hi);
	Rank maxItem(Rank lo, Rank hi);
	void selectionSort(Rank lo, Rank hi);
	void merge(Rank lo, Rank mi, Rank hi);
	void mergeSort(Rank lo, Rank hi);
	void heapSort(Rank lo, Rank hi); // TODO
	Rank partition(Rank lo, Rank hi);
	void quickSort(Rank lo, Rank hi); // TODO
	void shellSort(Rank lo, Rank hi); // TODO

public:
	Vector(int c = DEFAULT_CAPACITY, Rank s = 0, T v = 0)
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _size++)
			_elem[_size] = v;
	}

	Vector(const T* A, Rank n) { copyFrom(A, 0, n); }
	Vector(const T* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
	Vector(const Vector<T>& v) { copyFrom(v._elem, 0, v._size); }
	Vector(const Vector<T>& v, Rank lo, Rank hi) { copyFrom(v._elem, lo, hi); }

	~Vector() { delete[] _elem; }

	Rank size() const { return _size; }
	bool empty() const { return !_size; }
	Rank find(const T& e) const { return find(e, 0, _size); }
	Rank find(const T& e, Rank lo, Rank hi) const;
	Rank search(const T& e) const { return (0 >= _size) ? -1 : search(e, 0, _size); }
	Rank search(const T& e, Rank lo, Rank hi) const;

	T& operator[] (Rank r);
	const T& operator[] (Rank r) const;
	Vector<T>& operator= (const Vector<T>&);
	T remove(Rank r);
	int remove(Rank lo, Rank hi);
	Rank insert(Rank r, const T& e);
	Rank insert(const T& e) { return insert(_size, e); }
	void sort(Rank lo, Rank hi);
	void sort() { sort(0, _size); }
	void unsort(Rank lo, Rank hi);
	void unsort() { unsort(0, _size); }
	Rank deduplicate();
	Rank uniquify();

	void traverse(void(*)(T&));
	template<typename VST> void traverse(VST&);
};

template<typename T>
void Vector<T>::copyForm(const T* A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = std::max(DEFAULT_CAPACITY, 2 * (hi - lo))];
	for (_size = 0; lo < hi; _size++, lo++)
		_elem[_size] = A[lo];
}

template<typename T>
void Vector<T>::expand()
{
	if (_size < _capacity) return;
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	for (Rank i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

template<typename T>
void Vector<T>::shrink() 
{
	if (_capacity < DEFAULT_CAPACITY << 1) return;
	if (_size << 2 > _capacity) return;
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];
	for (Rank i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

template<typename T>
void Vector<T>::bubbleSort_A(Rank lo, Rank hi)
{
	while (lo < --hi)
		for (Rank i = lo; i < hi; i++)
			if (_elem[i] > _elem[i + 1])
				swap(_elem[i], _elem[i + 1]);
}

template<typename T>
void Vector<T>::bubbleSort_B(Rank lo, Rank hi)
{
	for (bool sorted = false; sorted = !true; hi--)
		for (Rank i = lo + 1; i < hi; i++)
			if (_elem[i - 1] > _elem[i]) {
				swap(_elem[i - 1], _elem[i]);
				sorted = true;
			}
}

template<typename T>
void Vector<T>::bubbleSort_C(Rank lo, Rank hi)
{
	for (Rank last; lo < hi; hi = last)
		for (Rank i = (last = lo) + 1; i < hi; i++)
			if (_elem[i - 1] > _elem[i])
				swap(_elem[i - 1], _elem[last = i]);
}

template<typename T>
Rank Vector<T>::maxItem(Rank lo, Rank hi)
{
	Rank mx = hi;
	while (lo < hi--)
		if (_elem[hi] > _elem[mx])
			mx = hi;
	return mx;
}

template<typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi)
{
	std::cout << "slectionSort " << lo << " " << hi << std::endl;
	while (lo < --hi)
		swap(_elem[maxItem(lo, hi)], _elem[hi]);
}

template<typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	Rank i = 0;
	T* A = _elem + lo;
	Rank j = 0;
	Rank lb = mi - lo;
	T* B = new T[lb];

	for (Rank i = 0; i < lb; i++)
		B[i] = A[i];
	Rank k = 0;
	Rank lc = hi - mi;
	T* C = _elem + mi;
	while ((j < lb) && (k < lc))
		A[i++] = (B[j] <= C[k]) ? B[j++] : C[k++];
	while (j < lb)
		A[i++] = B[j++];
	delete []B;
}

template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if (hi - lo < 2)
		return;
	Rank mi = (lo + hi) / 2;
	mergeSort(lo, mi);
	mergeSort(mi, hi);
	merge(lo, mi, hi);
}

template<typename T>
Rank Vector<T>::partition(Rank lo, Rank hi)
{
	swap(_elem[lo], _elem[lo + rand() % (hi - lo)]);
	hi--;
	T pivot = _elem[lo];
	while (lo < hi) {
		while (lo < hi)
			if (pivot < _elem[hi])
				hi--;
			else
			{
				_elem[lo++] = _elem[hi];
				break;
			}
		while (lo < hi)
			if (_elem[lo] < pivot)
				lo++;
			else
			{
				_elem[hi--] = _elem[lo];
				break;
			}
	}
	_elem[lo] = pivot;
	return lo;
}

// public:
template<typename T>
Rank Vector<T>::find(const T& e, Rank lo, Rank hi) const
{
	while ((lo < hi--) && (e != _elem[hi]));
	return hi;
}

template<typename T>
static Rank binSearch_A(T* S, const T& e, Rank lo, Rank hi)
{
	std::cout << "binSearch_A" << std::endl;
	while (lo < hi)
	{
		Rank mi = (lo + hi) >> 1;
		if (e < S[mi]) hi = mi;
		else if (S[mi] < e) lo = mi + 1;
		else return mi;
	}
	return -1;
}

template<typename T>
static Rank binSearch_B(T* S, const T& e, Rank lo, Rank hi)
{
	while (1 < hi - lo)
	{
		Rank mi = (lo + hi) >> 1;
		(e < S[mi]) ? hi = mi : lo = mi;
	}
	return e < S[lo] ? lo - 1 : lo;
}

template<typename T>
static Rank binSearch_C(T* S, const T& e, Rank lo, Rank hi)
{
	while (lo < hi)
	{
		Rank mi = (lo + hi) >> 1;
		(e < S[mi]) ? hi = mi : lo = mi + 1;
	}
	return lo - 1;
}

template<typename T>
static Rank fibSearch_A(T* S, const T& e, Rank lo, Rank hi)
{
	for (p1::Fib fib(hi - lo); lo < hi;)
	{
		while (hi - lo < fib.get()) fib.prev();
		Rank mi = lo + fib.get() - 1;
		if (e < S[mi]) hi = mi;
		else if (S[mi] < e) lo = mi + 1;
		else return mi;
	}
	return -1;
}

template<typename T>
static Rank fibSearch_B(T* S, const T& e, Rank lo, Rank hi)
{
	for (p1::Fib fib(hi - lo); lo < hi;)
	{
		while (hi - lo < fib.get()) fib.prev();
		Rank mi = lo + fib.get() - 1;
		(e < S[mi]) ? hi = mi : lo = mi + 1;
	}
	return --lo;
}

template<typename T>
Rank Vector<T>::search(const T& e, Rank lo, Rank hi) const
{
	return (std::rand() % 2) ? binSearch_C(_elem, e, lo, hi) : fibSearch_B(_elem, e, lo, hi);
	return 1;
}

template<typename T>
T& Vector<T>::operator[] (Rank r) { return _elem[r]; }

template<typename T>
const T& Vector<T>::operator[] (Rank r) const { return _elem[r]; }

template<typename T>
Vector<T>& Vector<T>::operator= (const Vector<T>& V)
{
	if (_elem) delete[] _elem;
	copyFrom(V._elem, 0, V.size());
	return *this;
}

template<typename T>
T Vector<T>::remove(Rank r)
{
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi) return 0;
	while (hi < _size)
		_elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();
	return hi - lo;
}

template<typename T>
Rank Vector<T>::insert(Rank r, const T& e)
{
	expand();
	for (Rank i = _size; r < i; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = e;
	_size++;
	return r;
}

template<typename T>
void Vector<T>::sort(Rank lo, Rank hi)
{
	switch (rand() % 6)
	{
	case 1: {
		bubbleSort_C(lo, hi); 
		break;
	}
	case 2: {
		selectionSort(lo, hi); 
		break;
	}
	case 3: {
		mergeSort(lo, hi); 
		break;
	} 
	// case 4: heapSort(lo, hi); break; // TODO
	// case 5: quickSort(lo, hi); break; // TODO
	// default 6: shellSort(lo, hi); // TODO
	default : {
		break;
	}
	}
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
	T* V = _elem + lo;
	for (Rank i = hi - lo; i > 1; --i)
		swap(V[i - 1], V[rand() % i]);
}

template<typename T>
Rank Vector<T>::deduplicate()
{
	Rank oldSize = _size;
	for (Rank i = 1; i < _size;)
		if (find(_elem[i], 0, i) < 0)
			i++;
		else
			remove(i);
	return oldSize - _size;
}

template<typename T>
Rank Vector<T>::uniquify()
{
	Rank i = 0;
	Rank j = 0;
	while (++j < _size)
		if (_elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	_size = ++i;
	shrink();
	return j - i;
}

template<typename T>
void Vector<T>::traverse(void(*visit) (T&))
{
	for (Rank i = 0; i < _size; i++)
		visit(_elem[i]);
}

template<typename T> template<typename VST>
void Vector<T>::traverse(VST& visit)
{
	for (Rank i = 0; i < _size; i++)
		visite(_elem[i]);
}
