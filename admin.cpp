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
	cout << "=============================" << endl;
	cout << " 1. 查看所有订单" << endl;
	cout << " 2. 查看所有服务员" << endl;
	cout << " 3. 查看所有房间" << endl;
	cout << " 4. 按注册时间顺序显示所有用户" << endl;
	cout << " 5. 按字典顺序显示所有用户" << endl;
	cout << " 6. 查找用户是否存在" << endl;
	cout << " 0. 退出账号" << endl;
	cout << "=============================" << endl;
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
		else if (choice == "3")
		{
			showAllRoom();
		}
		else if (choice == "4")
		{
			showAllCustTime();
		}
		else if (choice == "5")
		{
			showAllCustASCII();
		}
		else if (choice == "6")
		{
			custDoExist();
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
	Order::showAll();
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

void Admin::showAllRoom()
{
	Room::showAll();
}

void Admin::custDoExist()
{
	string name;
	cout << "请输入用户名：" << endl;
	cout << "<Input> ";
	getline(cin, name);
	if (Cust::find(name))
	{
		cout << "[Info] 该用户存在" << endl;
	}
	else
	{
		cout << "[Info] 该用户不存在" << endl;
	}
}

void Admin::showAllCustTime()
{
	Cust::showAllTime();
}

void Admin::showAllCustASCII()
{
	Cust::showAllASCII();
}