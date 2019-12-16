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
#include <tuple>


using namespace std;
using ll = long long;

ifstream in("P_input.txt");

ll relativeBase = 0;

ll mat[200][200];

ll dirX[4] = { -1, 1, 0 , 0 };
ll dirY[4] = { 0, 0, -1 , 1 };

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

bool do_instructions(vector<ll>& vec, queue<ll>& inputQ, queue<ll>& outputQ)
{
	ll index = 0;
	while (1)
	{
		//cout << "index : " << index << endl;
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
			//cout << "Output : " << vec[C] << endl;
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

void change_dir(ll& curr_dir, ll output_val)
{
	if (output_val == 0)
		curr_dir += 3;
	else
		curr_dir += 1;

	curr_dir %= 4;
}

void Print_mat()
{
	for(int i = 0; i < 200; ++i)
	{ 
		for (int j = 0; j < 200; ++j)
			switch (mat[i][j])
			{
			case 0: cout << "#";
				break;
			case 1: cout << ".";
				break;
			case 2: cout << "O";
				break;
			}
		cout << endl;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	
	vector <ll> vec;
	map<pair<int, int>, int> game_map;
	queue<tuple< vector <ll>, string, ll , ll > >robots;

	while (!in.eof())
	{
		ll x;
		in >> x;
		vec.push_back(x);
	}

	for (int k = 0; k < 100; k++)
		vec.push_back(0);
	
	ll xx, OX, OY;
	queue<ll> inp, out;
	bool oxy_found = false;

	robots.push(make_tuple(vec, "", 0, 0));
	set<pair<ll, ll>> visited;

	while (1)
	{
		if (robots.size() == 0)
			break;
		auto robot = robots.front();
		robots.pop();
		for (ll i = 0; i < 4; ++i)
		{
			auto x = get <2>(robot) + dirX[i];
			auto y = get <3>(robot) + dirY[i];
			if (visited.find(make_pair(x, y)) != visited.end())
				continue;
			visited.insert(make_pair(x, y));
			
			auto aux_vec = get <0>(robot);
			auto aux_path = get <1> (robot) + to_string(i);

		
			inp.push(i + 1); 
			do_instructions(aux_vec, inp, out);
			if (out.size() < 1) break;
			xx = out.front(); out.pop();

			game_map[make_pair(x, y)] = xx;
			mat[ x+ 100][y + 100] = xx;

			if (xx == 0)
			{
				continue;
			}
			if (xx == 1)
			{				
				robots.push(make_tuple(aux_vec, aux_path , x, y));
			}
			if (xx == 2)
			{
				cout << "Part1: " << aux_path.size() << endl;
				OX = x; OY = y;
				oxy_found = true;
				break;
			}
		}
	}
	//Print_mat(); //
	//PART 2
	visited.clear();
	queue<tuple<ll, ll, ll>> q;
	q.push(make_tuple(OX, OY, 0));
	visited.insert(make_pair(OX, OY));
	ll max_dist = 0;

	while (!q.empty())
	{
		auto x = get<0>(q.front());
		auto y = get<1>(q.front());
		auto dist = get<2>(q.front());
		q.pop();
		max_dist = max(max_dist, dist);

		for (ll i = 0; i < 4; ++i)
		{
			ll aux_x = x + dirX[i];
			ll aux_y = y + dirY[i];
			if (visited.find(make_pair(aux_x, aux_y)) != visited.end())
				continue;
			visited.insert(make_pair(aux_x, aux_y));
			if (game_map[make_pair(aux_x, aux_y)] != 0)
			{
				q.push(make_tuple(aux_x, aux_y, dist + 1));
			}
		}

	}
	cout << "Part2: " << max_dist << endl;
}
