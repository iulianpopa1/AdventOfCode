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

char pixel(ll x, ll y)
{
	ll layer = 0;
	char pixel;

	while (1)
	{
		pixel = layers[layer][25 * y + x];

		if (pixel != '2')
			return pixel;

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

	ll min_0 = LONG_MAX, min_12;

	for (auto it : layers)
	{
		ll c0 = count(it.begin(), it.end(), '0');
		ll c1 = count(it.begin(), it.end(), '1');
		ll c2 = count(it.begin(), it.end(), '2');
	
		if (c0 < min_0)
		{
			min_0 = c0;
			min_12 = c1 * c2;
		}
	}

	cout << "Part1 : " <<  min_12 << endl;
	cout << "Part2 : " << endl;

	for(ll y = 0; y < 6; ++y)
	{ 
		for (ll x = 0; x < 25; ++x)
		{
			char pixx = pixel(x, y);
			if ( pixx == '0') cout << ' ';
			if ( pixx == '1') cout << '$';
			
		}
		cout << endl;
	}
}