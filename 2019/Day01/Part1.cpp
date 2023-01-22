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
		ans += x / 3 - 2; // P1
	}

	cout << ans << endl;
}
