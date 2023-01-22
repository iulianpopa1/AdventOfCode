#include <bits/stdc++.h>

using namespace std;

ifstream in("i1.txt");// INPUT PARSAT FARA OPCODES (Partea 2 din input)

int main()
{
    int ans = 0;
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

        int aux = 0;

        for(int i = 0; i < 16; ++i)
            if(rez[i] == after)
                aux++;

        if(aux >= 3)
            ans++;
    }

    cout << ans - 1;

    in.close();
    return 0;
}
