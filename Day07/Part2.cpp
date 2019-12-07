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
		
		inps[0].push(phases[0]);
		inps[1].push(phases[1]);
		inps[2].push(phases[2]);
		inps[3].push(phases[3]);
		inps[4].push(phases[4]);
		inps[0].push(0);

		while (1)
		{
			do_instructions(vects[0], pcs[0], inps[0], inps[1]);
			do_instructions(vects[1], pcs[1], inps[1], inps[2]);
			do_instructions(vects[2], pcs[2], inps[2], inps[3]);
			do_instructions(vects[3], pcs[3], inps[3], inps[4]);
			if (do_instructions(vects[4], pcs[4], inps[4], inps[0]))
				break;
		}
		MAX_RES = max(MAX_RES, inps[0].front());
	}
	cout << MAX_RES << endl;

}

