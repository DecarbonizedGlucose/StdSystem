#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "globalfile.h"
#include "list.h"
using namespace std;

class Room;

ostream& operator<<(ostream& cout, Room r);

class Room
{
public:
	string roomId; // ���ƺ�
	int roomSize; // �������
	int roomState; // ����״̬
	// 0 ���У�δ���䣩
	// 1 �ѷ���

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
			cout << "[Info] �ļ���ȡʧ��" << endl;
			ifs.close();
			return;
		}
		cout << "���ƺ�\t����\t״̬" << endl;
		string id;
		int size, state;
		while (ifs >> id)
		{
			ifs >> size >> state;
			cout << id << '\t' << size << '\t';
			if (state) cout << "�ѷ���";
			else cout << "δռ��";
			cout << endl;
		}
		ifs.close();
	}

	static List<Room>* showAvailable()
	{
		ifstream ifs(ROOM_FILE, ios::in);
		if (!ifs.is_open())
		{
			cout << "[Info] �ļ���ȡʧ��" << endl;
			ifs.close();
			return nullptr;
		}
		List<Room>* rooms = new List<Room>;
		string id;
		int size, state, cnt = 0;
		while (ifs >> id)
		{
			ifs >> size >> state;
			rooms->addBack(Room(id, size, state));
			if (state == 0) ++cnt;
		}
		ifs.close();
		if (cnt == 0) cout << endl << "[Info] û�п��еķ���" << endl << endl;
		else
		{
			cout << "���\t\t�û�\t����\t״̬\t����" << endl;
			Node<Room>* f = rooms->head->next;
			while (f)
			{
				cout << f->value;
				f = f->next;
			}
		}
	}
}; 