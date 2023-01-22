
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

ll relativeBase = 0;

ll mat[200][200];

ll dirX[4] = { -1, 0, 1 , 0 };
ll dirY[4] = { 0, 1, 0 , -1 };

void split_instructions(vector<ll> vec, ll index, ll& opcode, ll& C, ll& B, ll& A)
{
	ll coded = vec[index];

	// mode
	// A B C OP
	// - - - --
	opcode = vec[index] % 100;
	C = vec[index] / 100 % 10;
	B = vec[index] / 1000 % 10;
	C = vec[index] / 10000;
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
	case 2:
		C = vec[index + 1] + relativeBase;
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
	case 2:
		B = vec[index + 2] + relativeBase;
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
	case 2:
		A = vec[index + 3] + relativeBase;
		break;
	}
}

bool do_instructions(vector<ll> vec, ll index, queue<ll>& inputQ, queue<ll>& outputQ)
{
	while (1)
	{
		ll opcode, C, B, A;

		opcode = vec[index] % 100;

		if (opcode == 99)
		{
			return true;
		}

		C = vec[index] / 100 % 10;
		B = vec[index] / 1000 % 10;
		C = vec[index] / 10000;

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

			//cout << "Input : " << vec[C] << endl;
			inputQ.pop();
			index += 2;
			break;
		case 4: // OUTPUT
			cout << "Output : " << vec[C] << endl;
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
		case 9: // relative base += C
			relativeBase += vec[C];
			index += 2;
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

	for (int k = 0; k <= 10000; k++)
		vec.push_back(0);

	queue<ll> inp, out;
	vector<vector<ll>>mat;
	for (int i = 1; i <= 3000; ++i)
	{
		vector<ll> aux_v;
		for (int j = 1; j <= 3000; ++j)
		{
			cout << i << ' ' << j << endl;
			inp.push(i);
			inp.push(j);
			do_instructions(vec, 0, inp, out);
			aux_v.push_back(out.front());
			out.pop();
		}
		mat.push_back(aux_v);
	}

	ll i = 0, j = 0;

	while (1)
	{
		while (!mat[i + 99][j])
		{
			++j;
		}

		if (mat[i][j + 99])
		{
			cout << i << j << endl;
		}

		if (mat[i][j])
		{
			++i;
		}
	}
}
