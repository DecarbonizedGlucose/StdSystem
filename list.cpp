#include "list.h"
using namespace std;

template<class T>
Node<T>::Node(T v, Node<T>* n) : value(v), next(n) {}

template<class T>
void swapElem(T& a, T& b)
{
	T t = a;
	a = b;
	b = t;
}

template<class T>
List<T>::List() 
{}

template<class T>
List<T>::List(T* a, int len) // �вι���
{
	for (int i = 0; i < len; ++i)
	{
		addBack(a[i]);
	}
}

template<class T>
List<T>::List(List<T>& _L) // ����һ����ͬ������
{
	Node<T>* cur = _L.head->next;
	while (cur)
	{
		addBack(cur->value);
		cur = cur->next;
	}
}

template<class T>
List<T>::List(List<T>& _L1, List<T>& _L2) // �ں�������������
{
	if (_L1.empty() || _L2.empty())
	{
		head = _L1.empty() ? _L2.head : _L1.head;
		(_L1.empty() ? _L2 : _L1).head->next = nullptr;
		return;
	}
	Node<T>* pre = _L1.head->next->value <= _L2.head->next->value ? _L1.head->next : _L2.head->next;
	head->next = pre;
	Node<T>* cur1 = pre->next;
	Node<T>* cur2 = _L1.head->next->value <= _L2.head->next->value ? _L2.head->next : _L1.head->next->next;

	while (cur1 != nullptr && cur2 != nullptr)
	{
		if (cur1->value <= cur2->value)
		{
			pre->next = cur1;
			pre = cur1;
			cur1 = cur1->next;
		}
		else
		{
			pre->next = cur2;
			pre = cur2;
			cur2 = cur2->next;
		}
	}
	pre->next = cur1 == nullptr ? cur2 : cur1;
	_L1.head = nullptr;
	_L2.head = nullptr;
}

/*--------------------------   ����   ----------------------------*/

template<class T>
void List<T>::addBack(T value) // β��
{
	Node<T>* newElement = new Node<T>(value, nullptr);
	if (empty()) head->next = newElement;
	else tail()->next = newElement;
	++length;
}

template<class T>
void List<T>::addFront(T value) // ͷ��
{
	Node<T>* newFirstElem = new Node<T>(value, head->next);
	head->next = newFirstElem;
	++length;
}

template<class T>
void List<T>::add(int idx, T value) // ����λ�ò���
{
	if (idx > length - 1) throw "Listlist is not so long.";
	if (idx == 0)
	{
		addFront(value);
		return;
	}
	Node<T>* former = ptrOf(idx - 1);
	Node<T>* newElement = new Node<T>(value, former->next);
	former->next = newElement;
	++length;
}

/*--------------------------   ɾ��   ----------------------------*/

template<class T>
void List<T>::modify(int idx, T newv) // �޸�
{
	ptrOf(idx)->value = newv;
}

template<class T>
void List<T>::popFront() // ͷɾ
{
	if (empty()) throw "Listlist is empty.";
	Node<T>* toDel = head->next;
	head->next = toDel->next;
	delete toDel;
	toDel = nullptr;
	--length;
}

template<class T>
void List<T>::popBack() // βɾ
{
	if (empty()) throw "Listlist is empty.";
	if (length == 1) { popFront(); return; }
	Node<T>* Lsub2 = ptrOf(length - 2);
	delete Lsub2->next;
	Lsub2->next = nullptr;
	--length;
}

template<class T>
void List<T>::pop(int idx) // ����λ��ɾ
{
	if (idx == 0) { popFront(); return; }
	if (idx == length - 1) { popBack(); return; }
	Node<T>* former = ptrOf(idx - 1);
	Node<T>* toDel = former->next;
	Node<T>* latter = toDel->next;
	delete toDel;
	toDel = nullptr;
	former->next = latter;
	--length;
}

/*--------------------------   ��   ----------------------------*/

template<class T>
bool List<T>::empty() // �ж��Ƿ�Ϊ��
{
	return head->next == nullptr;
}

template<class T>
Node<T>* List<T>::tail() // ����ָ��ĩԪ�ص�ָ��
{
	if (empty()) return nullptr;
	Node<T>* nextptr = head->next;
	while (nextptr->next) nextptr = nextptr->next;
	return nextptr;
}

template<class T>
Node<T>* List<T>::ptrOf(int idx) // ��������������λ��
{
	if (empty()) throw "Listlist is empty!";
	if (idx + 1 > length) throw "Listlist is not so long.";
	Node<T>* nptr = head->next;
	for (int i = 0; i < idx; ++i)
	{
		nptr = nptr->next;
	}
	return nptr;
}

template<class T>
T List<T>::valueOf(int idx) // ������������������
{
	return ptrOf(idx)->value;
}

template<class T>
T List<T>::operator[](int idx)
{
	return ptrOf(idx)->value;
}

template<class T>
T List<T>::front()
{
	if (empty()) throw "Listlist is empty.";
	return head->next->value;
}

template<class T>
T List<T>::back()
{
	if (empty()) throw "Listlist is empty.";
	return tail()->value;
}

/*--------------------------   ����˳��   ----------------------------*/

template<class T>
void List<T>::reverse() // ����
{
	Node<T>* pre = nullptr;
	Node<T>* temp = head->next;
	Node<T>* nextptr = temp;
	while (temp)
	{
		nextptr = nextptr->next;
		temp->next = pre;
		pre = temp;
		temp = nextptr;
	}
	head->next = pre;
}

template<class T>
void List<T>::bubbleSort() // ���򣬲���ð�ݣ�ֻ����������
{
	if (length < 2) return;
	for (int i = 0; i < length; ++i)
	{
		for (Node<T>* i = head->next; i->next; i = i->next)
		{
			if (i->value > i->next->value)
				swapElem(i->value, i->next->value);
		}
	}
}