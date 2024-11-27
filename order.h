#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "customer.h"
#include "globalfile.h"
using namespace std;

class Order
{
public:
	string orderId; // 1st
	string usrId; // 2nd
	int req; // 3rd
	int state; // 4th
	string roomId; // 5th
	/*
	* 0 未处理
	* 1 已处理未使用
	* 2 已完成
	* 3 驳回
	* 4 用户撤销
	*/

	Order() {} 

	Order(string odid, string urid, int req, int state, string room)
	{
		orderId = odid;
		usrId = urid;
		this->req = req;
		this->state = state;
		roomId = room;
	}

	static void showAll()
	{
		ifstream ifs(ORDER_FILE, ios::in);
		if (!ifs.is_open())
		{
			cout << "[Info] 文件读取失败" << endl;
			ifs.close();
			return;
		}
		cout << "编号\t\t用户\t需求\t状态\t房间" << endl;
		string odid, urid, room;
		int req, state;
		while (ifs >> odid)
		{
			ifs >> urid >> req >> state >> room;
			cout << odid << '\t' << urid << '\t' << req << '\t';
			switch (state)
			{
			case 0:
				cout << "未分配"; break;
			case 1:
				cout << "未完成"; break;
			case 2:
				cout << "已离店"; break;
			case 3:
				cout << "驳回"; break;
			case 4:
				cout << "订单取消"; break;
			default:
				cout << "你他妈是不是打错字了";
			}
			if (room != "none") cout << '\t' << room;
			cout << endl;
		}
		ifs.close();
	}

	static void showOnes()
	{
	}

	//friend ostream& operator<<(ostream& cout, Order& o);
};