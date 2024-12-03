#pragma once
#include <string>
using namespace std;

class Person
{
public:
	string usrName;
	string usrPsw;
	string usrId;

	virtual void operMenu() = 0;
};