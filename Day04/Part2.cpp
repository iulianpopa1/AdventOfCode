#include <iostream>
#include <fstream>
#include <string> //stoi, atoi
#include <algorithm>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>

using namespace std;

bool check_double(string x)
{
	int rep = 1;

	for (int i = 0; i < 5; ++i) {
		if (x[i] == x[i + 1])
			rep++;
		else 
		{
			if (rep == 2)
				return true;
			else
				rep = 1;
		}
	}
	if (rep == 2)
		return true;

	return false;
}

bool check_incr(string x)
{
	if (x[0] > x[1] || x[1] > x[2] || x[2] > x[3] ||
		x[3] > x[4] || x[4] > x[5])
		return false;
	return true;
}

bool check(string x)
{
	return(check_double(x) && check_incr(x));
}
int main()
{
	ios::sync_with_stdio(false);

	int nr = 0;

	for (int i = 158126; i <= 624574; ++i) {
		if (check(to_string(i)))
			nr++;
	}

	cout << nr << endl;

}