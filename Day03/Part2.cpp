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

ifstream in("P_input.txt");


map<int, int> mapp;
//ios::sync_with_stdio(false);
int N = 20000;

int calc_dist(int x, int y)
{
	return (abs(N/2 - x) + abs(N/2 - y));
}

int hashh(int x, int y)
{
	return x % 999721 * 30949 + y;
}

int main()
{
	ios::sync_with_stdio(false);

	char dir;
	int dist;

	int min_dist = 99999999;
	int x, y;
	x = N/2; y = N/2;
	int steps = 1;
	while (!in.eof())
	{
		in >> dir >> dist;
		if (dir == 'X')
		{
			break;
		}

		for (int i = 1; i <= dist; ++i)
		{
			if (dir == 'R')
			{
				y += 1;
			}
			else if (dir == 'L')
			{
				y -= 1;
			}
			else if (dir == 'U')
			{
				x -= 1;
			}
			else if (dir == 'D')
			{
				x += 1;
			}
			mapp[hashh(x, y)] = steps;
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
			if (dir == 'R')
			{
				y += 1;
			}
			else if (dir == 'L')
			{
				y -= 1;
			}
			else if (dir == 'U')
			{
				x -= 1;
			}
			else if (dir == 'D')
			{
				x += 1;
			}

			if (mapp.find(hashh(x, y)) != mapp.end())
				min_dist = min(steps + mapp[hashh(x, y)], min_dist);
			steps++;
		}
		
	}
	cout << "MIn : " << min_dist + 1; 
}
