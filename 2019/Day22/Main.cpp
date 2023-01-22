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
#include <sstream>

using namespace std;
using ll = long long;

ifstream in("input.txt");
//ifstream in("P_input.txt");

// instr number :
// 1 - deal into new stack
// 2 - cut n cards
// 3 - deal with increment n

/* Iterative Function to calculate (x^y)%p in O(log y) */
int power(int x, unsigned int y, int p)
{
	int res = 1;      // Initialize result 

	x = x % p;  // Update x if it is more than or  
				// equal to p 

	while (y > 0)
	{
		// If y is odd, multiply x with result 
		if (y & 1)
			res = (res * x) % p;

		// y must be even now 
		y = y >> 1; // y = y/2 
		x = (x * x) % p;
	}
	return res;
}

void deal_stack(ll size, ll& pos)
{
	pos = size - pos - 1;
}

void cut_cards(ll size, ll n, ll& pos)
{
	if (n >= 0)
	{
		if (pos >= n)
		{
			pos -= n;
		}
		else
		{
			pos += (size - n);
		}
	}
	else
	{
		n *= -1;
		if (pos >= size - n)
		{
			pos -= (size - n);
		}
		else
		{
			pos += n;
		}
	}
}

void deal_increment(ll size, ll n, ll& pos)
{
	pos = (pos % size) * (n % size) % size;
}

void execute_instruct(vector<pair<int, int>> instructs, ll deck_size, ll & pos)
{
	for (auto it : instructs)
	{
		if (it.first == 1)
		{
			deal_stack(deck_size, pos);
		}
		else if (it.first == 2)
		{
			cut_cards(deck_size, it.second, pos);
		}
		else
		{
			deal_increment(deck_size, it.second, pos);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);

	ll deck_size_p1 = 10007;
	ll deck_size_p2 = 119315717514047;
	ll times = 101741582076661;
	ll pos, i;

	vector<pair<int, int>> instructs;

	while (!in.eof())
	{
		string line;
		getline(in, line);
		istringstream ss(line);
		string word;
		ss >> word;
		if (word == "cut")
		{
			ll n;
			ss >> n;
			instructs.push_back({ 2, n });
		}
		else
		{
			while (ss)
				ss >> word;
			if (word == "stack")
			{
				instructs.push_back({ 1, 0 });
			}
			else
			{
				ll n = stoll(word);
				instructs.push_back({ 3, n });
			}
		}
	}

	pos = 2019;
	execute_instruct(instructs, deck_size_p1, pos);
	cout << "Part1: " << pos << endl;

	pos = 2020;

	map<ll, ll> vis;

	for (i = 1; i < times; ++i)
	{
		execute_instruct(instructs, deck_size_p2, pos);

		if (vis.find(pos) != vis.end())
			break;
		if (vis.size() % 123456789 == 0)
			cout << "reached \n";
		vis[pos] = i;
	}

	cout << i;

	return 0;
}