
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

ll dirX[] = { -1, 0, 1 , 0 };
ll dirY[] = {  0, 1 , 0, -1 };

class Coordinate
{
public:
	ll x;
	ll y;

	Coordinate(ll x = 0, ll y = 0)
	{
		this->x = x;
		this->y = y;
	}

	bool operator ==(const Coordinate & obj) const
	{
		return ((this->x == obj.x) && (this->y == obj.y));
	}

	bool operator <(const Coordinate & obj) const
	{
		if (this->x != obj.x)
			return this->x < obj.x;
		else
			return this->y < obj.y;

	}
};

bool is_big_letter(char x)
{
	if (x >= 65 && x <= 90)
		return true;
	return false;
}

void check_for_portal(vector<string> v, ll x, ll y, multimap<string, Coordinate>& portals)
{
	if (is_big_letter(v[x][y]))
	{
		if (y + 1 < v[0].size() && is_big_letter(v[x][y + 1]))
		{
			string aux = "";
			aux += v[x][y];
			aux += v[x][y + 1];
			if (y + 2 < v[0].size())
				if( v[x][y + 2] == '.')
				{
					portals.insert({ aux, Coordinate(x, y + 2) });
				}

			if (y - 1 >= 0)
				if(v[x][y - 1] == '.')
				{
					portals.insert({ aux, Coordinate(x, y - 1) });
				}
		}

		if (x + 1 < v.size() && is_big_letter(v[x + 1][y]))
		{
			string aux = "";
			aux += v[x][y];
			aux += v[x + 1][y];
			if (x + 2 < v.size())
				if(v[x + 2][y] == '.')
				{
					portals.insert({ aux, Coordinate(x + 2, y) });
				}
			if (x - 1 >= 0)
				if(v[x - 1][y] == '.')
				{
					portals.insert({ aux, Coordinate(x - 1, y) });
				}
		}
	}
}

void link_portals(multimap<string, Coordinate> solo_portals, map<Coordinate, Coordinate>& portals)
{
	for (auto it = solo_portals.begin(); it != solo_portals.end(); ++it)
	{
		auto itt = it;
		if (itt != solo_portals.end())
			++itt;
		if (it->first == itt->first)
		{
			portals[Coordinate(it->second.x, it->second.y)] = Coordinate(itt->second.x, itt->second.y);
			portals[Coordinate(itt->second.x, itt->second.y)] = Coordinate(it->second.x, it->second.y);
		}
		++it;
	}
}

ll BFS(vector<string> v, map<Coordinate, Coordinate> portals, Coordinate start, Coordinate stop)
{
	vector<vector<bool>>vis(130, vector<bool>(130));

	queue<pair<Coordinate, ll>> q;
	q.push({ start, 0 });
	vis[start.x][start.y] = true;

	while (!q.empty())
	{
		auto front = q.front();
		Coordinate curr = front.first;

		q.pop();

		if (curr == stop)
		{
			return front.second;
		}

		for (int i = 0; i < 4; ++i)
		{
			ll new_x = curr.x + dirX[i];
			ll new_y = curr.y + dirY[i];

			if (new_x >= 0 && new_y >= 0 && new_x < v.size() && new_y < v[0].size() && !vis[new_x][new_y])
			{
				if (v[new_x][new_y] == '.')
				{
					q.push({ Coordinate(new_x, new_y), front.second + 1 });
					vis[new_x][new_y] = true;
				}
				if (is_big_letter(v[new_x][new_y]))
				{
					Coordinate aux_coord = portals[Coordinate(curr.x, curr.y)];
					q.push({ aux_coord, front.second + 1 });
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);

	vector<string> v;

	while (!in.eof())
	{
		string s;
		getline(in, s);
		v.push_back(s);
	}

	multimap<string, Coordinate> solo_portals;
	Coordinate start, stop;

	for (ll i = 0; i < v.size() - 1; ++i)
	{
		for (ll j = 0; j < v[0].size() - 1; ++j)
		{
			check_for_portal(v, i, j, solo_portals);
		}
	}

	start = solo_portals.find("AA")->second;
	stop = solo_portals.find("ZZ")->second;
	solo_portals.erase(solo_portals.find("AA"));
	solo_portals.erase(solo_portals.find("ZZ"));

	cout << "START: " << start.x << ' ' << start.y << endl;
	cout << "STOP : " << stop.x << ' ' << stop.y << endl;

	map<Coordinate, Coordinate> portals;

	link_portals(solo_portals, portals);

	cout << "Part1 : " << BFS(v, portals, start, stop) << endl;
	return 0;
}
