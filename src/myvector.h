#pragma once

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
	Rank find(const T& e) const { find(e, 0, _size); }
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
