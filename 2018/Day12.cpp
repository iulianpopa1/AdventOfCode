#include <bits/stdc++.h>

using namespace std;

ifstream in("input.txt");
ofstream out("out.txt");

unordered_map<string, char> forms;

char mdfy(int i, string s)
{
    string aux;
    aux += s[i-2];
    aux += s[i-1];
    aux += s[i];
    aux += s[i+1];
    aux += s[i+2];

    return forms[aux];
}

int main()
{
    string init_s, trash, s;
    char c;
    in >> trash >> trash >> init_s;
    init_s = "...................." + init_s + "....................................................................";
    while(!in.eof())
    {
        in >> s >> trash >> c;
        forms[s] = c;
    }

    cout << init_s << endl;

    s = init_s;
    //int sum = 0;
    for(int kkw = 1; kkw <= 205; kkw++)
    {
        trash = s[0];
        trash += s[1];
        for(int i = 2; i < s.size() - 2; ++i)
        {
            trash += mdfy(i, s);
        }
        trash += s[s.size() - 2];
        trash += s[s.size() - 1];
        s = trash;
        s += ".........";
        out << trash << endl;
        int sum = 0;
        for(int i = 0; i < s.size(); ++i)
            if(s[i] == '#')
            {
                sum += i - kkw;
            }
        cout << kkw << ' ' << sum << endl;
    }


    in.close();
    return 0;
}
