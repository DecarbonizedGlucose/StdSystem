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
	* 0 δ����
	* 1 �Ѵ���δʹ��
	* 2 �����
	* 3 ����
	* 4 �û�����
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