#include <bits/stdc++.h>
#include <string>

using namespace std;

ifstream in("input_org.txt");
ofstream out("mod_input.txt");
int mat[2000][2000];

int main()
{
    //PARSARE
    while(!in.eof())
    {
        string line;
        getline(in, line);
        cout << line << endl;
        for(auto is : line)
            if( (char)is < '0' || (char)is > '9' )
                out << ' ';
            else
                out << is;
        out << endl;
    }

    in.close();
    out.close();


    in.close();
    return 0;
}
