#include <bits/stdc++.h>

using namespace std;

ifstream in("input.txt");
//ofstream out("out.txt");

// STRUNG
//V[i] - toate elementele care depind de i
//vecfr[i] - nr de elemente de care depinde i

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


    for(auto i = 65; i <= 90; ++i)
    {
        sort(V[i].begin(), V[i].end());
    }

    vector<char>Q;
    vector<pair<int, char>>EV;
    int t = 0;
    char x;
    for(auto it : order)
        if(vecfr[it] == 0)
            Q.push_back(it);

    while(Q.size() != 0)
    {
        auto mn = min_element(Q.begin(), Q.end());
        char x = *mn;
        Q.erase(mn);
        cout << "Starting " << x << " at " << t << endl;
        EV.push_back({t + 61 + x - 'A', x});
    }

    while(Q.size() != 0 || EV.size() != 0)
    {
        pair<int, char> paux = *EV.begin();
        for(auto it : EV)
        {
            if(it.first < paux.first)
            {
                paux.first = it.first;
                paux.second = it.second;
            }
        }
        t = paux.first;
        x = paux.second;
        //cout << paux.first << ' ' << (char)paux.second << endl;
        cout << t << ' ' << (char)x << endl;

        bool found = true;
        while(found){
            auto dit = find(EV.begin(),EV.end(), paux);
            found = false;
            if(dit != EV.end())
                EV.erase(dit), found = true;
            }

        for(auto ity : V[paux.second])
        {
                vecfr[ity] -= 1;
                if(vecfr[ity] == 0)
                    Q.push_back(ity);
        }

        while(Q.size() != 0)
        {
            auto mn = min_element(Q.begin(), Q.end());
            char x = *mn;
            Q.erase(mn);
            cout << x << "  start -> " << t << endl;
            EV.push_back({t + 61 + x - 'A', x});
        }
    }
    cout << "\n\nSe ia prima valoare din ultima pereche afisata\n";

    in.close();
    return 0;
}
