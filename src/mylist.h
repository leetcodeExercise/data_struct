#pragma once
#include "utility.h"

template<typename T> struct ListNode;
template<typename T> using ListNodePosi = ListNode<T>*;
template<typename T> struct ListNode {
	T data;
	ListNodePosi<T> pred;
	ListNodePosi<T> succ;

	ListNode() {}
	ListNode(T e, ListNodePosi<T> p = nullptr, ListNodePosi<T> s = nullptr)
		: data(e), pred(p), succ(s) {}
	ListNodePosi<T> insertAsPred(const T& e);
	ListNodePosi<T> insertAsSucc(const T& e);
};

template<typename T>
class List {
private:
	int _size;
	ListNodePosi<T> header;
	ListNodePosi<T> trailer;

protected:
	void init();
	int clear();
	void copyNodes(ListNodePosi<T>, int);
	ListNodePosi<T> merge(ListNodePosi<T>, int, List<T>&, ListNodePosi<T>, int);
	void mergeSort(ListNodePosi<T>&, int);
	void selectionSort(ListNodePosi<T>, int);
	void insertionSort(ListNodePosi<T>, int);
	void radixSort(ListNodePosi<T>, int); // TODO

public:
	List() { init(); }
	List(const List<T>& L);
	List(const List<T>& L, Rank r, int n);
	List(ListNodePosi<T> p, int n);

	~List();

	Rank size() const { return _size; }
	bool empty() const { return _size <= 0; }
	T& operator[] (Rank r) const;
	ListNodePosi<T> first() const { return header->succ; }
	ListNodePosi<T> last() const { return trailer->pred; }
	bool valid(ListNodePosi<T> p) { return p && (trailer != p) && (header != p); }
	ListNodePosi<T> find(const T& e) const { return find(e, _size, trailer); }
	ListNodePosi<T> find(const T& e, int n, ListNodePosi<T> p) const;
	ListNodePosi<T> search(const T& e) const { return search(e, _size, trailer); }
	ListNodePosi<T> search(const T& e, int n, ListNodePosi<T> p) const;
	ListNodePosi<T> selectMax(ListNodePosi<T> p, int n);
	ListNodePosi<T> selectMax() { return selectMax(header->succ, _size); }
	ListNodePosi<T> insertAsFirst(const T& e);
	ListNodePosi<T> insertAsLast(const T& e);
	ListNodePosi<T> insert(ListNodePosi<T> p, const T& e);
	ListNodePosi<T> insert(const T& e, ListNodePosi<T> P);
	T remove(ListNodePosi<T> p);
	void merge(List<T>& L) { merge(header->succ, _size, L, L.header->succ, L._size); }
	void sort(ListNodePosi<T> p, int n);
	void sort() { sort(first(), _size); }
	int deduplicate();
	int uniquify();
	void reverse();
	void traverse(void(*)(T&));
	template<typename VST>
	void traverse(VST&);
};
