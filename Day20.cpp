#include <bits/stdc++.h>

using namespace std;

#define N 1000
//           U  R  D  L
int dx[] = {-1, 0, 1, 0};
int dy[] = {0 , 1, 0, -1};
int m[N][N];

int dir(char c)
{
    if (c == 'N') // U
        return 0;
    if (c == 'E') // R
        return 1;
    if (c == 'S') // D
        return 2;
    if (c == 'W') // L
        return 3;
    return -1;
}

void move(string s, int x, int y)
{
    int i = 0, j;
    while(i < s.size())
    {
        if(s[i] == '(')
            break;
        //Next x, y
        int aux_x = x + dx[dir(s[i])];
        int aux_y = y + dy[dir(s[i])];
        m[aux_x][aux_y] = min(m[aux_x][aux_y], m[x][y] + 1);
        //Updaet x, y
        x = aux_x;
        y = aux_y;
        i++;
    }
    if(i == s.size())
        return;
    int s_x = x, s_y = y;

    //Perechea parantezei
    int par = 1;
    j = i + 1;
    while(par != 0)
    {
        if(s[j] == '(')
            par++;
        else
            if(s[j] == ')')
                par--;
        j++;
    }
    j--;
    //Sir paranteze
    string s2 = s.substr(i + 1, j - i - 1);
    //cout << endl << s2 << endl;
    //system("pause");

    while(1)
    {
        par = 0;
        int k = 0;
        while(k < s2.size())
        {
            if(s2[k] == '(')
                par++;
            else
                if(s2[k] == ')')
                    par--;
                else
                    if(par == 0 && s2[k] == '|')
                        break;
            k++;
        }

        string s3 = s2.substr(0, k);
        move(s3, x, y);

        if(k == s2.size())
            break;
        else
            s2 = s2.substr(k + 1);
    }

    if(j < s.size())
    {
        string s4 = s.substr(j + 1);
        move(s4, s_x, s_y);
    }
}

ifstream in("input.txt");

int main()
{
    string ss; in >> ss;
    //cout << ss << endl;
    ss.erase(ss.begin()); ss.erase(--ss.end());
    //cout << ss << endl;

    for(int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j){
            m[i][j] = 9999;
        }
    m[N/2][N/2] = 0;

    move(ss, N/2, N/2);

    int ans1 = 0, ans2 = 0;

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (m[i][j] != 9999)
            {
                ans1 = max(ans1, m[i][j]);
                if(m[i][j] >= 1000)
                    ans2++;
            }
        }
    }
    cout << ans1 << endl << ans2 << endl;


    in.close();
    return 0;
}
    /*
    stack<int>Sp;
    vector< pair<int, int> > aux_vec;
    vector< vector< pair<int, int> > >ops;


    for(int i = 0; i < ss.size(); ++i)
    {
        if(ss[i] == '(')Sp.push(i);
        if(ss[i] == ')')
        {
            pair<int, int> pp;
            pp.first = Sp.top();
            pp.second = i;

            Sp.pop();

            aux_vec.push_back(pp);

            if(Sp.size() == 0)
            {
                ops.push_back(aux_vec);
                aux_vec.clear();
            }
        }
    }*/

    /*for(auto it : ops){
        for(auto itt: it)
            cout << itt.first << ' ' << itt.second << endl;
        cout << endl << endl << endl;
    }*/
