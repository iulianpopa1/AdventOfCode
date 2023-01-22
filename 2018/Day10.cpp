#include <bits/stdc++.h>

using namespace std;

typedef struct pnt
{
    int x, y, dx, dy;
}point;


ifstream in("input.txt");
ofstream out("out.txt");

int minx(vector<pair<int, int>>fs);
int miny(vector<pair<int, int>>fs);
int maxx(vector<pair<int, int>>fs);
int maxy(vector<pair<int, int>>fs);

vector <point> p(400);

vector<pair<int, int>> modif(vector<pair<int, int>> fs)
{
    for(int i = 0; i < fs.size(); i++)
    {
        fs[i].first += p[i].dx;
        fs[i].second += p[i].dy;
    }
    return fs;
}

void print_sol(vector<pair<int, int>> fs)
{
    for(int i = minx(fs) -1; i <= maxx(fs) + 1; i++)
    {
        for(int j = miny(fs) - 5; j <= maxy(fs) + 5; j++)
        {
            auto aux_pair = std::make_pair(i, j);
            if(find(fs.begin(), fs.end(), aux_pair) != fs.end())
                cout << '#';
            else cout << ' ';
        }
        cout << endl;
    }
}



int main()
{

    vector <pair<int, int>> fs;
    int i = 0;
    while(!in.eof())
    {
        int x, y, dx, dy;
        in >> x >> y >> dx >> dy;
        p[i].x = x;
        p[i].y = y;
        p[i].dx = dx;
        p[i].dy = dy;
        i++;
    }
    p.resize(i-1);

    for(auto it : p)
    {
        fs.push_back({it.x, it.y});
    }

    int zx = 1;
    int mmmx = 99999, mmmy= 99999;
    //while(maxx(fs) - minx(fs) > 100 || maxy(fs) - miny(fs) > 100)
    for(int kd = 1; kd <= 10500; ++kd)
    {
        //cout << kd << endl;
        fs = modif(fs);
        mmmx = min(mmmx, maxx(fs) - minx(fs));
        mmmy = min(mmmy, maxy(fs) - miny(fs));
        cout << kd << ' ' << mmmx << ' ' << mmmy << endl;
        if(mmmx == 61 && mmmy == 9)
        {
            print_sol(fs);
            system("pause");
            system("cls");
        }

        zx ++;
    }


    //61 9

    system("pause");

    in.close();
    return 0;
}


int minx(vector<pair<int, int>>fs)
{
    int m = 99999;
    for(auto it : fs)
    {
        m = min(m, it.first);
    }
    return m;
}
int miny(vector<pair<int, int>>fs)
{
    int m = 99999;
    for(auto it : fs)
    {
        m = min(m, it.second);
    }
    return m;
}
int maxx(vector<pair<int, int>>fs)
{
    int m = -99999;
    for(auto it : fs)
    {
        m = max(m, it.first);
    }
    return m;
}
int maxy(vector<pair<int, int>>fs)
{
    int m = -99999;
    for(auto it : fs)
    {
        m = max(m, it.second);
    }
    return m;
}
