#include <iostream>
#include "room.h"
using namespace std;

ostream& operator<<(ostream& cout, Room r)
{
	cout << r.roomId << '\t' << r.roomSize << '\t' << r.roomState << endl;
	return cout;
}