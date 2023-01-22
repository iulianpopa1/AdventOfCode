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

void decode_instructions(vector<ll> vec, ll index, ll& C, ll& B, ll& A, ll & relativeBase)
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

bool do_instructions(vector<ll> & vec, ll & index, queue<ll>& inputQ, queue<ll>& outputQ, ll & relativeBase)
{
	while (1)
	{
		ll opcode, C, B, A;

		split_instructions(vec, index, opcode, C, B, A);

		if (opcode == 99)
		{
			return true;
		}

		decode_instructions(vec, index, C, B, A, relativeBase);

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
	ll x, nat_X = 0, nat_Y = 0;

	while (!in.eof())
	{
		in >> x;
		vec.push_back(x);
	}

	for (int k = 0; k < 10000; ++k)
	{
		vec.push_back(0);
	}

	vector <ll> instructs[50], index(50, 0), rel_base(50, 0);
	vector<queue<ll>> inp(50), out(50);

	for (int i = 0; i < 50; ++i)
	{
		instructs[i] = vec;
		inp[i].push(i);
		inp[i].push(-1);
		do_instructions(instructs[i], index[i], inp[i], out[i], rel_base[i]);
	}

	bool p1 = true, idle_net;
	ll last_X = -1, last_Y = -1;
	while (1)
	{
		for (int i = 0; i < 50; ++i)
		{
			do_instructions(instructs[i], index[i], inp[i], out[i], rel_base[i]);
			
			if (out[i].size() >= 3)
			{
				ll addr = out[i].front();
				out[i].pop();
				ll x = out[i].front();
				out[i].pop();
				ll y = out[i].front();
				out[i].pop();
			
				if (addr == 255)
				{
					
					nat_X = x;
					nat_Y = y;
					if (p1)
					{
						cout << "Part1: " << y << endl;
						p1 = false;
					}
				}
				else
				{ 
					inp[addr].push(x);
					inp[addr].push(y);
				}
			}
		}
		idle_net = true;

		for (auto & it : inp)
		{
			if (it.size() == 0)
			{
				it.push(-1);
			}
			else
			{
				idle_net = false;
			}
		}

		if (idle_net)
		{
			inp[0].pop();
			if (nat_X == last_X && nat_Y == last_Y)
			{
				cout << "Part2: " << nat_Y;
				return 0;
			}
			last_X = nat_X;
			inp[0].push(nat_X);
			last_Y = nat_Y;
			inp[0].push(nat_Y);
		}
	}

}