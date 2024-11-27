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

	static void showAll()
	{
		ifstream ifs(ORDER_FILE, ios::in);
		if (!ifs.is_open())
		{
			cout << "[Info] �ļ���ȡʧ��" << endl;
			ifs.close();
			return;
		}
		cout << "���\t\t�û�\t����\t״̬\t����" << endl;
		string odid, urid, room;
		int req, state;
		while (ifs >> odid)
		{
			ifs >> urid >> req >> state >> room;
			cout << odid << '\t' << urid << '\t' << req << '\t';
			switch (state)
			{
			case 0:
				cout << "δ����"; break;
			case 1:
				cout << "δ���"; break;
			case 2:
				cout << "�����"; break;
			case 3:
				cout << "����"; break;
			case 4:
				cout << "����ȡ��"; break;
			default:
				cout << "�������ǲ��Ǵ������";
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