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
	vector <long long> vec;

	while (!in.eof())
	{
		in >> x;
		vec.push_back(x);
	}

	vec[1] = 12;
	vec[2] = 2;

	int itt = 0;

	while (1)
	{
		for (auto it : vec)
			cout << it << ' ';
		cout << endl;
		if (vec[itt] == 1)
		{
			vec[vec[itt + 3]] = vec[vec[itt + 1]] +  vec[vec[itt + 2]];
		}
		else if (vec[itt] == 2)
		{
			vec[vec[itt + 3]] = vec[vec[itt + 1]] * vec[vec[itt + 2]];
		}
		else if (vec[itt] == 99)
		{
			break;
		}
		itt += 4;
	}

	cout << vec[0];
}
