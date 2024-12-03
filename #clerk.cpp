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
	while (1)
	{
		cout << "==================" << endl;
		cout << " 1. �鿴���ж���" << endl;
		cout << " 2. ������" << endl;
		cout << " 3. �鿴ĳ�˶���" << endl;
		cout << " 4. �鿴δ������" << endl;
		cout << " 5. �鿴���з���" << endl;
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
				break;
			}
			else if (choice == "2")
			{
				// manage orders
				manageOrder();
				break;
			}
			else if (choice == "3")
			{
				showOnesOrder();
				break;
			}
			else if (choice == "4")
			{
				showUnOrder();
				break;
			}
			else if (choice == "5")
			{
				showAllRoom();
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

void Clerk::showAllOrder()
{
	Order::showAll();
}

void Clerk::showOnesOrder()
{
	string name;
	cout << "�������û�����" << endl;
	cout << "<Input> ";
	getline(cin, name);
	Order::showOnes(name);
}

void Clerk::manageOrder()
{
	List<Order>* orders = Order::showUn();
	if (orders == nullptr) return;
	cout << "��Ҫ���ĸ��������䣿" << endl;
	cout << "<Input> " << endl;
	string orderId;
	getline(cin, orderId);
	if (Node<Order>*o=orders->find(Order(orderId, "", 0, 0, "")))
	{
		if (o->value.state == 0)
		{
			List<Room>* rs = Room::showAvailable();
			if (rs == nullptr) return;
			Node<Room>* f = rs->head->next;
			while (f)
			{
				if (f->value.roomSize >= o->value.req)
				{
					break;
				}
			}
			if (f)
			{
				f->value.roomState = 1;
				ofstream ofs1(ROOM_FILE, ios::out | ios::trunc);
				if (!ofs1.is_open())
				{
					cout << "[Info] ����ʧ��" << endl;
					ofs1.close();
					delete orders;
					delete rs;
					return;
				}
				f = rs->head->next;
				o->value.state = 1;
				o->value.roomId = f->value.roomId;
				while (f)
				{
					ofs1 << f->value.roomId << " " << f->value.roomSize << " " << f->value.roomState << endl;
				}
				ofstream ofs2(ORDER_FILE, ios::out | ios::trunc);
				if (!ofs2.is_open())
				{
					cout << "[Info] ����ʧ��" << endl;
					ofs2.close();
					delete orders;
					delete rs;
					return;
				}
				
				Node<Order>* n = orders->head->next;
				while (n)
				{
					ofs2 << n->value.orderId << ' ' << n->value.usrId << ' ';
					ofs2 << n->value.req << ' ' << n->value.state << ' ';
					ofs2 << n->value.roomId << endl;
					n = n->next;
				}
				ofs2.close();

				cout << "[Info] ����ɹ�" << endl;
				delete orders;
				delete rs;
				return;
			}
			else
			{
				cout << "[Info] û�к��ʴ�С�ķ���" << endl;
				delete orders;
				delete rs;
				return;
			}
		}
	}
	cout << "[Info] ���������ڻ��ѷ���" << endl;
	delete orders;
}

void Clerk::showAllRoom()
{
	Room::showAll();
}

void Clerk::showUnOrder()
{
	Order::showUn();
}