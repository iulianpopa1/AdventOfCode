#include <bits/stdc++.h>

using namespace std;

ifstream in("input_orig.txt");
ofstream out("i2.txt");

int main()
{
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
    cout << "\n SA SE SPARGA INPUT_MODIF IN 2, PRIMA PARTE PUSA IN 'i1'\n";
    cout << "iar cea de-a doua in 'i2'!";
    system("pause");
    in.close();
    return 0;
}
