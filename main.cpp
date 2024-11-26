#include <iostream>
#include <fstream>
#include "clerk.h"
#include "admin.h"
#include "customer.h"
#include "globalfile.h"
#include <string>
#define _CRT_SECURE_NO_WARNINGS 1
using namespace std;

Person* signIn(int type, string file)
{
	ifstream ifs(file, ios::in);
	if (!ifs.is_open())
	{
		cout << "[Info] �ļ���ȡʧ��" << endl;
		return nullptr;
	}
	string id, fid;
	string psw, fpsw;
	for (int i = 2; i >= 0; --i)
	{
		cout << "�������˺ţ�" << endl;
		cout << "<Input> ";
		getline(cin, id);
		cout << "���������룺" << endl;
		cout << "<Input> ";
		getline(cin, psw);
		while (ifs >> fid && ifs >> fpsw)
		{
			if (id == fid && psw == fpsw)
			{
				cout << "[Info] ��¼�ɹ�" << endl;
				Person* p;
				if (type == 1)
					p = new Admin(id, psw);
				else if (type == 2)
					p = new Clerk(id, psw);
				else
					p = new Cust(id, psw);
				system("pause");
				return p;
			}
		}
		cout << "[Info] �˺Ż���������㻹��" << i << "���������" << endl;
	}

	cout << "[Info] ��֤ʧ��" << endl;
	system("pause");
	return nullptr;
}

int main()
{
	bool running = true;
	while (running)
	{
		system("cls");
		cout << "== ����è���ѧ��ͤ�Ƶ����ϵͳ ==" << endl;
		cout << "================" << endl;
		cout << "    1. ��¼" << endl;
		cout << "    2. ע��" << endl;
		cout << "    0. �˳�" << endl;
		cout << "================" << endl;
		string choice;
		while (true)
		{
			cout << "<Input> ";
			getline(cin, choice);
			if (choice == "1")
			{
				// sign in
				system("cls");
				cout << "================" << endl;
				cout << "   1. ����Ա" << endl;
				cout << "   2. ǰְ̨Ա" << endl;
				cout << "   3. �˿��û�" << endl;
				cout << "================" << endl;
				string signtype;
				while (true)
				{
					cout << "<Input> ";
					getline(cin, signtype);
					Person* p;
					if (signtype == "1")
					{
						p = signIn(1, ADMIN_FILE);
						if (p)
						{
							p->operMenu();
						}
						break;
					}
					else if (signtype == "2")
					{
						p = signIn(2, CLERK_FILE);
						if (p)
						{
							p->operMenu();
						}
						break;
					}
					else if (signtype == "3")
					{
						p = signIn(3, CUSTOMER_FILE);
						if (p)
						{
							p->operMenu();
						}
						break;
					}
				}
				break;
			}
			else if (choice == "2")
			{
				// register
			}
			else if (choice == "0")
			{
				cout << "[Goodbye] ��ӭ�´�ʹ��" << endl;
				running = false;
				break;
			}
			else
			{
				cout << "[Info] ������������������" << endl;
			}
		}
	}
	system("pause");
	return 0;
}