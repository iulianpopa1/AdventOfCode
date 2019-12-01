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

ifstream in("input.txt");

//ios::sync_with_stdio(false);

int main()
{
	ios::sync_with_stdio(false);

	int ans = 0;

	while (!in.eof())
	{
		int x;
		in >> x;
		while (x > 0)
		{
			x = x / 3 - 2;
			if (x > 0)
				ans += x;
		}
	}

	cout << ans << endl;
}
