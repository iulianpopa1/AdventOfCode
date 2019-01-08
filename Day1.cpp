#include <bits/stdc++.h>
using namespace std;

ifstream in("input.txt");

set<int> sset;
vector<int> vec;
int main()
{
    int s = 0, aux;
    while(!in.eof())
    {
        in >> aux;
        vec.push_back(aux);
        s += aux;
    }
    in.close();
    cout << s << endl;
    s = 0;
    //system("pause");
    while(1)
    {
        for(auto it : vec)
        {
            s += it;
            //cout << s << ' ';
            if(sset.find(s) != sset.end())
            {
                cout << s;
                return 0;
            }
            sset.insert(s);
        }
    }
    return 0;
}
