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

ll relativeBase;


bool do_instructions(vector<ll>&vec, queue<ll>& inp, queue<ll>& out)
{
	ll index = 0;
	relativeBase = 0;

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

		if (opcode == 99)
		{
			return true;
		}

		ll opA, opB, opC;

		if (modeC == 0)
			opC = vec[index + 1];
		else if (modeC == 1)
			opC = index + 1;
		else
			opC = vec[index + 1] + relativeBase;

		if (modeB == 0)
			opB = vec[index + 2];
		else if (modeB == 1)
			opB = index + 2;
		else
			opB = vec[index + 2] + relativeBase;

		if (modeA == 0)
			opA = vec[index + 3];
		else if (modeA == 1)
			opA = index + 3;
		else
			opA = vec[index + 3] + relativeBase;
		if (opcode == 1)//sum A = B + C
		{
			vec[opA] = vec[opC] + vec[opB];
			index += 4;
		}
		else if (opcode == 2) //multiply A = B * C
		{
			vec[opA] = vec[opC] * vec[opB];

			index += 4;
		}
		else if (opcode == 3) //input
		{
			if (inp.empty())
				return false;

			vec[opC] = inp.front();
			inp.pop();

			index += 2;
		}
		else if (opcode == 4) //output
		{
			out.push(vec[opC]);
			index += 2;
		}
		else if (opcode == 5) // jump-if-true
		{
			if (vec[opC] != 0)
				index = vec[opB];
			else
				index += 3;
		}
		else if (opcode == 6) // jump-if-false
		{
			if (vec[opC] == 0)
				index = vec[opB];
			else
				index += 3;
		}
		else if (opcode == 7)
		{
			if (vec[opC] < vec[opB])
				vec[opA] = 1;
			else
				vec[opA] = 0;

			index += 4;
		}
		else if (opcode == 8)
		{
			if (vec[opC] == vec[opB])
				vec[opA] = 1;
			else
				vec[opA] = 0;

			index += 4;
		}
		else if (opcode == 9)
		{
			relativeBase += vec[opC];

			index += 2;
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
	ll index = 0;
	queue<ll> inp, out;

	inp.push(1); // 1 for part1, 2 for part2

	do_instructions(vec, inp, out);

	while (!out.empty())
	{
		cout << out.front() << endl;
		out.pop();
	}

}
