#include <bits/stdc++.h>

using namespace std;

ifstream in("input.txt");
//ofstream out("out.txt");

int vecfr[100];
int main()
{
    vector<vector<char>> V(100);
    vector<char> order;
    while(!in.eof())
    {
        char s1, s2;
        string trash;
        in >> trash >> s1 >> trash  >> trash >> trash >> trash >> trash >> s2 >> trash >> trash;

        V[(int)s1].push_back(s2);

        auto fit = find(order.begin(), order.end(), s1);
        if(fit == order.end())
            order.push_back(s1);

        vecfr[(int)s2]++;
    }
    vector<char>Q;
    for(auto it : order)
        if(vecfr[it] == 0)
            Q.push_back(it);

    string ans = "";
    while(Q.size() != 0)
    {
        auto mn = min_element(Q.begin(), Q.end());
        char x = *mn;
        Q.erase(mn);
        ans += x;
            for(auto ity : V[x])
            {
                vecfr[ity] -= 1;
                if(vecfr[ity] == 0)
                    Q.push_back(ity);
            }
    }
    cout << ans << endl;






    in.close();
    return 0;
}
