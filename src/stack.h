#pragma once
#include "utility.h"
#include "vector.h"
#include "list.h"

template<typename T>
class StackVector : public Vector<T> {
public:
	void push(const T& e) { Vector<T>::insert(e); }
	T pop() { return Vector<T>::remove(Vector<T>::size() - 1); }
	T& top() { return (*this)[Vector<T>::size() - 1]; }
};

template<typename T>
class StackList : public List<T> {
public:
	void push(const T& e) { List<T>::insertAsLast(e); }
	T pop() { return List<T>::remove(last()); }
	T& top() { return List<T>::last()->data; }
};
