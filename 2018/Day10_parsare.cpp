#include <bits/stdc++.h>

using namespace std;

ifstream in("input_orig.txt");
ofstream out("input.txt");

int main()
{
    while(!in.eof())
    {
        string line;
        getline(in, line);
        cout << line << endl;
        for(auto is : line)
            {

            if( (char)is == '-'){ out << is; continue;}
            if( (char)is < '0' || (char)is > '9' )
                out << ' ';
            else
                out << is;
                }
        out << endl;
    }

    in.close();
    return 0;
}
