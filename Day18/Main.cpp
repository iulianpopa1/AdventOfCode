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
#include <bitset>
#include <math.h>

using namespace std;
using ll = long long;

ifstream in("input.txt");

ll dirX[4] = { -1, 0, 1, 0 };
ll dirY[4] = { 0, -1, 0, 1 };

void Find_keys_start(vector<string> v, map<char, pair<ll, ll>>& keys, pair<ll, ll>& start_point)
{
	for (char c = 'A'; c <= 'Z'; ++c)
	{
		for (ll i = 0; i < v.size(); ++i)
		{
			auto find_it = find(v[i].cbegin(), v[i].cend(), c + 32);
			if (find_it != v[i].cend())
				keys[c + 32] = { i, find_it - v[i].begin() };


			find_it = find(v[i].cbegin(), v[i].cend(), '@');
			if (find_it != v[i].cend())
			{
				start_point.first = i;
				start_point.second = find_it - v[i].begin();
			}
		}
	}
}

ll BFS(vector<string> v, pair<ll, ll> start, map<char, pair<ll, ll>> keys = map<char, pair<ll, ll>>())
{
	set<tuple<ll, ll, ll>> vis;
	queue<tuple<ll, ll, ll, ll>> q;

	ll bit_set = 0;

	if (keys.size())
		bit_set = pow(2, 26) - 1;

	for (auto it : keys)
	{
		bit_set -= pow(2, (it.first - 'a'));
	}

	vis.insert({ start.first, start.second, 0 });
	q.push({ start.first, start.second, bit_set , 0 });


	while (!q.empty())
	{
		ll x = get<0>(q.front());
		ll y = get<1>(q.front());
		ll bs_ll = get<2>(q.front());
		ll d = get<3>(q.front());
		bitset<26> bs(bs_ll);
		q.pop();

		if (bs == bitset<26>(pow(2, 26) - 1)) // 2 ^ 26 - 1
		{
			return d;
		}

		for (ll i = 0; i < 4; ++i)
		{
			ll x_new = x + dirX[i];
			ll y_new = y + dirY[i];
			char ch_new = v[x_new][y_new];
			bitset<26> bs_new = bs;

			if (ch_new == '#') continue;
			if (vis.find({ x_new, y_new, bs_ll }) != vis.end()) continue;
			if (ch_new >= 'A' && ch_new <= 'Z' && !bs[ch_new - 'A']) continue;

			if (ch_new >= 'a' && ch_new <= 'z' && !bs[ch_new - 'a'])
			{
				bs_new[ch_new - 'a'] = 1;
			}

			vis.insert({ x_new, y_new, bs_new.to_ulong() });
			q.push({ x_new, y_new, bs_new.to_ulong(), d + 1 });
		}
	}
}

void Split_map(vector<vector<string>> & v)
{
	for (int i = 0; i <= v[0].size() / 2; ++i)
	{
		v[1].push_back(v[0][i].substr(0, 41)); // quadrant 1 ~ Left-Up
		v[2].push_back(v[0][i].substr(40, 41)); // quadrant 2 ~ Right-Up
	}

	for (int i = v[0].size() / 2; i < v[0].size(); ++i)
	{
		v[3].push_back(v[0][i].substr(0, 41)); // quadrant 3 ~ Left-Down
		v[4].push_back(v[0][i].substr(40, 41)); // quadrant 4 ~ Right-Down
	}
}


int main()
{
	ios::sync_with_stdio(false);

	vector<vector<string>> v(5);

	while (!in.eof())
	{
		string x;
		in >> x;
		v[0].push_back(x);
	}
	vector< map<char, pair<ll, ll>>> keys(5);
	vector<pair<ll, ll>> start_point(5); // start point

	Find_keys_start(v[0], keys[0], start_point[0]);
	cout << "Part1: " << BFS(v[0], start_point[0]) << endl;

	v[0][start_point[0].first - 1][start_point[0].second - 1] = '@';		v[0][start_point[0].first - 1][start_point[0].second] = '#';		v[0][start_point[0].first - 1][start_point[0].second + 1] = '@';
	v[0][start_point[0].first]	  [start_point[0].second - 1] = '#';		v[0][start_point[0].first]	  [start_point[0].second] = '#';		v[0][start_point[0].first]	  [start_point[0].second + 1] = '#';
	v[0][start_point[0].first + 1][start_point[0].second - 1] = '@';		v[0][start_point[0].first + 1][start_point[0].second] = '#';		v[0][start_point[0].first + 1][start_point[0].second + 1] = '@';

	Split_map(v);

	ll part2_ans = 0;

	for (int i = 1; i <= 4; ++i)
	{	
		Find_keys_start(v[i], keys[i], start_point[i]);
		ll aux = BFS(v[i], start_point[i], keys[i]);
		part2_ans += aux;
		cout << "Part2 - quadrant " << i << ": " << aux << endl;
	}
	cout << "Part2: " << part2_ans << endl;

	return 0;
}
