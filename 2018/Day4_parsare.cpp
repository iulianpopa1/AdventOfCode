#include <bits/stdc++.h>

using namespace std;

ifstream in("input_original.txt");
ofstream out("input.txt");

int main()
{
    while(!in.eof())
    {
        string line;
        getline(in, line);
        cout << line << endl;
        for(auto is : line)
            if( isdigit((char)is) || isalpha((char)is)  )
                out << is;
            else
                out << ' ';
        out << endl;
    }

    in.close();
    return 0;
}
