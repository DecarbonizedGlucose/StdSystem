#include "order.h"
#include "list.h"
#include <iostream>
using namespace std;

//Order::empty

ostream& operator<<(ostream& cout, Order& o)
{
	cout << o.orderId << '\t' << o.usrId << '\t' << o.req << '\t';
	switch (o.state)
	{
	case 0:
		cout << "未分配"; break;
	case 1:
		cout << "未完成"; break;
	case 2:
		cout << "已完成"; break;
	case 3:
		cout << "驳回"; break;
	case 4:
		cout << "订单取消"; break;
	default:
		cout << "你他妈是不是打错字了";
	}
	if (o.roomId != "none") cout << '\t' << o.roomId;
	cout << endl;
	return cout;
}

bool operator==(Order& o1, Order& o2)
{
	return (o1.usrId == o2.usrId) || (o1.orderId == o2.orderId);
}

void Order::showAll()
{
	ifstream ifs(ORDER_FILE, ios::in);
	int cnt = 0;
	if (!ifs.is_open())
	{
		cout << "[Info] 文件读取失败" << endl;
		ifs.close();
		return;
	}
	cout << "编号\t\t用户\t需求\t\t状态\t房间" << endl;
	string odid, urid, room;
	int req, state;
	while (ifs >> odid)
	{
		ifs >> urid >> req >> state >> room;
		cnt++;
		cout << odid << '\t' << urid << '\t' << req << '\t\t';
		switch (state)
		{
		case 0:
			cout << "未分配"; break;
		case 1:
			cout << "未完成"; break;
		case 2:
			cout << "已离店"; break;
		case 3:
			cout << "驳回"; break;
		case 4:
			cout << "订单取消"; break;
		default:
			cout << "你他妈是不是打错字了";
		}
		if (room != "none") cout << '\t' << room;
		cout << endl;
	}
	cout << "[Info] 共找到" << cnt << "条订单记录" << endl;
	ifs.close();
}

void Order::showOnes(string usrId)
{
	fstream ifs(ORDER_FILE, ios::in);
	string code, name, room;
	int num, state;
	List<Order> orders;
	while (ifs >> code)
	{
		ifs >> name >> num >> state;
		if (name == usrId)
			orders.addBack(Order(code, name, num, state, room));
	}
	if (!orders.length)
	{
		cout << endl << "[Info] 未找到相关订单" << endl << endl;
		ifs.close();
		return;
	}
	Node<Order>* f = orders.head->next;
	cout << "编号\t\t用户\t需求\t\t状态\t房间" << endl;
	while (f)
	{
		if (f->value.usrId == usrId)
			cout << f->value;
		f = f->next;
	}
	cout << "[Info] 共找到" << orders.length << "条订单记录" << endl;
	ifs.close();
}

List<Order>* Order::showUn()
{
	fstream ifs(ORDER_FILE, ios::in);
	string code, name, room;
	int num, state, cnt = 0;
	List<Order>* orders = new List<Order>;
	while (ifs >> code)
	{
		ifs >> name >> num >> state;
		orders->addBack(Order(code, name, num, state, room));
		if (state == 0) ++cnt;
	}
	if (!cnt)
	{
		cout << endl << "[Info] 未找到相关订单" << endl << endl;
		ifs.close();
		return nullptr;
	}
	Node<Order>* f = orders->head->next;
	cout << "编号\t\t用户\t需求\t\t状态\t房间" << endl;
	while (f)
	{
		if (f->value.state == 0)
			cout << f->value;
		f = f->next;
	}
	cout << "[Info] 共找到" << orders->length << "条订单记录" << endl;
	ifs.close();
	return orders;
}