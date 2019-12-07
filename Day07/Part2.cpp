/**/
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


bool do_instructions(vector<ll> &vec , ll &index, queue<ll> &inp, queue<ll> &out)
{
	while (1)
	{
		ll val = vec[index];

		ll opcode = val % 100;
		val /= 100;
		ll modeC = val % 10;
		val /= 10;
		ll modeB = val % 10;
		val /= 10;
		ll modeA = val % 10;
		val /= 10;

		ll opB = -1, opC = -1;

		if (opcode == 1)//sum
		{
			if (modeB == 0)
				opB = vec[vec[index + 2]];
			else
				opB = vec[index + 2];

			if (modeC == 0)
				opC = vec[vec[index + 1]];
			else
				opC = vec[index + 1];

			vec[vec[index + 3]] = opB + opC;
			index += 4;
		}
		else if (opcode == 2) //multiply
		{
			if (modeB == 0)
				opB = vec[vec[index + 2]];
			else
				opB = vec[index + 2];

			if (modeC == 0) opC = vec[vec[index + 1]];
			else			opC = vec[index + 1];

			if (modeC == 0)
				opC = vec[vec[index + 1]];
			else
				opC = vec[index + 1];
			vec[vec[index + 3]] = opB * opC;

			index += 4;
		}
		else if (opcode == 3) //input
		{
			if (inp.empty())
				return false;

			vec[vec[index + 1]] = inp.front();
			inp.pop();

			index += 2;
		}
		else if (opcode == 4) //output
		{
			out.push(vec[vec[index + 1]]);

			index += 2;
		}
		else if (opcode == 5) // jump-if-true
		{
			if (modeB == 0)
				opB = vec[vec[index + 2]];
			else
				opB = vec[index + 2];
			if (modeC == 0)
				opC = vec[vec[index + 1]];
			else
				opC = vec[index + 1];

			if (opC != 0)
				index = opB;
			else
				index += 3;
		}
		else if (opcode == 6) // jump-if-false
		{
			if (modeB == 0)
				opB = vec[vec[index + 2]];
			else
				opB = vec[index + 2];
			if (modeC == 0)
				opC = vec[vec[index + 1]];
			else
				opC = vec[index + 1];

			if (opC == 0)
				index = opB;
			else
				index += 3;
		}
		else if (opcode == 7)
		{
			if (modeB == 0)
				opB = vec[vec[index + 2]];
			else
				opB = vec[index + 2];
			if (modeC == 0)
				opC = vec[vec[index + 1]];
			else
				opC = vec[index + 1];

			if (opC < opB)
				vec[vec[index + 3]] = 1;
			else
				vec[vec[index + 3]] = 0;
			index += 4;
		}
		else if (opcode == 8)
		{
			if (modeB == 0)
				opB = vec[vec[index + 2]];
			else
				opB = vec[index + 2];
			if (modeC == 0)
				opC = vec[vec[index + 1]];
			else
				opC = vec[index + 1];

			if (opC == opB)
				vec[vec[index + 3]] = 1;
			else
				vec[vec[index + 3]] = 0;

			index += 4;
		}
		else if (opcode == 99)
		{
			return true;
			break;
		}
	}
}


int main()
{
	ios::sync_with_stdio(false);

	vector <ll> vec;
	ll x;

	while (!in.eof())
	{
		in >> x;
		vec.push_back(x);
	}

	ll phases[] = { 5, 6, 7, 8, 9 };
	ll MAX_RES = -1;

	while (next_permutation(phases, phases + 5))
	{	
		vector<vector<ll>> vects;
		vector<queue<ll>> inps(5);
		vector<ll> pcs;

		vects.clear();
		vects.push_back(vec); vects.push_back(vec); vects.push_back(vec); vects.push_back(vec); vects.push_back(vec);
		pcs.push_back(0); pcs.push_back(0); pcs.push_back(0); pcs.push_back(0); pcs.push_back(0);
		
		for (int i = 0; i < 5; ++i)
			inps[i].push(phases[i]);

		inps[0].push(0);

		for (int i = 0; i < 5; ++i)
		{
			bool ok = do_instructions(vects[i], pcs[i], inps[i], inps[(i + 1) % 5]);

			if (i == 4)
				if (ok)
					break;
				else i = -1;
		}

		MAX_RES = max(MAX_RES, inps[0].front());
	}
	cout << MAX_RES << endl;

}
