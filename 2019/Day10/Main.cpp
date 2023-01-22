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
#include <math.h>

using namespace std;
using ll = long long;

ifstream in("input.txt");

// (00) (10) (20)
// (01) (11) (21)
// (02) (12) (22)

vector<pair<int, int>> asteroids;
int source_id;

int main()
{
	ios::sync_with_stdio(false);
	
	vector<string> input_mat;

	while (!in.eof())
	{
		string x;
		in >> x;
		input_mat.push_back(x);
	}
	
	for(int y = 0; y < input_mat.size(); ++y)
		for (int x = 0; x < input_mat[y].size(); ++x)
			if (input_mat[y][x] == '#')
				asteroids.push_back(make_pair(x, y));

	int max = 0;
	int max_p = 0;

	for (int i = 0; i < asteroids.size(); ++i)
	{
		vector<float> angles;
		int cnt = 0;

		for (int j = 0; j < asteroids.size(); ++j)
		{
			if (i == j)
				continue;
			float angle = (float)atan2(asteroids[i].first - asteroids[j].first, asteroids[i].second - asteroids[j].second);
			if (find(angles.begin(), angles.end(), angle) == angles.end())
			{
				angles.push_back(angle);
				cnt++;
			}
		}

		if (cnt > max)
		{
			max = cnt;
			max_p = i;
		}
	}

	cout << "Part1 : (" << asteroids[max_p].first << ',' << asteroids[max_p].second << ") => " << max << endl;
	source_id = max_p;

	map<float, map<float, int>> neg_angles_map;
	map<float, map<float, int>> pos_angles_map;


	for (int j = 0; j < asteroids.size(); ++j)
	{
		if (max_p == j)
			continue;

		float angle = (float)atan2(asteroids[max_p].first - asteroids[j].first, asteroids[max_p].second - asteroids[j].second);
		if (angle <= 0)
		{
			neg_angles_map[angle].insert({ pow(asteroids[j].first - asteroids[source_id].first, 2) + pow(asteroids[j].second - asteroids[source_id].second, 2), j });
		}
		else
		{
			pos_angles_map[angle].insert({ pow(asteroids[j].first - asteroids[source_id].first, 2) + pow(asteroids[j].second - asteroids[source_id].second, 2), j });
		}

	}

	int destroyed_ast = 0;
	int destroyed_x, destroyed_y;
	for (auto it = neg_angles_map.rbegin(); it != neg_angles_map.rend(); ++it)
	{
		destroyed_ast += 1;
		if (destroyed_ast == 200)
		{
			destroyed_x = asteroids[it->second.begin()->second].first;
			destroyed_y = asteroids[it->second.begin()->second].second;
		}
		it->second.erase(it->second.begin());
	}	

	for (auto it = pos_angles_map.rbegin(); it != pos_angles_map.rend(); ++it)
	{
		destroyed_ast += 1;		
		if (destroyed_ast == 200)
		{
			destroyed_x = asteroids[it->second.begin()->second].first;
			destroyed_y = asteroids[it->second.begin()->second].second;
		}
		it->second.erase(it->second.begin());
	}

	cout << "Part2 : (" << destroyed_x << ',' << destroyed_y << ") => " << destroyed_x * 100 + destroyed_y;
}