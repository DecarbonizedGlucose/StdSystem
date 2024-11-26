#include <string>
#include "clerk.h"
#include <iostream>
#include <fstream>
#include "globalfile.h"
using namespace std;

Clerk::Clerk() {}

Clerk::Clerk(string id, string psw) : usrId(id), usrPsw(psw) {}

void Clerk::operMenu()
{
	system("cls");
	cout << "==================" << endl;
	cout << " 1. �鿴����ԤԼ" << endl;
	cout << " 2. ����ԤԼ" << endl;
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
			// manage orders
			manageOrder();
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

void Clerk::showAllOrder()
{
	ifstream ifs(ORDER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "[Info] �ļ���ȡʧ��" << endl;
		ifs.close();
		return;
	}
	cout << "���\t\t�û�\t����\t״̬" << endl;
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

void Clerk::manageOrder()
{
}