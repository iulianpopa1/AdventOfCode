#include <bits/stdc++.h>

using namespace std;

ifstream in("input.txt");
struct format
{
    int m, d, hh, mm;
    string st;

    void print(){
        cout << m << ' ' << d << ' ' << hh << ' ' << mm << ' ' << st << endl;
    }
};

bool sortaux(const format &f1, const format &f2)
{
    if(f1.m != f2.m) return (f1.m < f2.m);
    if(f1.d != f2.d) return (f1.d < f2.d);
    if(f1.hh != f2.hh) return (f1.hh < f2.hh);
    if(f1.mm != f2.mm) return (f1.mm < f2.mm);
}


vector<int> intersection(vector<int> &v1, vector<int> &v2)
{

    vector<int> v3;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3));

    return v3;
}


vector<struct format> data;
int main()
{
    while(!in.eof())
    {
        struct format aux;
        int y;
        in >> y >> aux.m >> aux.d >> aux.hh >> aux.mm;
        getline(in, aux.st);
        //aux.print();
        data.push_back(aux);
    }
    sort(data.begin(), data.end(), sortaux);
    //for(auto itt : data)
        //itt.print();
    unordered_map<int, vector< vector<int> > > mapids;
            // id , vector de timp [f, w]

    int id = 0;
    int sleep = -1;
    int wake = -1;

    for(auto itt : data)
    {

        if(sleep != -1 && wake != -1){
            vector<int> auv;
            for(int i = sleep; i < wake; ++ i)
                auv.push_back(i);
            auto itmap = mapids.find(id);
            if(itmap != mapids.end())
            {
                itmap->second.push_back(auv);
            }
            else
            mapids[id].push_back(auv);
            sleep = -1;
            wake = -1;
        }
        if(itt.st[2] == 'G'){
        id = 0;
        id = itt.st[9] - '0';
        if(isdigit(itt.st[10])) id = id * 10 + (itt.st[10] - '0');
        if(isdigit(itt.st[11])) id = id * 10 + (itt.st[11] - '0');
        if(isdigit(itt.st[12])) id = id * 10 + (itt.st[12] - '0');
        if(isdigit(itt.st[13])) id = id * 10 + (itt.st[13] - '0');
        }
        if(itt.st[2] == 'f') sleep = itt.mm;
        if(itt.st[2] == 'w') wake = itt.mm;
    }


    for(auto itk : mapids)
    {
    int fr[70] =  {0};
        for(auto itkk : itk.second)
            for(auto ittkj : itkk )
                fr[ittkj]++;

        int maxfr = 0, maxidd = 0;
        for(int i = 0; i <= 66; ++i)
            if(maxfr < fr[i]) maxfr = fr[i], maxidd = i;
         cout <<itk.first << ' ' << maxfr << ' '  << maxidd << endl;
    }
    //cout << "\nPART 1: \n\n";


    cout << "\nPART 2: \n\n";
    cout << "Se cauta max de pe coloana 2\n";
    cout << "De pe linia lui max se inmulteste campul 1 si 3 (id si minut)\n";
    cout << "(2137 * 50)\n\n";

    in.close();
    return 0;
}
