#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "BLL.h"
#include "UI.h"
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

//////


void Admin::operMenu()
{
	while (true)
	{
		pui(1);
		string choice;
		while (true)
		{
			cout << "<Input> ";
			getline(cin, choice);
			if (choice == "1")
			{
				// show all order
				showAllOrder();
				break;
			}
			else if (choice == "2")
			{
				// show all clerks
				showAllClerk();
				break;
			}
			else if (choice == "3")
			{
				showAllRoom();
				break;
			}
			else if (choice == "4")
			{
				showAllCustTime();
				break;
			}
			else if (choice == "5")
			{
				showAllCustASCII();
				break;
			}
			else if (choice == "6")
			{
				custDoExist();
				break;
			}
			else if (choice == "0")
			{
				return;
			}
			else
			{
				cout << "[Info] 输入有误，请重新输入" << endl;
				break;
			}
		}
		system("pause");
		system("cls");
	}
}

void Clerk::operMenu()
{
	while (1)
	{
		pui(2);
		string choice;
		while (true)
		{
			cout << "<Input> ";
			getline(cin, choice);
			if (choice == "1")
			{
				// show all order
				showAllOrder();
				break;
			}
			else if (choice == "2")
			{
				// manage orders
				manageOrder();
				break;
			}
			else if (choice == "3")
			{
				showOnesOrder();
				break;
			}
			else if (choice == "4")
			{
				showUnOrder();
				break;
			}
			else if (choice == "5")
			{
				showAllRoom();
				break;
			}
			else if (choice == "0")
			{
				return;
			}
			else
			{
				cout << "[Info] 输入有误，请重新输入" << endl;
				break;
			}
		}
		system("pause");
		system("cls");
	}
}

void Cust::operMenu()
{
	while (1)
	{
		pui(3);
		string choice;
		while (true)
		{
			cout << "<Input> ";
			getline(cin, choice);
			//cin >> choice;
			if (choice == "1")
			{
				// create and submit an order
				submitOrder();
				break;
			}
			else if (choice == "2")
			{
				// show my orders
				showMyOrder();
				break;
			}
			else if (choice == "3")
			{
				// cancel my order
				cancelOrder();
				break;
			}
			else if (choice == "0")
			{
				return;
			}
			else
			{
				cout << "[Info] 输入有误，请重新输入" << endl;
				break;
			}
		}
		system("pause");
		system("cls");
	}
}

//////

Admin::Admin() {}

Admin::Admin(string id, string psw)
{
	usrId = id;
	usrPsw = psw;
}

void Admin::showAllOrder()
{
	Order::showAll();
}

void Admin::showAllClerk()
{
	ifstream ifs(CLERK_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "[Info] 文件读取失败" << endl;
		ifs.close();
		return;
	}
	cout << "用户名    |    密码" << endl;
	string name, psw;
	while (ifs >> name)
	{
		ifs >> psw;
		cout << name << "    |    " << psw << endl;
	}
	ifs.close();
}

void Admin::showAllRoom()
{
	Room::showAll();
}

void Admin::custDoExist()
{
	string name;
	cout << "请输入用户名：" << endl;
	cout << "<Input> ";
	getline(cin, name);
	if (Cust::find(name))
	{
		cout << "[Info] 该用户存在" << endl;
	}
	else
	{
		cout << "[Info] 该用户不存在" << endl;
	}
}

void Admin::showAllCustTime()
{
	Cust::showAllTime();
}

void Admin::showAllCustASCII()
{
	Cust::showAllASCII();
}

Clerk::Clerk() {}

Clerk::Clerk(string id, string psw) : usrId(id), usrPsw(psw) {}

void Clerk::showAllOrder()
{
	Order::showAll();
}

void Clerk::showOnesOrder()
{
	string name;
	cout << "请输入用户名：" << endl;
	cout << "<Input> ";
	getline(cin, name);
	Order::showOnes(name);
}

void Clerk::manageOrder()
{
	List<Order>* orders = Order::showUn();
	if (orders == nullptr) return;
	cout << "你要给哪个订单分配？" << endl;
	cout << "<Input> " << endl;
	string orderId;
	getline(cin, orderId);
	if (Node<Order>* o = orders->find(Order(orderId, "", 0, 0, "")))
	{
		if (o->value.state == 0)
		{
			List<Room>* rs = Room::showAvailable();
			if (rs == nullptr) return;
			Node<Room>* f = rs->head->next;
			while (f)
			{
				if (f->value.roomSize >= o->value.req)
				{
					break;
				}
			}
			if (f)
			{
				f->value.roomState = 1;
				ofstream ofs1(ROOM_FILE, ios::out | ios::trunc);
				if (!ofs1.is_open())
				{
					cout << "[Info] 分配失败" << endl;
					ofs1.close();
					delete orders;
					delete rs;
					return;
				}
				f = rs->head->next;
				o->value.state = 1;
				o->value.roomId = f->value.roomId;
				while (f)
				{
					ofs1 << f->value.roomId << " " << f->value.roomSize << " " << f->value.roomState << endl;
				}
				ofstream ofs2(ORDER_FILE, ios::out | ios::trunc);
				if (!ofs2.is_open())
				{
					cout << "[Info] 分配失败" << endl;
					ofs2.close();
					delete orders;
					delete rs;
					return;
				}

				Node<Order>* n = orders->head->next;
				while (n)
				{
					ofs2 << n->value.orderId << ' ' << n->value.usrId << ' ';
					ofs2 << n->value.req << ' ' << n->value.state << ' ';
					ofs2 << n->value.roomId << endl;
					n = n->next;
				}
				ofs2.close();

				cout << "[Info] 分配成功" << endl;
				delete orders;
				delete rs;
				return;
			}
			else
			{
				cout << "[Info] 没有合适大小的房间" << endl;
				delete orders;
				delete rs;
				return;
			}
		}
	}
	cout << "[Info] 订单不存在或已分配" << endl;
	delete orders;
}

