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

//ios::sync_with_stdio(false);

int main()
{
	ios::sync_with_stdio(false);
	long long x;
	vector <long long> vo, vc;

	while (!in.eof())
	{
		in >> x;
		vo.push_back(x);
	}
	int itt = 0;

	for (int x1 = 0; x1 <= 100; x1++) {
		for (int x2 = 0; x2 <= 100; x2++)
		{
			vc = vo;
			vc[1] = x1;
			vc[2] = x2;
			itt = 0;
			while (1)
			{
				if (vc[itt] > vc.size() || vc[itt + 1] > vc.size() || vc[itt + 2] > vc.size() || vc[itt + 3] > vc.size())
					break;
				if (vc[itt] == 1)
				{
					vc[vc[itt + 3]] = vc[vc[itt + 1]] + vc[vc[itt + 2]];
				}
				else if (vc[itt] == 2)
				{
					vc[vc[itt + 3]] = vc[vc[itt + 1]] * vc[vc[itt + 2]];
				}
				else if (vc[itt] == 99)
				{
					break;
				}
				itt += 4;
			}

			if (vc[0] == 19690720)
				cout << x1 << ' ' << x2;
		}
	}
}