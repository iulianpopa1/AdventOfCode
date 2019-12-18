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

void find_keys_doors_start(vector<string> v, map<char, pair<ll, ll>>& keys, pair<ll, ll>& start_point)
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

ll hsh(ll x, ll y)
{
	//Cantor pairing
	return ((x + y) * (x + y + 1)) / 2 + y;
}

ll lee(vector<string> v, pair<ll, ll> start, map<char, pair<ll, ll>> keys = map<char, pair<ll, ll>>())
{
	set<pair<ll, ll>> vis;
	queue<tuple<ll, ll, ll, ll>> q;
	
	ll bit_set = 0;

	if(keys.size())
		bit_set = pow(2, 26) - 1;

	for (auto it : keys)
	{
		bit_set -= pow(2, (it.first - 'a'));
	}

	vis.insert({ hsh(start.first, start.second), 0 });
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
			if (vis.find({ hsh(x_new, y_new), bs_ll }) != vis.end()) continue;
			if (ch_new >= 'A' && ch_new <= 'Z' && !bs[ch_new - 'A']) continue;

			if (ch_new >= 'a' && ch_new <= 'z' && !bs[ch_new - 'a'])
			{
				bs_new[ch_new - 'a'] = 1;
			}

			vis.insert({ hsh(x_new, y_new), bs_new.to_ulong() });
			q.push({ x_new, y_new, bs_new.to_ulong(), d + 1 });
		}
	}
}

void split_mat(vector<string> v, vector<string>& v1, vector<string>& v2, vector<string>& v3, vector<string>& v4)
{
	for (int i = 0; i <= v.size() / 2; ++i)
	{
		v1.push_back(v[i].substr(0, 41));
		v2.push_back(v[i].substr(40, 41));
	}

	for (int i = v.size() / 2; i < v.size(); ++i)
	{
		v3.push_back(v[i].substr(0, 41));
		v4.push_back(v[i].substr(40, 41));
	}
}


int main()
{
	ios::sync_with_stdio(false);

	string x;
	vector<string> v, v1, v2, v3, v4;
	while (!in.eof())
	{
		in >> x;
		v.push_back(x);
	}
	map<char, pair<ll, ll>> keys, keys1, keys2, keys3, keys4;
	pair<ll, ll> s_p, s_p1, s_p2, s_p3, s_p4; // start point

	find_keys_doors_start(v, keys, s_p);
	cout <<"Part1: " << lee(v, s_p) << endl;

	v[s_p.first - 1][s_p.second - 1] = '@';		v[s_p.first - 1][s_p.second] = '#';		v[s_p.first - 1][s_p.second + 1] = '@';
	v[s_p.first][s_p.second - 1] = '#';		v[s_p.first][s_p.second] = '#';		v[s_p.first][s_p.second + 1] = '#';
	v[s_p.first + 1][s_p.second - 1] = '@';		v[s_p.first + 1][s_p.second] = '#';		v[s_p.first + 1][s_p.second + 1] = '@';

	{
		split_mat(v, v1, v2, v3, v4);

		find_keys_doors_start(v1, keys1, s_p1);
		find_keys_doors_start(v2, keys2, s_p2);
		find_keys_doors_start(v3, keys3, s_p3);
		find_keys_doors_start(v4, keys4, s_p4);
	}

	ll p2_ans = 0;
	ll aux;
	{
		aux = lee(v1, s_p1, keys1);
		p2_ans += aux;
		cout << "Part2 - 1: " << aux << endl;
		aux = lee(v2, s_p2, keys2);
		p2_ans += aux;
		cout << "Part2 - 2: " << aux << endl;
		aux = lee(v3, s_p3, keys3);
		p2_ans += aux;
		cout << "Part2 - 3: " << aux << endl;
		aux = lee(v4, s_p4, keys4);
		p2_ans += aux;
		cout << "Part2 - 4: " << aux << endl;
	}

	cout << "Part2: " << p2_ans << endl;

	return 0;
}
