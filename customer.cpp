#include <string>
#include "customer.h"
#include "globalfile.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>
#include "list.h"
#include "order.h"
#define _CRT_SECURE_NO_WARNINGS 1 
using namespace std;

Cust::Cust() {}

Cust::Cust(string id, string psw) : usrId(id), usrPsw(psw) {}

void Cust::operMenu()
{
	system("cls");
	cout << "==================" << endl;
	cout << " 1. 创建提交预约" << endl;
	cout << " 2. 查看我的预约" << endl;
	cout << " 3. 取消预约" << endl;
	cout << " 0. 退出账号" << endl;
	cout << "==================" << endl;
	string choice;
	while (true)
	{
		cout << "<Input> ";
		getline(cin, choice);
		if (choice == "1")
		{
			// create and submit an order
			submitOrder();
		}
		else if (choice == "2")
		{
			// show my orders
		}
		else if (choice == "3")
		{
			// cancel my order
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

void Cust::submitOrder()
{
	time_t now = time(nullptr);
	tm* ltm = localtime(&now);
	stringstream sst;
	int temp;
	sst << "R";
	sst << 1900 + ltm->tm_year;
	temp = ltm->tm_mon + 1;
	if (temp < 10) sst << '0' << temp;
	else sst << temp;
	temp = ltm->tm_mday;
	if (temp < 10) sst << '0' << temp;
	else sst << temp;
	temp = ltm->tm_hour;
	if (temp < 10) sst << '0' << temp;
	else sst << temp;
	temp = ltm->tm_min;
	if (temp < 10) sst << '0' << temp;
	else sst << temp;
	temp = ltm->tm_sec;
	if (temp < 10) sst << '0' << temp;
	else sst << temp;
	string code;
	sst >> code;
	ofstream ofs(ORDER_FILE, ios::app);
	cout << "请输入人数：" << endl;
	cout << "<Input> ";
	string num;
	getline(cin, num);
	ofs << code << " " << usrId << " " << num << " 0" << endl;
	ofs.close();
	cout << "[Info] 提交成功" << endl;
}

ostream& operator<<(ostream& cout, Order o)
{
	cout << o.orderId << " " << o.usrId << " " << o.req << " " << o.state << endl;
	return cout;
}

void Cust::cancelOrder()
{
	fstream ifs(ORDER_FILE, ios::in);
	string code, name;
	int num, state;
	List<Order> orders;
	while (ifs >> code)
	{
		ifs >> name >> num >> state;
		/*if (name == this->usrName)
			orders.addBack(Order(code, name, num, state));*/
		/*for (int i = 1; i < orders.length; ++i)
		{
			cout << orders[i];
		}*/
	}
	ifs.close();
}