#include <bits/stdc++.h>

using namespace std;

ifstream in("input.txt");

int main()
{
    vector<string> v;
    string s;

    while(!in.eof())
    {
        in >> s;
        v.push_back(s);
    }

    for(auto it1 : v)
        for(auto it2 : v)
        {
            int dif = 0;
            auto a = it1.begin(), b = it2.begin();
            for(; a != it1.end(), b != it2.end(); ++a, ++b)
                if(*a != *b) dif++;
            if(dif == 1)
            {
                cout << it1 << ' ' << it2 << endl;
                cout << endl << "\nElimina litera care difera\n\n";
                return 0;
            }

        }
}
