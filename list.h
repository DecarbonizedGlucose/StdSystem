#pragma once
using namespace std;

/*
template<class Mem, class Ctn>
class Iter;
*/

template<class T>
class Node
{
public:
	T value;
	Node<T>* next;
	Node(T v, Node* n);
	//~Node();
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
	T& valueOf(int idx);
	T operator[](int idx);
	T front();
	T back();
	void reverse();
	void bubbleSort();
	~List();

	Node<T>* find(T con);

	/*
	list原始设计问题，加不了了
	// 以下是为范围for循环设计的

	Iter<T, List<T>> begin() const
	{
		return Iter<T, List<T>>(this, 1);
	}

	Iter<T, List<T>> end() const;
	{
		return Iter<T, List<T>>(this, length + 1);
	}*/
};

/*
template<class Mem, class Ctn>
class Iter
{
private:
	int _pos;
	const Ctn* _p_ctn;

public:
	Iter(const Ctn* _p_ctn, int pos) : _pos(pos), _p_ctn(_p_ctn) {}

	bool operator!=(const Iter& other) const
	{
		return _pos != other._pos;
	}

	Mem operator*() const
	{
		return _p_ctn->valueOf(_pos);
	}

	const Iter& operator++()
	{
		++_pos;
		return *this;
	}
};*/

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
{
}

template<class T>
List<T>::List(T* a, int len) // 有参构造
{
	for (int i = 0; i < len; ++i)
	{
		addBack(a[i]);
	}
}

template<class T>
List<T>::List(List<T>& _L) // 复制一个相同的链表
{
	Node<T>* cur = _L.head->next;
	while (cur)
	{
		addBack(cur->value);
		cur = cur->next;
	}
}

template<class T>
List<T>::List(List<T>& _L1, List<T>& _L2) // 融合两个有序链表
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

/*--------------------------   插入   ----------------------------*/

template<class T>
void List<T>::addBack(T value) // 尾插
{
	Node<T>* newElement = new Node<T>(value, nullptr);
	if (empty()) head->next = newElement;
	else tail()->next = newElement;
	++length;
}

template<class T>
void List<T>::addFront(T value) // 头插
{
	Node<T>* newFirstElem = new Node<T>(value, head->next);
	head->next = newFirstElem;
	++length;
}

template<class T>
void List<T>::add(int idx, T value) // 任意位置插入
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

/*--------------------------   删改   ----------------------------*/

template<class T>
void List<T>::modify(int idx, T newv) // 修改
{
	ptrOf(idx)->value = newv;
}

template<class T>
void List<T>::popFront() // 头删
{
	if (empty()) throw "Listlist is empty.";
	Node<T>* toDel = head->next;
	head->next = toDel->next;
	delete toDel;
	toDel = nullptr;
	--length;
}

template<class T>
void List<T>::popBack() // 尾删
{
	if (empty()) throw "Listlist is empty.";
	if (length == 1) { popFront(); return; }
	Node<T>* Lsub2 = ptrOf(length - 2);
	delete Lsub2->next;
	Lsub2->next = nullptr;
	--length;
}

template<class T>
void List<T>::pop(int idx) // 任意位置删
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

/*--------------------------   查   ----------------------------*/

template<class T>
bool List<T>::empty() // 判断是否为空
{
	return head->next == nullptr;
}

template<class T>
Node<T>* List<T>::tail() // 返回指向末元素的指针
{
	if (empty()) return nullptr;
	Node<T>* nextptr = head->next;
	while (nextptr->next) nextptr = nextptr->next;
	return nextptr;
}

template<class T>
Node<T>* List<T>::ptrOf(int idx) // 根据序号索引结点位置
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
T& List<T>::valueOf(int idx) // 根据序号索引结点数据
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

/*--------------------------   调整顺序   ----------------------------*/

template<class T>
void List<T>::reverse() // 逆置
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
void List<T>::bubbleSort() // 排序，采用冒泡，只交换数据域
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

template<class T>
List<T>::~List()
{
	while (length > 0)
	{
		popFront();
	}
	delete head;
}

template<class T>
Node<T>* List<T>::find(T con)
{
	Node<T>* f = head->next;
	while (f)
	{
		if (f->value == con) return f;
		f = f->next;
	}
	return nullptr;
}