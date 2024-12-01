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
		ifs.close();
		return nullptr;
	}
	string id, fid;
	string psw, fpsw;
	for (int i = 2; i >= 0; --i)
	{
		cout << "请输入账号：" << endl;
		cout << "<Input> ";
		getline(cin, id);
		//cin >> id;
		cout << "请输入密码：" << endl;
		cout << "<Input> ";
		getline(cin, psw);
		//cin >> psw;
		// 这一步非常重要
		// 循环再读文件从头开始，不然毛都读不到
		ifs.clear();
		ifs.seekg(0, ios::beg);
		// 黑马程序员 你怎么没写啊 你马没了
		while (ifs >> fid && ifs >> fpsw)
		{   //读到最后状态是坏的
			//得clear一下 不然seek不了（上面）
			//cout << fid << " " << fpsw << endl;
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
		//cin.sync();
		cout << "[Info] 账号或密码错误，你还有" << i << "次输入机会" << endl;
	}

	cout << "[Info] 验证失败" << endl;
	ifs.close();
	system("pause");
	return nullptr;
}

bool stryes(string s)
{
	if (8 <= s.length() && s.length() <= 16)
	{
		for (char c : s)
		{
			if (!(('0' <= c && c <= '9') || ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')))
				return 0;
		}
		return 1;
	}
	return 0;
}

void regi()
{
	string name, psw;
	while (1)
	{
		cout << "请输入用户名（8~16位，仅包含英文字母和数字）：" << endl;
		cout << "<Input> ";
		getline(cin, name);
		if (stryes(name))
			break;
		else
			cout << "[Info] 用户名不合法" << endl;
	}
	while (1)
	{
		cout << "请输入密码（8~16位，仅包含英文字母和数字）：" << endl;
		cout << "<Input> ";
		getline(cin, psw);
		if (stryes(psw))
			break;
		else
			cout << "[Info] 密码不合法" << endl;
	}
	ofstream ofs(CUSTOMER_FILE, ios::out | ios::app);
	if (!ofs.is_open())
	{
		cout << "[Info] 注册失败" << endl;
		ofs.close();
		return;
	}
	ofs << name << " " << psw << endl;
	ofs.close();
	cout << "[Info] 注册成功" << endl;
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
			//cin >> choice;
			if (choice == "1")
			{
				// sign in
				system("cls");
				cout << "================" << endl;
				cout << "   1. 管理员" << endl;
				cout << "   2. 前台职员" << endl;
				cout << "   3. 顾客用户" << endl;
				cout << "   0. 返回" << endl;
				cout << "================" << endl;
				string signtype;
				while (true)
				{
					cout << "<Input> ";
					getline(cin, signtype);
					//cin >> signtype;
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
					else if (signtype == "0")
					{
						break;
					}
					else
					{
						cout << "[Info] 输入有误，请重新输入" << endl;
					}
				}
				break;
			}
			else if (choice == "2")
			{
				// register
				regi();
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