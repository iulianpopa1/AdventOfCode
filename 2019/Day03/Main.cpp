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

ifstream in("P_input.txt");

map<pair<ll, ll>, ll> mapp;
ll N = 20000;

ll mht_dist(ll x, ll y)
{
	return (abs(N/2 - x) + abs(N/2 - y));
}

pair<ll, ll> move(char c)
{
	switch (c)
	{
	case 'R':
		return make_pair(0, 1);
		break;	
	case 'L':
		return make_pair(0, -1);
		break;
	case 'U':
		return make_pair(-1, 0);
		break;
	case 'D':
		return make_pair(1, 0);
		break;
	}
}

int main()
{
	ios::sync_with_stdio(false);

	char dir;
	ll dist;

	ll min_dist_P1 = 99999999;
	ll min_dist_P2 = 99999999;
	ll x, y, steps;

	x = N/2; y = N/2;
	steps = 1;

	while (!in.eof())
	{
		in >> dir >> dist;

		if (dir == 'X') // I put a (X, 0) between the each wire input
		{
			break;
		}

		for (ll i = 1; i <= dist; ++i)
		{
			auto dir_move = move(dir);
			x += dir_move.first;
			y += dir_move.second;

			mapp[make_pair(x, y)] = steps;
			steps++;
		}
	}

	x = N / 2; y = N / 2;
	steps = 0;

	while (!in.eof())
	{
		in >> dir >> dist;

		if (dir == 'X')
		{
			break;
		}

		for (int i = 1; i <= dist; ++i)
		{
			auto dir_move = move(dir);
			x += dir_move.first;
			y += dir_move.second;

			if (mapp.find({ x, y }) != mapp.end())
				min_dist_P1 = min(mht_dist(x, y), min_dist_P1);

			if (mapp.find(make_pair(x, y)) != mapp.end())
				min_dist_P2 = min(steps + mapp[make_pair(x, y)], min_dist_P2);
			steps++;
		}
	}
	cout << "P1 : " << min_dist_P1 << endl;
	cout << "P2 : " << min_dist_P2 + 1;
}
