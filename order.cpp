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
		cout << "δ����"; break;
	case 1:
		cout << "δ���"; break;
	case 2:
		cout << "�����"; break;
	case 3:
		cout << "����"; break;
	case 4:
		cout << "����ȡ��"; break;
	default:
		cout << "�������ǲ��Ǵ������";
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
		cout << "[Info] �ļ���ȡʧ��" << endl;
		ifs.close();
		return;
	}
	cout << "���\t\t�û�\t����\t״̬\t����" << endl;
	string odid, urid, room;
	int req, state;
	while (ifs >> odid)
	{
		ifs >> urid >> req >> state >> room;
		cout << odid << '\t' << urid << '\t' << req << '\t';
		switch (state)
		{
		case 0:
			cout << "δ����"; break;
		case 1:
			cout << "δ���"; break;
		case 2:
			cout << "�����"; break;
		case 3:
			cout << "����"; break;
		case 4:
			cout << "����ȡ��"; break;
		default:
			cout << "�������ǲ��Ǵ������";
		}
		if (room != "none") cout << '\t' << room;
		cout << endl;
	}
	ifs.close();
}

void Order::showOnes()
{
	
}