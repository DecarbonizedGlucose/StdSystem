#include "order.h"
#include <iostream>
using namespace std;

ostream& operator<<(ostream& cout, Order& o)
{
	cout << o.orderId << '\t' << o.usrId << '\t' << o.req << '\t';
	switch (o.state)
	{
	case 0:
		cout << "δ����"; break;
	case 1:
		cout << "�Ѵ��� δ���"; break;
	case 2:
		cout << "�����"; break;
	case 3:
		cout << "����"; break;
	case 4:
		cout << "�û�����"; break;
	default:
		cout << "�������ǲ��Ǵ������";
	}
	if (o.roomId != "none") cout << '\t' << o.roomId;
	cout << endl;
	return cout;
}