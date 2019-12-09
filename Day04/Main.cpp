/**/
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
using ll = long long;

bool check_double_P2(string x)
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

bool check_double_P1(string x)
{
	for (ll i = 0; i < 5; ++i)
		if (x[i] == x[i + 1])
			return true;
	return false;
}

bool check_increasing(string x)
{
	for (ll i = 0; i < 5; ++i)
		if (x[i] > x[i + 1])
			return false;
	return true;
}

pair<long, long> check(string x)
{
	if (!check_increasing(x))
		return make_pair(0, 0);
	return make_pair(check_double_P1(x), check_double_P2(x));
}

int main()
{
	ios::sync_with_stdio(false);

	ll count_P1 = 0;
	ll count_P2 = 0;

	ll LEFT_LIMIT = 158126; //INPUT
	ll RIGHT_LIMIT = 624574; //INPUT

	for (ll i = LEFT_LIMIT; i <= RIGHT_LIMIT; ++i) {
		auto result = check(to_string(i));
		count_P1 += result.first;
		count_P2 += result.second;
	}
	
	cout << "Part1 : " << count_P1 << endl;
	cout << "Part2 : " << count_P2 << endl;
}
