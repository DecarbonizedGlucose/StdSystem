#pragma once
#include <string>
#include "person.h"
using namespace std;

class Cust : public Person
{
public:
	string usrId;

	string usrPsw;

	Cust();

	Cust(string id, string psw);

	virtual void operMenu();

	void submitOrder();

	void showMyOrder();

	void cancelOrder();
};