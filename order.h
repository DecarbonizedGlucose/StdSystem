#pragma once
//#include <string>
#include "customer.h"
using namespace std;

class Order
{
public:
	//Cust* person;
	string usrId; // 2nd
	string orderId; // 1st
	int req; // 3rd
	int state; // 4th
	/*
	* 0 δ����
	* 1 �Ѵ���δʹ��
	* 2 �����
	* 3 ����
	* 4 �û�����
	*/

	Order() {} 

	Order(string odid, string urid, int req, int state)
	{
		orderId = odid;
		usrId = urid;
		this->req = req;
		this->state = state;
	}

	

};