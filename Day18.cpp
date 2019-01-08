#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ifstream in("input.txt");

int dx[8] = { -1, -1, -1, 0,  0,  1, 1, 1 };
int dy[8] = { -1,  0,  1, -1, 1, -1, 0, 1 };

int main()
{
    vector< string > v;
    while(!in.eof())
    {
        string s;
        getline(in, s);
        v.push_back(s);
    }

    int X = v.size();     // R
    int Y = v[0].size();  // C

    ll T = 1000000000;

    map< vector< string >, ll > m;

    for(ll t = 0; t < T; ++t)
    {
        vector<string> v2(X, string(Y, ' '));
        for(ll x = 0; x < X; ++x)
            for(ll y = 0; y < Y; ++y)
            {
                ll tree = 0, lumber = 0;

                for (int i = 0; i < 8; i++)
                {
                    ll xx = x + dx[i];
                    ll yy = y + dy[i];
                    if(!(0 <= xx && xx < X && 0 <= yy && yy < Y)) { continue; }
                    if(v[xx][yy] == '|') tree++;
                    if(v[xx][yy] == '#') lumber++;
                }

                if(v[x][y] == '.')
                    v2[x][y] = (tree >= 3 ? '|' : '.');
                else if(v[x][y] == '|')
                  v2[x][y] = (lumber >= 3 ? '#' : '|');
                else
                  v2[x][y] = (lumber >= 1 && tree >= 1 ? '#' : '.');

            }
    v = v2;
    if(m.count(v) == 1)
    {
        ll skip = (T - t) / (t - m[v]);
        t += skip * (t - m[v]);
    }
    else
        m[v] = t;


        ll tree = 0;
        ll lumber = 0;
        for(ll x = 0; x < X; ++x)
        {
            for(ll y = 0; y < Y; ++y)
            {
                if(v[x][y] == '|') { tree++; }
                if(v[x][y] == '#') { lumber++; }
            }
        }
    if(t == 9 || t == T - 1)
        cout << tree * lumber << endl;
    }

}
