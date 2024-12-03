#include "UI.h"
#include "BLL.h"
using namespace std;

void mainUI()
{
	Person* p = nullptr;
	bool running = true;
	while (running)
	{
		if (p != nullptr)
		{
			delete p;
			p = nullptr;
		}
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
					if (signtype == "1")
					{
						p = signIn(1, ADMIN_FILE);
						if (p)
						{
							system("cls");
							p->operMenu();
						}
						break;
					}
					else if (signtype == "2")
					{
						p = signIn(2, CLERK_FILE);
						if (p)
						{
							system("cls");
							p->operMenu();
						}
						break;
					}
					else if (signtype == "3")
					{
						p = signIn(3, CUSTOMER_FILE);
						if (p)
						{
							system("cls");
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
				// 牛魔 register竟然被占用了
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
}

void pui(int type)
{
	switch (type)
	{
	case 1:
		cout << "=============================" << endl;
		cout << " 1. 查看所有订单" << endl;
		cout << " 2. 查看所有服务员" << endl;
		cout << " 3. 查看所有房间" << endl;
		cout << " 4. 按注册时间顺序显示所有用户" << endl;
		cout << " 5. 按字典顺序显示所有用户" << endl;
		cout << " 6. 查找用户是否存在" << endl;
		cout << " 0. 退出账号" << endl;
		cout << "=============================" << endl;
		break;
	case 2:
		cout << "==================" << endl;
		cout << " 1. 查看所有订单" << endl;
		cout << " 2. 处理订单" << endl;
		cout << " 3. 查看某人订单" << endl;
		cout << " 4. 查看未处理订单" << endl;
		cout << " 5. 查看所有房间" << endl;
		cout << " 0. 退出账号" << endl;
		cout << "==================" << endl;
		break;
	case 3:
		cout << "==================" << endl;
		cout << " 1. 创建提交预约" << endl;
		cout << " 2. 查看我的预约" << endl;
		cout << " 3. 取消预约" << endl;
		cout << " 0. 退出账号" << endl;
		cout << "==================" << endl;
		break;
	}
}
