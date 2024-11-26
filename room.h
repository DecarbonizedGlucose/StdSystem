#pragma once
using namespace std;

class Room
{
public:
	int volume; // 允许最多入住的人数
	int id; // 门牌号
	int state; // 分配状态
	// 0 空闲（未分配）
	// 1 已分配
};