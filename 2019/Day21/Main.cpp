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

	vector <ll> vec, vec_org;
	ll x;

	while (!in.eof())
	{
		in >> x;
		vec.push_back(x);
	}

	for (int k = 0; k < 10000; k++)
		vec.push_back(0);

	ll index = 0, last_val;
	queue<ll> inp, out;
	vector<string> instr;
	string instructs; 
	instr.push_back("NOT A T");
	instr.push_back("AND D T");
	instr.push_back("OR T J");
	instr.push_back("NOT B T");
	instr.push_back("AND D T");
	instr.push_back("OR T J");
	instr.push_back("NOT C T");
	instr.push_back("AND D T");
	instr.push_back("OR T J");
	instr.push_back("AND D J");
	instr.push_back("WALK");

	for (auto it : instr)
	{
		for (auto itt : it)
		{
			inp.push(itt);
		}
		inp.push('\n');
	}

	do_instructions(vec, index, inp, out);

	while (out.size() > 0)
	{
		last_val = out.front();
		out.pop();
	}
	cout << "Part1 : " << last_val << endl;

	instr.clear();
	instr.push_back("NOT A T");
	instr.push_back("AND D T");
	instr.push_back("OR T J");
	instr.push_back("NOT B T");
	instr.push_back("AND D T");
	instr.push_back("OR T J");
	instr.push_back("NOT C T");
	instr.push_back("AND D T");
	instr.push_back("AND H T");
	instr.push_back("OR T J");
	instr.push_back("AND D J");
	instr.push_back("RUN");
	
	for (auto it : instr)
	{
		for (auto itt : it)
		{
			inp.push(itt);
		}
		inp.push('\n');
	}

	do_instructions(vec, index, inp, out);

	while (out.size() > 0)
	{
		last_val = out.front();
		out.pop();
	}
	cout << "Part2 : " << last_val << endl;

}