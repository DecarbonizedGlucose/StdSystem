#include <string>
#include "customer.h"
#include "globalfile.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>
#include "list.h"
#include "order.h"
#include <list>
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
		//cin >> choice;
		if (choice == "1")
		{
			// create and submit an order
			submitOrder();
		}
		else if (choice == "2")
		{
			// show my orders
			showMyOrder();
		}
		else if (choice == "3")
		{
			// cancel my order
			cancelOrder();
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
	string num;
	//getline(cin, num); // 这他妈哪来的bug
	//cin >> num;
	//cin.clear();
	//cin.sync(); // 这玩意在vs里没用
	//cin.ignore();
	while (true)
	{
		cout << "请输入人数：" << endl;
		cout << "<Input> ";
		getline(cin, num);
		if (num == "1" || num == "2" || num == "3" || num == "4") break;
		else if (num == "0")
		{
			cout << "[Info] 已取消" << endl;
			ofs.close();
			return;
		}
		else cout << "[Info] 输入有误，请重新输入" << endl;
	}
	ofs << code << " " << usrId << " " << num << " 0 none" << endl;
	ofs.close();
	cout << "[Info] 提交成功" << endl;
}

void Cust::showMyOrder()
{
	fstream ifs(ORDER_FILE, ios::in);
	string code, name, room;
	int num, state;
	List<Order> orders;
	while (ifs >> code)
	{
		ifs >> name >> num >> state;
		if (name == this->usrId)
		{
			orders.addBack(Order(code, name, num, state, room));
			//cout << "成功添加一个" << endl;
		}
	}
	Node<Order>* f = orders.head->next;
	cout << "编号\t\t用户\t需求\t状态\t房间" << endl;
	while (f)
	{
		cout << f->value;
		f = f->next;
	}
	ifs.close();
}

void Cust::cancelOrder()
{

}