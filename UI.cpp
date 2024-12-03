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
			//cin >> choice;
			if (choice == "1")
			{
				// sign in
				system("cls");
				cout << "================" << endl;
				cout << "   1. ����Ա" << endl;
				cout << "   2. ǰְ̨Ա" << endl;
				cout << "   3. �˿��û�" << endl;
				cout << "   0. ����" << endl;
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
						cout << "[Info] ������������������" << endl;
					}
				}
				break;
			}
			else if (choice == "2")
			{
				// register
				// ţħ register��Ȼ��ռ����
				regi();
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
}

void pui(int type)
{
	switch (type)
	{
	case 1:
		cout << "=============================" << endl;
		cout << " 1. �鿴���ж���" << endl;
		cout << " 2. �鿴���з���Ա" << endl;
		cout << " 3. �鿴���з���" << endl;
		cout << " 4. ��ע��ʱ��˳����ʾ�����û�" << endl;
		cout << " 5. ���ֵ�˳����ʾ�����û�" << endl;
		cout << " 6. �����û��Ƿ����" << endl;
		cout << " 0. �˳��˺�" << endl;
		cout << "=============================" << endl;
		break;
	case 2:
		cout << "==================" << endl;
		cout << " 1. �鿴���ж���" << endl;
		cout << " 2. ������" << endl;
		cout << " 3. �鿴ĳ�˶���" << endl;
		cout << " 4. �鿴δ������" << endl;
		cout << " 5. �鿴���з���" << endl;
		cout << " 0. �˳��˺�" << endl;
		cout << "==================" << endl;
		break;
	case 3:
		cout << "==================" << endl;
		cout << " 1. �����ύԤԼ" << endl;
		cout << " 2. �鿴�ҵ�ԤԼ" << endl;
		cout << " 3. ȡ��ԤԼ" << endl;
		cout << " 0. �˳��˺�" << endl;
		cout << "==================" << endl;
		break;
	}
}
