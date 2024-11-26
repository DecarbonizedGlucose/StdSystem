#pragma once
#include "person.h"
#include <string>
using namespace std;

class Clerk : public Person
{
public:
	string usrId;

	string usrPsw;

	Clerk();

	Clerk(string id, string psw);

	virtual void operMenu();

	void showAllOrder();

	void manageOrder();
};