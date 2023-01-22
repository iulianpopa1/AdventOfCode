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

bool do_instructions(vector<ll> &vec , ll &index, queue<ll> &inputQ, queue<ll> &outputQ)
{
	while (1)
	{
		ll opcode, C, B, A;

		split_instructions(vec, index, opcode, C, B, A);

		if (opcode == 99)
		{
			return true;
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
			if (inputQ.empty())
				return false;
			vec[C] = inputQ.front();
			inputQ.pop();
			index += 2;
			break;
		case 4: // OUTPUT
			outputQ.push(vec[C]);
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
	ll phases[] = { 5, 6, 7, 8, 9 };

	while (next_permutation(phases, phases + 5))
	{
		vector<vector<ll>> vects(5, vec);
		vector<queue<ll>> inps(5);
		vector<ll> pcs(5, 0);
	
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