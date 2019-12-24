
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

ll dirX[4] = { -1, 0, 1, 0 };
ll dirY[4] = { 0, -1, 0, 1 };

vector<string> default_mat;

ifstream in("input.txt");

void update_p1(vector<string>& v)
{
	auto v_copy = v;

	for (ll x = 0; x < 5; ++x)
	{
		for (ll y = 0; y < 5; ++y)
		{
			ll cnt = 0;

			for (ll i = 0; i < 4; ++i)
			{
				if (x + dirX[i] < 0 || x + dirX[i] > 4 || y + dirY[i] < 0 || y + dirY[i] > 4)
					continue;

				if (v_copy[x + dirX[i]][y + dirY[i]] == '#')
					++cnt;
			}
			if (v_copy[x][y] == '#' && cnt != 1)
			{
					v[x][y] = '.';
			}
			if (v_copy[x][y] == '.' && (cnt == 1 || cnt == 2))
			{
				v[x][y] = '#';
			}
		}
	}
}

ll calc_cost(vector<string> v)
{
	ll cost = 0;
	for (ll x = 0; x < 5; ++x)
	{
		for (ll y = 0; y < 5; ++y)
		{
			if (v[x][y] == '#')
				cost += pow(2, x * 5 + y);
		}
	}
	return cost;
}

ll part1(vector<string> v)
{
	map<ll, ll> vis;
	ll step = 1;
	vis[calc_cost(v)] = 0;

	while (1)
	{
		//print_mat(v);
		update_p1(v);
		auto aux_cost = calc_cost(v);
		if (vis.find(aux_cost) != vis.end())
		{
			return aux_cost;
		}
		vis[aux_cost] = step;
		step++;
	}
}

void update_p2(vector<vector<string>>& levels)
{
	auto levels_copy = levels;

	for (ll lvl = 0; lvl < 1000; ++lvl)
	{
		auto v_copy = levels[lvl];
		for (ll x = 0; x < 5; ++x)
		{
			for (ll y = 0; y < 5; ++y)
			{
				ll cnt = 0;

				for (ll i = 0; i < 4; ++i)
				{
					ll new_x = x + dirX[i];
					ll new_y = y + dirY[i];

					if (x + dirX[i] < 0 || x + dirX[i] > 4 || y + dirY[i] < 0 || y + dirY[i] > 4)
					{
						if (lvl > 0 && levels[lvl - 1][2 + dirX[i]][2 + dirY[i]] == '#')
						{
							cnt++;
						}
					}
					else
					{
						if (levels[lvl][x + dirX[i]][y + dirY[i]] == '?')
						{
							for (ll j = 0; j < 5; ++j)
							{
								if (i == 0 && levels[lvl + 1][4][j] == '#')
									cnt++;
								if (i == 1 && levels[lvl + 1][j][4] == '#')
									cnt++;
								if (i == 2 && levels[lvl + 1][0][j] == '#')
									cnt++;
								if (i == 3 && levels[lvl + 1][j][0] == '#')
									cnt++;
							}
						}
						if (levels[lvl][x + dirX[i]][y + dirY[i]] == '#')
						{
							cnt++;
						}
					}
				}
				if (levels[lvl][x][y] == '#' && cnt != 1)
				{
					v_copy[x][y] = '.';
				}
				if (levels[lvl][x][y] == '.' && (cnt == 1 || cnt == 2))
				{
					v_copy[x][y] = '#';
				}
			}
		}
		levels_copy[lvl] = v_copy;
	}
	levels = levels_copy;
}

ll count_bugs(vector<string> v)
{
	vector<vector<string>> levels;

	for (ll lvl = 0; lvl < 1000; ++lvl)
	{
		if (lvl == 500)
		{
			levels.push_back(v);
		}
		levels.push_back(default_mat);
	}

	for (ll minutes = 0; minutes < 200; ++minutes)
	{
		update_p2(levels);
	}

	ll bugs = 0;

	for (ll lvl = 0; lvl < 1000; ++lvl)
	{
		for (ll x = 0; x < 5; ++x)
		{
			for (ll y = 0; y < 5; ++y)
			{
				if (levels[lvl][x][y] == '#')
				{
					bugs++;
				}
			}
		}
	}

	return bugs;
}

int main()
{
	ios::sync_with_stdio(false);

	vector<string> v;

	while (!in.eof())
	{
		string s;
		in >> s;
		v.push_back(s);
	}
	
	cout << "Part1: " << part1(v) << endl;

	for (int i = 0; i < 5; ++i)
	{
		default_mat.push_back(string(5, '.'));
	}

	v[2][2] = default_mat[2][2] = '?';

	cout << "Part2: " << count_bugs(v);
	return 0;
}