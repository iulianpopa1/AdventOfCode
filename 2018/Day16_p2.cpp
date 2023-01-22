#include <bits/stdc++.h>

using namespace std;

ifstream in("i1.txt");// INPUT PARSAT FARA OPCODES (Partea 2 din input)
ifstream in2("i2.txt");



int main()
{
    vector<set<int>> opss(16);
    //for(int i = 0; i < 16; ++i)
       // for(int j = 0; j < 16; ++j)
           // opss[i].push_back(j);
    for(int i = 0; i < 16; ++i)
        for(int j = 0; j < 16; ++j)
            opss[i].insert(j);




    while(!in.eof())
    {
        vector<int>before(4);
        vector<int>after(4);
        int op, a, b, c;
        in >> before[0] >> before[1] >> before[2] >> before[3];
        in >> op >> a >> b >> c;
        in >> after[0] >> after[1] >> after[2] >> after[3];

        vector<vector<int>> rez;
        for(int i = 0; i < 16; ++i)
            rez.push_back(before);

        rez[0][c] = before[a] + before[b];
		rez[1][c] = before[a] + b;
		rez[2][c] = before[a] * before[b];
		rez[3][c] = before[a] * b;
		rez[4][c] = before[a] & before[b];
		rez[5][c] = before[a] & b;
		rez[6][c] = before[a] | before[b];
		rez[7][c] = before[a] | b;
		rez[8][c] = before[a];
		rez[9][c] = a;
		rez[10][c] = (a > before[b]);
		rez[11][c] = (before[a] > b);
		rez[12][c] = (before[a] > before[b]);
		rez[13][c] = (a == before[b]);
		rez[14][c] = (before[a] == b);
		rez[15][c] = (before[a] == before[b]);

        for(int i = 0; i < 16; ++i)
            if(rez[i] != after)
                opss[op].erase(i);

    }

    for(int f = 0; f < 25; ++f)
        for(int i = 0; i < 16; ++i)
            if(opss[i].size() == 1)
                for(int j = 0; j < 16; ++j)
                    if(i != j)
                        opss[j].erase(*(opss[i].begin()));
    vector<int> r_op;
    vector<int>before(4, 0);

    for(int i = 0; i < 16; ++i){
        for(auto it:opss[i])
            r_op.push_back(it);
    }

    for(auto it : r_op)
        cout << it << ' ';
    cout << endl;

    while(!in2.eof())
    {
        int op, a, b, c;
        in2 >> op >> a >> b >> c;

        vector<vector<int>> rez;
        for(int i = 0; i < 16; ++i)
            rez.push_back(before);

        rez[0][c] = before[a] + before[b];
		rez[1][c] = before[a] + b;
		rez[2][c] = before[a] * before[b];
		rez[3][c] = before[a] * b;
		rez[4][c] = before[a] & before[b];
		rez[5][c] = before[a] & b;
		rez[6][c] = before[a] | before[b];
		rez[7][c] = before[a] | b;
		rez[8][c] = before[a];
		rez[9][c] = a;
		rez[10][c] = (a > before[b]);
		rez[11][c] = (before[a] > b);
		rez[12][c] = (before[a] > before[b]);
		rez[13][c] = (a == before[b]);
		rez[14][c] = (before[a] == b);
		rez[15][c] = (before[a] == before[b]);

        before = rez[r_op[op]];
    }

    cout << before[0] - 1 << ' ' << before[1] - 1<< ' ' << before[2] << ' ' << before[3] <<endl;
    in.close();
    return 0;
}