void Clerk::showAllRoom()
{
	Room::showAll();
}

void Clerk::showUnOrder()
{
	Order::showUn();
}

Cust::Cust() {}

Cust::Cust(string id, string psw) : usrId(id), usrPsw(psw) {}

void Cust::submitOrder()
{
	time_t now = time(nullptr);
	tm* ltm = localtime(&now);
	stringstream sst;
	int temp;
	sst << "R";
	sst << 1900 + ltm->tm_year;
	temp = ltm->tm_mon + 1;
	if (temp < 10) sst << '0' << temp;
	else sst << temp;
	temp = ltm->tm_mday;
	if (temp < 10) sst << '0' << temp;
	else sst << temp;
	temp = ltm->tm_hour;
	if (temp < 10) sst << '0' << temp;
	else sst << temp;
	temp = ltm->tm_min;
	if (temp < 10) sst << '0' << temp;
	else sst << temp;
	temp = ltm->tm_sec;
	if (temp < 10) sst << '0' << temp;
	else sst << temp;
	string code;
	sst >> code;
	ofstream ofs(ORDER_FILE, ios::app);
	string num;
	//getline(cin, num); // 这他妈哪来的bug
	//cin >> num;
	//cin.clear();
	//cin.sync(); // 这玩意在vs里没用
	//cin.ignore();
	while (true)
	{
		cout << "请输入人数（输入0返回）：" << endl;
		cout << "<Input> ";
		getline(cin, num);
		if (num == "1" || num == "2" || num == "3" || num == "4") break;
		else if (num == "0")
		{
			cout << "[Info] 已取消" << endl;
			ofs.close();
			return;
		}
		else cout << "[Info] 输入有误，请重新输入" << endl;
	}
	ofs << code << " " << usrId << " " << num << " 0 none" << endl;
	ofs.close();
	cout << "[Info] 提交成功" << endl;
}

void Cust::showMyOrder()
{
	fstream ifs(ORDER_FILE, ios::in);
	string code, name, room;
	int req, state;
	List<Order> orders;
	while (ifs >> code)
	{
		ifs >> name >> req >> state >> room;
		if (name == this->usrId)
		{
			orders.addBack(Order(code, name, req, state, room));
		}
	}
	if (orders.length == 0)
	{
		cout << endl << "[Info] 未找到相关订单" << endl << endl;
		ifs.close();
		return;
	}
	Node<Order>* f = orders.head->next;
	cout << "编号          |  用户         |   需求    |  状态    | 房间" << endl;
	while (f)
	{
		cout << f->value;
		f = f->next;
	}
	cout << "[Info] 共找到" << orders.length << "条订单记录" << endl;
	ifs.close();
}

void Cust::cancelOrder()
{
	fstream ifs(ORDER_FILE, ios::in);
	string code, name, room;
	int req, state, cnt = 0;
	List<Order> orders;
	while (ifs >> code)
	{
		ifs >> name >> req >> state >> room;
		if (name == this->usrId) ++cnt;
		orders.addBack(Order(code, name, req, state, room));
	}
	if (cnt == 0)
	{
		cout << endl << "[Info] 未找到相关订单" << endl << endl;
		ifs.close();
		return;
	}
	Node<Order>* f = orders.head->next;
	cout << "编号          |  用户         |   需求    |  状态    | 房间" << endl;
	while (f)
	{
		if (f->value.usrId == this->usrId)
			cout << f->value;
		f = f->next;
	}
	cout << "[Info] 共找到" << cnt << "条订单记录" << endl;
	ifs.close();
	cout << endl << "请输入要取消的订单（输入0返回）：" << endl;
	string iptId;
	Node<Order>* n;
	while (true)
	{
		cout << "<Input> ";
		getline(cin, iptId);
		n = orders.find(Order(iptId, "", 0, 0, ""));
		if (n) break;
		else if (iptId == "0")
		{
			cout << "[Info] 已放弃修改" << endl;
			return;
		}
		else cout << "[Info] 输入有误，请重新输入" << endl;
	}
	n->value.state = 4;
	n->value.roomId = "none";
	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	if (!ofs.is_open())
	{
		cout << "[Info] 修改失败" << endl;
		ofs.close();
		return;
	}
	n = orders.head->next;
	while (n)
	{
		ofs << n->value.orderId << ' ' << n->value.usrId << ' ';
		ofs << n->value.req << ' ' << n->value.state << ' ';
		ofs << n->value.roomId << endl;
		n = n->next;
	}
	ofs.close();
	cout << "[Info] 撤销成功" << endl;
}

