#pragma once
using namespace std;

template<class T>
class Node
{
public:
	T value;
	Node* next;
	Node(T v, Node* n);
};

template<class T>
void swapElem(T& a, T& b);

template<class T>
class List
{
public:
	Node<T>* head = new Node<T>(T(), nullptr);
	int length = 0;
	List();
	List(T* a, int len);
	List(List& _L);
	List(List& l1, List& l2);
	void addBack(T value);
	void addFront(T value);
	void add(int idx, T value);
	void modify(int idx, T newValue);
	void popFront();
	void popBack();
	void pop(int idx);
	bool empty();
	Node<T>* tail();
	Node<T>* ptrOf(int idx);
	T valueOf(int idx);
	T operator[](int idx);
	T front();
	T back();
	void reverse();
	void bubbleSort();
};