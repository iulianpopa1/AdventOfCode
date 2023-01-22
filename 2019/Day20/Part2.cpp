
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

class Point
{
public:
	ll x;
	ll y;
	ll step;
	ll level;

	Point(ll x = 0, ll y = 0, ll step = 0, ll level = 0)
	{
		this->x = x;
		this->y = y;
		this->step = step;
		this->level = level;
	}

	bool operator ==(const Point & obj) const
	{
		return ((this->x == obj.x) && (this->y == obj.y));
	}

	bool operator <(const Point & obj) const
	{
		if (this->x != obj.x)
			return this->x < obj.x;
		else
			return this->y < obj.y;

	}
};

ofstream out1("out1.txt");


bool is_big_letter(char x)
{
	if (x >= 65 && x <= 90)
		return true;
	return false;
}

void check_for_portal(vector<string> v, ll x, ll y, multimap<string, Point>& portals)
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
					portals.insert({ aux, Point(x, y + 2) });
				}
			
			if (y - 1 >= 0) 
				if(v[x][y - 1] == '.')
				{
					portals.insert({ aux, Point(x, y - 1) });
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
					portals.insert({ aux, Point(x + 2, y) });
				}
			if (x - 1 >= 0)
				if(v[x - 1][y] == '.')
				{
					portals.insert({ aux, Point(x - 1, y) });
				}
		}
	}
}

void link_portals(multimap<string, Point> solo_portals, map<Point, Point>& portals)
{
	for (auto it = solo_portals.begin(); it != solo_portals.end(); ++it)
	{
		auto itt = it;
		if (itt != solo_portals.end())
			++itt;
		if (it->first == itt->first)
		{
			portals[Point(it->second.x, it->second.y)] = Point(itt->second.x, itt->second.y);
			portals[Point(itt->second.x, itt->second.y)] = Point(it->second.x, it->second.y);
		}
		++it;
	}
}

void teleport(vector<string> v, queue<Point>& q, vector<vector<vector<bool>>>& vis, Point curr, Point curr_pair)
	{	
	out1 << "TP : " << curr.x << ' ' << curr.y << " | " << curr_pair.x << ' ' << curr_pair.y << endl;
	if (((curr.x > 3) && (curr.y > 3)) && ((curr.x < v.size() - 3) && (curr.y < v[0].size() - 3)))
	{
		q.push(Point(curr_pair.x, curr_pair.y, curr.step + 1, curr.level + 1));
		vis[curr.x][curr.y][curr.level + 1] = true;
	}
	else
	{
		if (curr.level - 1 >= 0)
		{

			q.push(Point(curr_pair.x, curr_pair.y, curr.step + 1, curr.level - 1));
			vis[curr_pair.x][curr_pair.y][curr.level - 1] = true;
		}
	}
}

ll BFS(vector<string> v, map<Point, Point> portals, Point start, Point stop)
{
	vector<vector<vector<bool>>> vis(1300, vector<vector<bool>>(1300, vector<bool>(1300)));
	
	queue<Point> q;

	q.push(start);
	vis[start.x][start.y][0] = true;

	while (!q.empty())
	{
		auto curr_point = q.front();
		q.pop();

		if (curr_point == stop && curr_point.level == 0)
		{
			return curr_point.step;
		}

		for (int i = 0; i < 4; ++i)
		{
			ll new_x = curr_point.x + dirX[i];
			ll new_y = curr_point.y + dirY[i];
			if (new_x >= 0 && new_y >= 0 && new_x < v.size() && new_y < v[0].size() 
				&& !vis[new_x][new_y][curr_point.level])
			{
				if (v[new_x][new_y] == '.')
				{
					q.push(Point(new_x, new_y, curr_point.step + 1, curr_point.level));
					vis[new_x][new_y][curr_point.level] = true;
				}
				if (is_big_letter(v[new_x][new_y]))
				{
					if (curr_point == start || curr_point == stop)
						continue;

					teleport(v, q, vis, curr_point, portals[curr_point]);
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

	multimap<string, Point> solo_portals;
	Point start, stop;

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

	map<Point, Point> portals;

	link_portals(solo_portals, portals);
	cout << "BFS START\n";
	cout << "Part2 : " << BFS(v, portals, start, stop) << endl;
	return 0;
}
