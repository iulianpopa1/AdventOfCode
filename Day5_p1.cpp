#include <bits/stdc++.h>

using namespace std;

ifstream in("input.txt");
//ofstream out("out.txt");
bool ver(char a, char b)
{
    if(isupper(a))
    {
        if(tolower(a) == b)
            return true;
    }
    else
        if(toupper(a) == b)
            return true;
    return false;
}

string dels(string s)
{
    string aux = s;
    for(int i = 1; i < aux.size(); ++i)
    {
        if( ver(*(aux.begin() + (i - 1)), *(aux.begin() + i) ))
            {
                aux.erase(aux.begin() + i);
                aux.erase(aux.begin() + (i - 1));
                return aux;
            }
    }
    return s;
}

int main()
{
    string s;
    in >> s;
    string SC = s;
    while(SC != dels(SC))
    {
        SC = dels(SC);
    }

    cout << SC.size() << endl;
    in.close();
    return 0;
}
