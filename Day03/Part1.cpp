/* PASTE THE CODE HERE! 🡇

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


set<pair<int, int>> mapp;
//ios::sync_with_stdio(false);
int N = 20000;

int calc_dist(int x, int y)
{
	return (abs(N/2 - x) + abs(N/2 - y));
}



int main()
{
	ios::sync_with_stdio(false);

	char dir;
	int dist;

	int min_dist = 999999;
	int x, y;
	x = N/2; y = N/2;
	while (!in.eof())
	{
		in >> dir >> dist;
		cout << dir << ' ' << dist << endl;
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
			mapp.insert(make_pair( x, y ));
		}
	}
	//print_mat();


	x = N / 2; y = N / 2;

	while (!in.eof())
	{
		in >> dir >> dist;
		cout << dir << ' ' << dist << endl;
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

			if (mapp.find({ x, y }) != mapp.end())
				min_dist = min(calc_dist(x, y), min_dist);
		}

	}
	cout << "MIn : " << min_dist;
}






PASTE THE CODE HERE! 🡅 */