bool Cust::find(string usrId)
{
	ifstream ifs(CUSTOMER_FILE, ios::in);
	string name, psw;
	while (ifs >> name)
	{
		ifs >> psw;
		if (name == usrId)
		{
			ifs.close();
			return true;
		}
	}
	ifs.close();
	return false;
}

void Cust::showAllTime()
{
	ifstream ifs(CUSTOMER_FILE, ios::in);
	string name, psw;
	while (ifs >> name)
	{
		ifs >> psw;
		cout << name << endl;
	}
	ifs.close();
}

void Cust::showAllASCII()
{
	List<string> names;
	ifstream ifs(CUSTOMER_FILE, ios::in);
	string name, psw;
	while (ifs >> name)
	{
		ifs >> psw;
		names.addBack(name);
	}
	ifs.close();
	names.bubbleSort();
	Node<string>* f = names.head->next;
	while (f)
	{
		cout << f->value << endl;
		f = f->next;
	}
}

ostream& operator<<(ostream& cout, Order& o)
{
	cout << o.orderId << '\t' << o.usrId << '\t' << o.req << '\t';
	switch (o.state)
	{
	case 0:
		cout << "未分配"; break;
	case 1:
		cout << "未完成"; break;
	case 2:
		cout << "已完成"; break;
	case 3:
		cout << "驳回"; break;
	case 4:
		cout << "订单取消"; break;
	default:
		cout << "你他妈是不是打错字了";
	}
	cout << '\t' << o.roomId;
	cout << endl;
	return cout;
}

bool operator==(Order& o1, Order& o2)
{
	return (o1.usrId == o2.usrId) || (o1.orderId == o2.orderId);
}

void Order::showAll()
{
	ifstream ifs(ORDER_FILE, ios::in);
	int cnt = 0;
	if (!ifs.is_open())
	{
		cout << "[Info] 文件读取失败" << endl;
		ifs.close();
		return;
	}
	cout << "编号          |  用户         |   需求    |  状态    | 房间" << endl;
	string odid, urid, room;
	int req, state;
	while (ifs >> odid)
	{
		ifs >> urid >> req >> state >> room;
		cnt++;
		cout << odid << '\t' << urid << '\t' << req << "\t\t";
		switch (state)
		{
		case 0:
			cout << "未分配"; break;
		case 1:
			cout << "未完成"; break;
		case 2:
			cout << "已离店"; break;
		case 3:
			cout << "驳回"; break;
		case 4:
			cout << "订单取消"; break;
		default:
			cout << "你他妈是不是打错字了";
		}
		cout << '\t' << room;
		cout << endl;
	}
	cout << "[Info] 共找到" << cnt << "条订单记录" << endl;
	ifs.close();
}

void Order::showOnes(string usrId)
{
	fstream ifs(ORDER_FILE, ios::in);
	string code, name, room;
	int num, state, cnt = 0;
	List<Order> orders;
	while (ifs >> code)
	{
		ifs >> name >> num >> state >> room;
		if (name == usrId)
		{
			++cnt;
			orders.addBack(Order(code, name, num, state, room));
		}
	}
	if (!cnt)
	{
		cout << endl << "[Info] 未找到相关订单" << endl << endl;
		ifs.close();
		return;
	}
	Node<Order>* f = orders.head->next;
	cout << "编号          |  用户         |   需求    |  状态    | 房间" << endl;
	while (f)
	{
		if (f->value.usrId == usrId)
			cout << f->value;
		f = f->next;
	}
	cout << "[Info] 共找到" << cnt << "条订单记录" << endl;
	ifs.close();
}

List<Order>* Order::showUn()
{
	fstream ifs(ORDER_FILE, ios::in);
	string code, name, room;
	int num, state, cnt = 0;
	List<Order>* orders = new List<Order>;
	while (ifs >> code)
	{
		ifs >> name >> num >> state >> room;
		orders->addBack(Order(code, name, num, state, room));
		if (state == 0) ++cnt;
	}
	if (!cnt)
	{
		cout << endl << "[Info] 未找到相关订单" << endl << endl;
		ifs.close();
		return nullptr;
	}
	Node<Order>* f = orders->head->next;
	cout << "编号          |  用户         |   需求    |  状态    | 房间" << endl;
	while (f)
	{
		if (f->value.state == 0)
			cout << f->value;
		f = f->next;
	}
	cout << "[Info] 共找到" << orders->length << "条订单记录" << endl;
	ifs.close();
	return orders;
}

ostream& operator<<(ostream& cout, Room r)
{
	cout << r.roomId << '\t' << r.roomSize << '\t' << r.roomState << endl;
	return cout;
}