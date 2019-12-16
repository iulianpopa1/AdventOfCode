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
			pattern_it = (pattern_it + 1) % (repeats * 4);
		}
		new_x += '0' + abs(local_ans) % 10;
	}
	return new_x;
}

string phase2(string x)
{
	vector<int> sums{ 0 };

	for (auto it : x)
	{
		sums.push_back(it - '0' + sums.back());
	}

	for (int j = x.size() / 2; j < x.size(); ++j)
	{
		x[j] = (sums[x.size()] - sums[j]) % 10 + '0';
	}

	return x;
}

int main()
{
	ios::sync_with_stdio(false);

	string x, input_x, BIG_X;
	in >> input_x;

	x = input_x;
	for (int i = 1; i <= 100; ++i)
	{
		x = phase(x);
	}
	cout << "Part1: " << x.substr(0, 8) << endl;
	
	for (int i = 1; i <= 10000; ++i)
	{
		BIG_X += input_x;
	}

	for (int i = 1; i <= 100; ++i)
	{
		BIG_X = phase2(BIG_X);
	}
	
	ll offset = stoll(input_x.substr(0, 7));
	cout << "Part2: " << BIG_X.substr(offset, 8) << endl;
	return 0;
}