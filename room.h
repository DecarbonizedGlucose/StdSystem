#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "globalfile.h"
#include "list.h"
using namespace std;

class Room
{
public:
	string roomId; // 门牌号
	int roomSize; // 最大容量
	int roomState; // 分配状态
	// 0 空闲（未分配）
	// 1 已分配

	Room() {}
	
	Room(string id, int size, int state)
	{
		roomId = id;
		roomSize = size;
		roomState = state;
	}

	static void showAll()
	{
		ifstream ifs(ROOM_FILE, ios::in);
		if (!ifs.is_open())
		{
			cout << "[Info] 文件读取失败" << endl;
			ifs.close();
			return;
		}
		cout << "门牌号\t容量\t状态" << endl;
		string id;
		int size, state;
		while (ifs >> id)
		{
			ifs >> size >> state;
			cout << id << '\t' << size << '\t';
			if (state) cout << "已分配";
			else cout << "未占用";
			cout << endl;
		}
		ifs.close();
	}

	static void showAvailable()
	{
		ifstream ifs(ROOM_FILE, ios::in);
		if (!ifs.is_open())
		{
			cout << "[Info] 文件读取失败" << endl;
			ifs.close();
			return;
		}
		List<Room> rooms;
		string id;
		int size, state;
		while (ifs >> id)
		{
			ifs >> size >> state;
			if (!state) rooms.addBack(Room(id, size, state));
		}
		ifs.close();
		if (rooms.length == 0) cout << endl << "[Info] 没有空闲的房间" << endl << endl;
		else
		{
			cout << "编号\t\t用户\t需求\t状态\t房间" << endl;
			Node<Room>* f = rooms.head->next;
			while (f)
			{
				cout << f -> value;
				f = f->next;
			}
		}
	}
};

ostream& operator<<(ostream& cout, Room& r)
{
	cout << r.roomId << '\t' << r.roomSize << '\t' << r.roomState << endl;
	return cout;
}