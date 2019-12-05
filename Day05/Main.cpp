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

int main()
{
	ios::sync_with_stdio(false);

	vector <int> vec;

	int x, index;

	while (!in.eof())
	{
		in >> x;
		vec.push_back(x);
	}

	index = 0;


	int INPUT_VALUE = 5; /// HERE ///

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
			vec[vec[index + 1]] = INPUT_VALUE;
			index += 2;
		}
		else if (opcode == 4) //output
		{
			cout << vec[vec[index + 1]] << endl;
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