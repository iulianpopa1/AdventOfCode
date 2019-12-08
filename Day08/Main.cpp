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

vector<string> layers;
string strr;
char pixel(int x, int y)
{
	int layer = 0;
	int pix;
	while (1)
	{
		pix = strr[(25 * 6 * layer) + (y * 25) + x];
		if (pix != '2')
			return pix;
		layer++;
	}
}

int main()
{
	ios::sync_with_stdio(false);

	string y;
	while (!in.eof())
	{
		getline(in, strr);
		y = strr;
	}
	
	while (y.size()) {
		layers.push_back(y.substr(0, 25 * 6));
		y.erase(0, 25 * 6);
	}
	int c0, minc0 = 99999, minV = 0;

	for (auto it : layers)
	{
		c0 = count(it.begin(), it.end(), '0');
		if (c0 < minc0)
		{
			minc0 = c0;
			minV = count(it.begin(), it.end(), '1') * count(it.begin(), it.end(), '2');
		}
	}

	cout << minV << endl;

	for(int y = 0; y < 6; ++y)
	{ 
		for (int x = 0; x < 25; ++x)
		{
			char pixx = pixel(x, y);
			if ( pixx == '0') cout << ' ';
			if ( pixx == '1') cout << '#';
			
		}
		cout << endl;
	}
}