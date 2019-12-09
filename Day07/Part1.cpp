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

ll do_instructions(vector<ll> vec, ll input1, ll input2)
{
	ll index = 0;
	bool inp_was_used = false;

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
			if (inp_was_used == false)
				vec[C] = input1,
				inp_was_used = true;
			else
				vec[C] = input2;
			index += 2;
			break;
		case 4: // OUTPUT
			return vec[C];
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

int main()
{
	ios::sync_with_stdio(false);

	vector <ll> vec;

	while (!in.eof())
	{
		ll x;
		in >> x;
		vec.push_back(x);
	}

	ll MAX_RES = -1;
	ll phases[] = { 0, 1, 2, 3, 4 };

	while (next_permutation(phases, phases + 5))
	{
		ll input = 0;

		for (ll i = 0; i < 5; ++i)
		{
			input = do_instructions(vec, phases[i], input);

			if (i == 4)
				MAX_RES = max(MAX_RES, input);
		}
	}

	cout << MAX_RES << endl;
}
