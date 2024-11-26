#include <string>
#include <fstream>
#include <iostream>
#include "admin.h"
#include "globalfile.h"
#include "order.h"
#include "list.h"
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
	//Link<Order> orders;
	ifstream ifs(ORDER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "[Info] �ļ���ȡʧ��" << endl;
		ifs.close();
		return;
	}
	cout << "���\t�û�\t����\t״̬" << endl;
	string odid, urid;
	int req, state;
	while (ifs >> odid)
	{
		ifs >> urid >> req >> state;
		//orders.addBack(Order(odid, urid, req, state));
		cout << odid << '\t' << urid << '\t' << req << '\t';
		switch (state)
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
		cout << endl;
	}
	ifs.close();
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