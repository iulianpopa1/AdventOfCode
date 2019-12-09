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

void split_instructions(vector<ll> vec, ll index, ll& opcode, ll& C, ll& B, ll& A)
{
	ll coded = vec[index];

	// mode
	// A B C OP
	// - - - --
	opcode = coded % 100;
	coded /= 100;
	C = coded % 10;
	coded /= 10;
	B = coded % 10;
	coded /= 10;
	A = coded % 10;
	coded /= 10;
}

void decode_instructions(vector<ll> vec, ll index, ll& C, ll& B, ll& A)
{
	switch (C)
	{
	case 0:
		C = vec[index + 1];
		break;
	case 1:
		C = index + 1;
		break;
	}

	switch (B)
	{
	case 0:
		B = vec[index + 2];
		break;
	case 1:
		B = index + 2;
		break;
	}

	switch (A)
	{
	case 0:
		A = vec[index + 3];
		break;
	case 1:
		A = index + 3;
		break;
	}
}

void execute_instructions(vector<ll> vec, ll INPUT_VALUE)
{
	ll index = 0;
	while (1)
	{
		ll opcode, C, B, A;

		split_instructions(vec, index, opcode, C, B, A);

		if (opcode == 99)
		{
			break;
		}

		decode_instructions(vec, index, C, B, A);


		switch (opcode)
		{
		case 1: // A = B + C
			vec[A] = vec[B] + vec[C];
			index += 4;
			break;
		case 2: // A = B * C
			vec[A] = vec[B] * vec[C];
			index += 4;
			break;
		case 3: // C = INPUT
			vec[C] = INPUT_VALUE;
			index += 2;
			break;
		case 4: // OUTPUT
			if(vec[C])
				cout << vec[C] << endl;
			index += 2;
			break;
		case 5: // jump-if-true
			if (vec[C] != 0)
				index = vec[B];
			else
				index += 3;
			break;
		case 6: // jump-if-false
			if (vec[C] == 0)
				index = vec[B];
			else
				index += 3;
			break;
		case 7: // A = (C < B)
			if (vec[C] < vec[B])
				vec[A] = 1;
			else
				vec[A] = 0;
			index += 4;
			break;
		case 8: // A = (C == B)
			if (vec[C] == vec[B])
				vec[A] = 1;
			else
				vec[A] = 0;
			index += 4;
			break;
		}
	}
}

ifstream in("P_input.txt");
// parameter modes - single digits
// 0 - position mode ~ v[param]
// 1 - immediate mode ~ param

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


	cout << "PART 1 : ";
	ll INPUT_VALUE = 1; /// HERE /// PART1 - 1, PART2 - 5
	execute_instructions(vec, INPUT_VALUE);	

	cout << "PART 2 : ";
	INPUT_VALUE = 5; /// HERE /// PART1 - 1, PART2 - 5
	execute_instructions(vec, INPUT_VALUE);
}