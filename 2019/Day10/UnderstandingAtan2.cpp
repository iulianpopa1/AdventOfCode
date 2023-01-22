#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;
// (00) (10) (20)       p8 p1 p2
// (01) (11) (21)       p7 p0 p3
// (02) (12) (22)       p6 p5 p4

float calc_angle(pair<int, int> p1, pair<int, int> p2)
{
	return (float)atan2(p1.first - p2.first, p1.second - p2.second);
}

int main()
{
	auto p0 = make_pair(1, 1);
	auto p1 = make_pair(1, 0);
	auto p2 = make_pair(2, 0);
	auto p3 = make_pair(2, 1);
	auto p4 = make_pair(2, 2);
	auto p5 = make_pair(1, 2);
	auto p6 = make_pair(0, 2);
	auto p7 = make_pair(0, 1);
	auto p8 = make_pair(0, 0);

	cout << "atan(p0, p1) : "<<calc_angle(p0, p1) << endl;
	cout << "atan(p0, p2) : "<<calc_angle(p0, p2) << endl;
	cout << "atan(p0, p3) : "<<calc_angle(p0, p3) << endl;
	cout << "atan(p0, p4) : "<<calc_angle(p0, p4) << endl;
	cout << "atan(p0, p5) : "<<calc_angle(p0, p5) << endl;
	cout << "atan(p0, p6) : "<<calc_angle(p0, p6) << endl;
	cout << "atan(p0, p7) : "<<calc_angle(p0, p7) << endl;
	cout << "atan(p0, p8) : "<<calc_angle(p0, p8) << endl;
}
