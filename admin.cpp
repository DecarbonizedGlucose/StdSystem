#include <string>
#include <fstream>
#include <iostream>
#include "admin.h"
#include "globalfile.h"
#include "order.h"
#include "list.h"
#include "room.h"
using namespace std;

Admin::Admin() {}

Admin::Admin(string id, string psw)
{
	usrId = id;
	usrPsw = psw;
}

void Admin::operMenu()
{
	system("cls");
	cout << "==================" << endl;
	cout << " 1. �鿴����ԤԼ" << endl;
	cout << " 2. �鿴���з���Ա" << endl;
	cout << " 0. �˳��˺�" << endl;
	cout << "==================" << endl;
	string choice;
	while (true)
	{
		cout << "<Input> ";
		getline(cin, choice);
		if (choice == "1")
		{
			// show all order
			showAllOrder();
		}
		else if (choice == "2")
		{
			// show all clerks
			showAllClerk();
		}
		else if (choice == "0")
		{
			return;
		}
		else
		{
			cout << "[Info] ������������������" << endl;
		}
	}
}

void Admin::showAllOrder()
{
	Order::showAll();
}

void Admin::showAllClerk()
{
	ifstream ifs(CLERK_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "[Info] �ļ���ȡʧ��" << endl;
		ifs.close();
		return;
	}
	cout << "�û���    |    ����" << endl;
	string name, psw;
	while (ifs >> name)
	{
		ifs >> psw;
		cout << name << "    |    " << psw << endl;
	}
	ifs.close();
}

void Admin::showAllRoom()
{
	Room::showAll();
}