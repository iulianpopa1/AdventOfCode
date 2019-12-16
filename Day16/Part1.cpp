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
ifstream in("input.txt");

ll pat[4] = { 0, 1, 0, -1 };

string phase(string x)
{
	string new_x;
	ll pattern_it, local_ans;
	for (ll repeats = 1; repeats <= x.size(); ++repeats)
	{
		pattern_it = 1;
		local_ans = 0;

		for (ll j = 0; j < x.size(); ++j)
		{
			local_ans += (x[j] - '0') * pat[pattern_it / (repeats)];
			++pattern_it;
			if (pattern_it >= (repeats) * 4)
				pattern_it = 0;
		}
		new_x += to_string(abs(local_ans) % 10);
	}
	return new_x;
}

int main()
{
	ios::sync_with_stdio(false);

	string x;
	in >> x;
	for (int i = 1; i <= 100; ++i)
	{
		x = phase(x);
	}
	cout << "Part1: " << x.substr(0, 8) << endl;

	return 0;
}