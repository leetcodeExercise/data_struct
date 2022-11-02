#pragma once
#include <cstdlib>
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

template<typename T>
ListNodePosi<T> ListNode<T>::insertAsPred(const T& e)
{
	ListNodePosi<T> x = new ListNode(e, pred, this);
	pred->succ = x;
	pred = x;
	return x;
}

template<typename T>
ListNodePosi<T> ListNode<T>::insertAsSucc(const T& e)
{
	ListNodePosi<T> x = new ListNode(e, this, succ);
	succ->pred = x;
	succ = x;
	return x;
}

template<typename T>
ListNodePosi<T> List<T>::insertAsFirst(const T& e)
{
	_size++;
	return header->insertAsSucc(e);
}

template<typename T>
ListNodePosi<T> List<T>::insertAsLast(const T& e)
{
	_size++;
	return trailer->insertAsPred(e);
}

template<typename T>
ListNodePosi<T> List<T>::insert(ListNodePosi<T> p, const T& e)
{
	_size++;
	return p->insertAsSucc(e);
}

template<typename T>
ListNodePosi<T> List<T>::insert(const T& e, ListNodePosi<T> p)
{
	_size++;
	return p->insertAsPred(e);
}

template<typename T> void List<T>::init() 
{
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer;
	header->pred = nullptr;
	trailer->pred = header;
	trailer->succ = nullptr;
	_size = 0;
}

template<typename T> int List<T>::clear()
{
	int oldSize = _size;
	while (0 < _size)
		remove(header->succ);
	return oldSize;
}

template<typename T> void List<T>::copyNodes(ListNodePosi<T> p, int n)
{
	init();
	while (n--)
	{
		insertAsLast(p->data);
		p = p->succ;
	}
}

template<typename T>
ListNodePosi<T> List<T>::merge(ListNodePosi<T> p, int n, List<T>& L, ListNodePosi<T> q, int m)
{
	ListNodePosi<T> pp = p->pred;
	while ((0 < m) && (q != p))
		if ((0 < n) && (p->data <= q->data)) {
			p = p->succ;
			n--;
		} else {
			insert((L.remove(q = q->succ)->pred), p);
			m--;
		}
	return pp->succ;
}

template<typename T>
void List<T>::mergeSort(ListNodePosi<T>& p, int n)
{
	if (n < 2) return;
	int m = n >> 1;
	ListNodePosi<T> q = p;
	for (int i = 0; i < m; i++)
		q = q->succ;
	mergeSort(p, m);
	mergeSort(q, n - m);
	p = merge(p, m, *this, q, n - m);
}

template<typename T>
ListNodePosi<T> List<T>::selectMax(ListNodePosi<T> p, int n)
{
	ListNodePosi<T> max = p;
	for (ListNodePosi<T> cur = p; 1 < n; n--)
		if (!It((cur = cur->succ)->data, max->data))
			max = cur;
	return max;
}

template<typename T>
void List<T>::selectionSort(ListNodePosi<T> p, int n)
{
	ListNodePosi<T> head = p->pred;
	ListNodePosi<T> tail = p;
	for (int i = 0; i < n; i ++)
		tail = tail->succ;
	while (1 < n)
	{
		ListNodePosi<T> max = selectMax(head->succ, n);
		insert(remove(max), tail);
		tail = tail->pred;
		n--;
	}
}

template<typename T>
void List<T>::insertionSort(ListNodePosi<T> p, int n)
{
	for (int r = 0; r < n; r++)
	{
		insert(search(p->data, r, p), p->data);
		p = p->succ;
		remove(p->pred);
	}
}

template<typename T>
ListNodePosi<T> List<T>::search(const T& e, int n, ListNodePosi<T> p) const
{
	do {
		p = p->pred;
		n--;
	} while ((-1 < n) && (e < p->data));
	return p;
}

template<typename T>
List<T>::List(ListNodePosi<T> p, int n) { copyNodes(p, n); }

template<typename T>
List<T>::List(const List<T>& L) { coptNodes(L.first(), L.size()); }

template<typename T>
List<T>::List(const List<T>& L, Rank r, int n)
{
	ListNodePosi<T> p = L.first();
	while (0 < r--)
		p = p->succ;
	copyNodes(p, n);
}

template<typename T>
List<T>::~List()
{
	clear();
	delete header;
	delete trailer;
}

template<typename T>
T& List<T>::operator[] (Rank r) const
{
	ListNodePosi<T> p = first();
	while (0 < r--)
	p = p->succ;
	return p->data;
}

template<typename T>
ListNodePosi<T> List<T>::find(const T& e, int n, ListNodePosi<T> p) const
{
	while (0 < n--)
		if (e == (p = p->pred)->data) return p;
	return nullptr;
}

template<typename T>
T List<T>::remove(ListNodePosi<T> p)
{
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}

template<typename T>
void List<T>::sort(ListNodePosi<T> p, int n)
{
	switch (std::rand() % 4)
	{
		case 1: insertionSort(p, n); break;
		case 2: selectionSort(p, n); break;
		case 3: mergeSort(p, n); break;
		default: radixSort(p, n); break; // TODO
	}
}

template<typename T>
int List<T>::deduplicate()
{
	int oldSize = _size;
	ListNodePosi<T> p = first();
	for (Rank r = 0; p != trailer; p = p->succ)
		if (ListNodePosi<T> q = find(p->data, r, p))
			remove(q);
		else r++;
	return oldSize - _size;
}

template<typename T>
int List<T>::uniquify()
{
	if (_size < 2) return 0;
	int oldSize = _size;
	ListNodePosi<T> p = first();
	ListNodePosi<T> q;
	while (trailer != (q = p->succ))
		if (p->data != q->data)
			p = q;
		else remove(q);
	return oldSize - _size;
}

template<typename T>
void List<T>::reverse()
{
	ListNodePosi<T> p = header;
	ListNodePosi<T> q = trailer;
	for (int i = 1; i < _size; i += 2)
		swap((p = p->succ)->data, (q = q->pred)->data);
}

template<typename T>
void List<T>::traverse(void(*visit)(T&))
{
	for (ListNodePosi<T> p = header->succ; p != trailer; p = p->succ)
		visit(p->date);
}

template<typename T> template<typename VST>
void List<T>::traverse(VST& visit)
{
	for (ListNodePosi<T> p = header->succ; p != trailer; p = p->succ)
		visit(p->date);
}
