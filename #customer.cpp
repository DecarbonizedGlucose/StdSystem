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
	while (1)
	{
		cout << "==================" << endl;
		cout << " 1. �����ύԤԼ" << endl;
		cout << " 2. �鿴�ҵ�ԤԼ" << endl;
		cout << " 3. ȡ��ԤԼ" << endl;
		cout << " 0. �˳��˺�" << endl;
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
				break;
			}
			else if (choice == "2")
			{
				// show my orders
				showMyOrder();
				break;
			}
			else if (choice == "3")
			{
				// cancel my order
				cancelOrder();
				break;
			}
			else if (choice == "0")
			{
				return;
			}
			else
			{
				cout << "[Info] ������������������" << endl;
				break;
			}
		}
		system("pause");
		system("cls");
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
	//getline(cin, num); // ������������bug
	//cin >> num;
	//cin.clear();
	//cin.sync(); // ��������vs��û��
	//cin.ignore();
	while (true)
	{
		cout << "����������������0���أ���" << endl;
		cout << "<Input> ";
		getline(cin, num);
		if (num == "1" || num == "2" || num == "3" || num == "4") break;
		else if (num == "0")
		{
			cout << "[Info] ��ȡ��" << endl;
			ofs.close();
			return;
		}
		else cout << "[Info] ������������������" << endl;
	}
	ofs << code << " " << usrId << " " << num << " 0 none" << endl;
	ofs.close();
	cout << "[Info] �ύ�ɹ�" << endl;
}

void Cust::showMyOrder()
{
	fstream ifs(ORDER_FILE, ios::in);
	string code, name, room;
	int req, state;
	List<Order> orders;
	while (ifs >> code)
	{
		ifs >> name >> req >> state >> room;
		if (name == this->usrId)
		{
			orders.addBack(Order(code, name, req, state, room));
		}
	}
	if (orders.length == 0)
	{
		cout << endl << "[Info] δ�ҵ���ض���" << endl << endl;
		ifs.close();
		return;
	}
	Node<Order>* f = orders.head->next;
	cout << "���          |  �û�         |   ����    |  ״̬    | ����" << endl;
	while (f)
	{
		cout << f->value;
		f = f->next;
	}
	cout << "[Info] ���ҵ�" << orders.length << "��������¼" << endl;
	ifs.close();
}

void Cust::cancelOrder()
{
	fstream ifs(ORDER_FILE, ios::in);
	string code, name, room;
	int req, state, cnt = 0;
	List<Order> orders;
	while (ifs >> code)
	{
		ifs >> name >> req >> state >> room;
		if (name == this->usrId) ++cnt;
		orders.addBack(Order(code, name, req, state, room));
	}
	if (cnt == 0)
	{
		cout << endl << "[Info] δ�ҵ���ض���" << endl << endl;
		ifs.close();
		return;
	}
	Node<Order>* f = orders.head->next;
	cout << "���          |  �û�         |   ����    |  ״̬    | ����" << endl;
	while (f)
	{
		if (f->value.usrId == this->usrId)
			cout << f->value;
		f = f->next;
	}
	cout << "[Info] ���ҵ�" << cnt << "��������¼" << endl;
	ifs.close();
	cout << endl << "������Ҫȡ���Ķ���������0���أ���" << endl;
	string iptId;
	Node<Order>* n;
	while (true)
	{
		cout << "<Input> ";
		getline(cin, iptId);
		n = orders.find(Order(iptId, "", 0, 0, ""));
		if (n) break;
		else if (iptId == "0") 
		{
			cout << "[Info] �ѷ����޸�" << endl;
			return;
		}
		else cout << "[Info] ������������������" << endl;
	}
	n->value.state = 4;
	n->value.roomId = "none";
	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	if (!ofs.is_open())
	{
		cout << "[Info] �޸�ʧ��" << endl;
		ofs.close();
		return;
	}
	n = orders.head->next;
	while (n)
	{
		ofs << n->value.orderId << ' ' << n->value.usrId << ' ';
		ofs << n->value.req << ' ' << n->value.state << ' ';
		ofs << n->value.roomId << endl;
		n = n->next;
	}
	ofs.close();
	cout << "[Info] �����ɹ�" << endl;
}

bool Cust::find(string usrId)
{
	ifstream ifs(CUSTOMER_FILE, ios::in);
	string name, psw;
	while (ifs >> name)
	{
		ifs >> psw;
		if (name == usrId)
		{
			ifs.close();
			return true;
		}
	}
	ifs.close();
	return false;
}

void Cust::showAllTime()
{
	ifstream ifs(CUSTOMER_FILE, ios::in);
	string name, psw;
	while (ifs >> name)
	{
		ifs >> psw;
		cout << name << endl;
	}
	ifs.close();
}

void Cust::showAllASCII()
{
	List<string> names;
	ifstream ifs(CUSTOMER_FILE, ios::in);
	string name, psw;
	while (ifs >> name)
	{
		ifs >> psw;
		names.addBack(name);
	}
	ifs.close();
	names.bubbleSort();
	Node<string>* f = names.head->next;
	while (f)
	{
		cout << f->value << endl;
		f = f->next;
	}
}