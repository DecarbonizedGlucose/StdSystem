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
		cout << "[Info] 文件读取失败" << endl;
		return nullptr;
	}
	string id, fid;
	string psw, fpsw;
	for (int i = 2; i >= 0; --i)
	{
		cout << "请输入账号：" << endl;
		cout << "<Input> ";
		getline(cin, id);
		cout << "请输入密码：" << endl;
		cout << "<Input> ";
		getline(cin, psw);
		while (ifs >> fid && ifs >> fpsw)
		{
			if (id == fid && psw == fpsw)
			{
				cout << "[Info] 登录成功" << endl;
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
		cout << "[Info] 账号或密码错误，你还有" << i << "次输入机会" << endl;
	}

	cout << "[Info] 验证失败" << endl;
	system("pause");
	return nullptr;
}

int main()
{
	bool running = true;
	while (running)
	{
		system("cls");
		cout << "== 西安猫鼠大学长亭酒店操作系统 ==" << endl;
		cout << "================" << endl;
		cout << "    1. 登录" << endl;
		cout << "    2. 注册" << endl;
		cout << "    0. 退出" << endl;
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
				cout << "   1. 管理员" << endl;
				cout << "   2. 前台职员" << endl;
				cout << "   3. 顾客用户" << endl;
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
				cout << "[Goodbye] 欢迎下次使用" << endl;
				running = false;
				break;
			}
			else
			{
				cout << "[Info] 输入有误，请重新输入" << endl;
			}
		}
	}
	system("pause");
	return 0;
}