#include "order.h"
#include <iostream>
using namespace std;

ostream& operator<<(ostream& cout, Order& o)
{
	cout << o.orderId << '\t' << o.usrId << '\t' << o.req << '\t';
	switch (o.state)
	{
	case 0:
		cout << "未处理"; break;
	case 1:
		cout << "已处理 未完成"; break;
	case 2:
		cout << "已完成"; break;
	case 3:
		cout << "驳回"; break;
	case 4:
		cout << "用户撤销"; break;
	default:
		cout << "你他妈是不是打错字了";
	}
	if (o.roomId != "none") cout << '\t' << o.roomId;
	cout << endl;
	return cout;
}