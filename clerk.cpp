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
	std::cout << "==================" << endl;
	std::cout << " 1. 查看所有订单" << endl;
	std::cout << " 2. 处理订单" << endl;
	std::cout << " 3. 查看某人订单" << endl;
	std::cout << " 4. 查看所有房间" << endl;
	std::cout << " 0. 退出账号" << endl;
	std::cout << "==================" << endl;
	string choice;
	while (true)
	{
		std::cout << "<Input> ";
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
		else if (choice == "3")
		{
			showOnesOrder();
		}
		else if (choice == "4")
		{
			showAllRoom();
		}
		else if (choice == "0")
		{
			return;
		}
		else
		{
			std::cout << "[Info] 输入有误，请重新输入" << endl;
		}
	}
}

void Clerk::showAllOrder()
{
	Order::showAll();
}

void Clerk::showOnesOrder()
{
	string name;
	std::cout << "请输入用户名：" << endl;
	std::cout << "<Input> ";
	getline(cin, name);
	Order::showOnes(name);
}

void Clerk::manageOrder()
{
	List<Order>* orders = Order::showUn();
	if (orders == nullptr) return;
	std::cout << "你要给哪个订单分配？" << endl;
	std::cout << "<Input> " << endl;
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
					std::cout << "[Info] 分配失败" << endl;
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
					std::cout << "[Info] 分配失败" << endl;
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

				std::cout << "[Info] 分配成功" << endl;
				delete orders;
				delete rs;
				return;
			}
			else
			{
				std::cout << "[Info] 没有合适大小的房间" << endl;
				delete orders;
				delete rs;
				return;
			}
		}
	}
	std::cout << "[Info] 订单不存在或已分配" << endl;
	delete orders;
}

void Clerk::showAllRoom()
{
	Room::showAll();
}