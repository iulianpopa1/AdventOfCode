#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define depth  4002

ll xt = 5, yt = 746;
ll cave[depth + 1][depth + 1];
int mod = 20183;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

//0 - rocky   .
//1 - wet     =
//2 - narrow  |

bool ok(ll cavesq, ll tool)
{
    if(cavesq == 0 && ( tool == 0 || tool == 1 ))return true;
    if(cavesq == 1 && ( tool == 1 || tool == 2 ))return true;
    if(cavesq == 2 && ( tool == 0 || tool == 2 ))return true;
    return false;
}

int main()
{
    cave[0][0] = 0;
    for(int i = 1; i <= 2000; ++i)
    {
        cave [0][i] = (i * 48271 + depth) % mod; //x == 0; y != 0
        cave [i][0] = (i * 16807 + depth) % mod; //x != 0; y == 0
    }
    for(int i = 1; i <= 2000; ++i)
        for(int j = 1; j <= 2000; ++j)
        {
            cave[i][j] = ( (cave[i - 1][j] % mod) * (cave[i][j - 1] % mod) ) % mod;
            cave[i][j] = (cave[i][j] + depth) % mod;
        }
    cave[xt][yt] = 0;

    int risk = 0;                       //PART 1
    for(int i = 0; i <= xt; ++i)        //PART 1
        for(int j = 0; j <= yt; ++j)    //PART 1
            risk += cave[i][j] % 3;     //PART 1
    cout << endl << risk << endl;       //PART 1


    set< tuple< ll, ll , ll > >seen;
    priority_queue< tuple< ll, ll , ll, ll > >Q;
    Q.push(make_tuple(0,0,0,0));

    while(!Q.empty())
    {
        auto tpl = Q.top(); Q.pop();

        ll dist, x, y, tool;
        dist = get<0>(tpl) * (-1);
        x = get<1>(tpl);
        y = get<2>(tpl);
        tool = get<3>(tpl);

        if(x == xt && y == yt && tool == 0)
        {
            cout << dist << endl;
            break;
        }
        if(seen.count(make_tuple(x, y, tool)) == 1) continue;
        seen.insert(make_tuple(x, y, tool));

        for(long long atool = 0; atool < 3; ++atool)
            if(ok(cave[x][y] % 3, atool))
                Q.push(make_tuple( -(dist + 7), x, y, atool));

        for(long long ad = 0; ad < 4; ++ad)
        {
            long long ax = x + dx[ad];
            long long ay = y + dy[ad];
            if(!(0 <= ax && ax < 2000 && 0 <= ay && ay < 2000)) continue;
            if(ok(cave[ax][ay] % 3, tool))
                Q.push(make_tuple( -(dist + 1), ax, ay, tool));
        }
    }

    return 0;
}
