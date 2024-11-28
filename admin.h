#pragma once
#include "person.h"
#include <string>
using namespace std;

class Admin : public Person
{
public:
	Admin();

	Admin(string id, string psw);

	virtual void operMenu();

	void showAllOrder();

	void showAllClerk();

	void showAllRoom();

	void custDoExist();

	void showAllCustTime();

	void showAllCustASCII();
};