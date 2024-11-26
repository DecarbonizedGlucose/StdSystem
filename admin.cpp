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
	cout << " 1. 查看所有预约" << endl;
	cout << " 2. 查看所有服务员" << endl;
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
			// show all clerks
			showAllClerk();
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

void Admin::showAllOrder()
{
	//Link<Order> orders;
	ifstream ifs(ORDER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "[Info] 文件读取失败" << endl;
		ifs.close();
		return;
	}
	cout << "编号\t用户\t需求\t状态" << endl;
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
		cout << endl;
	}
	ifs.close();
}

void Admin::showAllClerk()
{
	ifstream ifs(CLERK_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "[Info] 文件读取失败" << endl;
		ifs.close();
		return;
	}
	cout << "用户名    |    密码" << endl;
	string name, psw;
	while (ifs >> name)
	{
		ifs >> psw;
		cout << name << "    |    " << psw << endl;
	}
	ifs.close();
}