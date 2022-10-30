#pragma once
#include "utility.h"
#include "vector.h"

template<typename T>
class StackVector : public Vector<T> {
public:
	void push(const T& e) { insert(e); }
	T pop() { return remove(size() - 1); }
	T& top() { return (*this)[size() - 1]; }
};

template<typename T>
class StackList : public List<T> {
public:
	void push(const T& e) { insertAsLast(e); }
	T pop() { return remove(last()); }
	T& top() { return last()->data; }
};
