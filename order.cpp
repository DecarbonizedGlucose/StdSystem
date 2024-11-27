#include "order.h"
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
	return o1.usrId == o2.usrId;
}

void Order::showAll()
{
	ifstream ifs(ORDER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "[Info] 文件读取失败" << endl;
		ifs.close();
		return;
	}
	cout << "编号\t\t用户\t需求\t状态\t房间" << endl;
	string odid, urid, room;
	int req, state;
	while (ifs >> odid)
	{
		ifs >> urid >> req >> state >> room;
		cout << odid << '\t' << urid << '\t' << req << '\t';
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
	ifs.close();
}

void Order::showOnes()
{
	
}