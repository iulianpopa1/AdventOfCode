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

ifstream in("P_input.txt");
// parameter modes - single digits
// 0 - position mode ~ v[param]
// 1 - immediate mode ~ param

int do_instructions(vector<int> vec, int inp1, int inp2)
{
	int index = 0;
	bool inp_was_used = false;

	while (1)
	{
		int val = vec[index];
		int opcode = val % 100;
		val /= 100;
		int modeC = val % 10;
		val /= 10;
		int modeB = val % 10;
		val /= 10;
		int modeA = val % 10;
		val /= 10;

		int opB = -1, opC = -1;

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
			if (inp_was_used == false)
			{
				vec[vec[index + 1]] = inp1;
				inp_was_used = true;
			}
			else
			{
				vec[vec[index + 1]] = inp2;
			}
			index += 2;
		}
		else if (opcode == 4) //output
		{
			return  vec[vec[index + 1]];
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
			break;
		}
	}
}


int main()
{
	ios::sync_with_stdio(false);

	vector <int> vec;
	vector <int> vec_copy;

	int x;

	while (!in.eof())
	{
		in >> x;
		vec.push_back(x);
	}

	int phases[] = { 0, 1, 2, 3, 4 };
	int MAX_RES = -1;

	while (next_permutation(phases, phases + 5))
	{
		int input = 0;

		for (int i = 0; i < 5; ++i)
		{
			vec_copy = vec;
			input = do_instructions(vec_copy, phases[i], input);

			if (i == 4)
				MAX_RES = max(MAX_RES, input);
		}
	}
	cout << MAX_RES << endl;
}

//The first amplifier's input value is 0
//and the last amplifier's output leads to your ship's thrusters.
//phase setting (an integer from 0 to 4)
//Each phase setting is used exactly once
