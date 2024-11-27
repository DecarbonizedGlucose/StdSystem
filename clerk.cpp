#include <string>
#include "clerk.h"
#include <iostream>
#include <fstream>
#include "order.h"
#include "globalfile.h"
#include "room.h"
using namespace std;

Clerk::Clerk() {}

Clerk::Clerk(string id, string psw) : usrId(id), usrPsw(psw) {}

void Clerk::operMenu()
{
	system("cls");
	cout << "==================" << endl;
	cout << " 1. 查看所有预约" << endl;
	cout << " 2. 处理预约" << endl;
	cout << " 0. 退出账号" << endl;
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
			cout << "[Info] 输入有误，请重新输入" << endl;
		}
	}
}

void Clerk::showAllOrder()
{
	Order::showAll();
}

void Clerk::showOnesOrder()
{
	Order::showOnes();
}

void Clerk::manageOrder()
{
}

void Clerk::showAllRoom()
{
	Room::showAll();
}