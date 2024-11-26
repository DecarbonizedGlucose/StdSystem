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
	* 0 未处理
	* 1 已处理未使用
	* 2 已完成
	* 3 驳回
	* 4 用户撤销
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