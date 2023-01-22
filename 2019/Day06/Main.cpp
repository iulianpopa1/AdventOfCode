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

map<string, vector<string>> orbits;
set<string> vis;
map<string, int> dists;
bool part2 = false;

void dfs(string node, int dist)
{
	vis.insert(node);
	
	if (node == "SAN" && part2 == true)
	{
		cout << dist  - 2 << endl;
		return;
	}

	for(auto it : orbits[node])
	{ 
		if (vis.find(it) == vis.end())
		{
			dists[it] = dist;
			dfs(it, dist + 1);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);

	while (!in.eof())
	{
		string x, y;
		in >> x >> y;
		orbits[x].push_back(y);
		orbits[y].push_back(x);
	}

	orbits.erase(orbits.find(""));

	int sum = 0;

	dfs("COM", 1);
	
	for (auto it : dists)
		sum += it.second;

	cout << sum << endl;
	//Part2
	vis.clear();
	part2 = true;
	dfs("YOU", 0);
}