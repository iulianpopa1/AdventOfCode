#include <bits/stdc++.h>

using namespace std;

ifstream in("input.txt");

int main()
{
    int p2 = 0, p3 = 0;

    string s;

    while(!in.eof())
    {
        in >> s;
        int app[28] = {0};
        for(auto it : s)
            app[int(it) - 97] += 1;

        for(int i = 0; i <= 26; ++i)
            if(app[i] == 2 )
            {
                p2++;
                break;
            }
        for(int i = 0; i <= 26; ++i)
            if(app[i] == 3 )
            {
                p3++;
                break;
            }
    }
    cout << p2 * p3;
}
