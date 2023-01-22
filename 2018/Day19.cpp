#include <bits/stdc++.h>

using namespace std;

ifstream in("input.txt");
//ofstream out("out.txt");

int ip, il;

struct instruction {
	string inst;
	int a, b, c;
};

int main() {
	vector<int> rez(6, 0);
	vector<instruction> v;
	string trash, inst;
	int a, b, c;
	ip = 0;
	in >> trash >> il;

	while (!in.eof()) {
		in >> inst;
		in >> a >> b >> c;
		v.push_back( { inst, a, b, c } );
	}

    //rez[0] = 1;       // Modificare pentru partea 2
                        //~~~~T~~~
	while (ip >= 0 && ip < v.size()) {
        rez[il] = ip;
        //v[ip].inst.c
		if (v[ip].inst == "addr") rez[v[ip].c] = rez[v[ip].a] + rez[v[ip].b];
		if (v[ip].inst == "addi") rez[v[ip].c] = rez[v[ip].a] + v[ip].b;
		if (v[ip].inst == "mulr") rez[v[ip].c] = rez[v[ip].a] * rez[v[ip].b];
		if (v[ip].inst == "muli") rez[v[ip].c] = rez[v[ip].a] * v[ip].b;
		if (v[ip].inst == "banr") rez[v[ip].c] = rez[v[ip].a] & rez[v[ip].b];
		if (v[ip].inst == "bani") rez[v[ip].c] = rez[v[ip].a] & v[ip].b;
		if (v[ip].inst == "borr") rez[v[ip].c] = rez[v[ip].a] | rez[v[ip].b];
		if (v[ip].inst == "bori") rez[v[ip].c] = rez[v[ip].a] | v[ip].b;
		if (v[ip].inst == "setr") rez[v[ip].c] = rez[v[ip].a];
		if (v[ip].inst == "seti") rez[v[ip].c] = v[ip].a;
		if (v[ip].inst == "gtir") rez[v[ip].c] = v[ip].a > rez[v[ip].b];
		if (v[ip].inst == "gtri") rez[v[ip].c] = rez[v[ip].a] > v[ip].b;
		if (v[ip].inst == "gtrr") rez[v[ip].c] = rez[v[ip].a] > rez[v[ip].b];
		if (v[ip].inst == "eqir") rez[v[ip].c] = v[ip].a == rez[v[ip].b];
		if (v[ip].inst == "eqri") rez[v[ip].c] = rez[v[ip].a] == v[ip].b;
		if (v[ip].inst == "eqrr") rez[v[ip].c] = rez[v[ip].a] == rez[v[ip].b];

		ip = rez[il];
		ip++;
	}

    cout << rez[0];

	return 0;
}
