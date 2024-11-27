#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "customer.h"
#include "globalfile.h"
using namespace std;

class Order;

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

	//static Order* empty;

	friend ostream& operator<<(ostream& cout, Order& o);

	friend bool operator==(Order& o1, Order& o2);

	static void showAll();

	static void showOnes();
};