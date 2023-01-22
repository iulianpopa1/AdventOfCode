#include <bits/stdc++.h>

using namespace std;

ifstream in("input.txt");
//ofstream out("out.txt");

int switches[3] = {'L', 'F', 'R'};

string track[151];


struct cart
{
    int x, y, swt;
    char dir;

    void mov()
    {
        bool md = false;
        if(dir == '^' && md == false)
        {
            if(track[x][y] == '|' && md == false)
            {
                x -= 1;md = true;
            }
            else if(track[x][y] == '/' && md == false)
            {
                y += 1;
                dir = '>';md = true;
            }
            else if(track[x][y] == '\\' && md == false)
            {
                y -= 1;
                dir = '<';md = true;
            }
            else if(track[x][y] == '+' && md == false)
            {

                if(swt == 0 && md == false) // L
                {
                    y -= 1;
                    dir = '<';
                    swt++;
                    md = true;
                }
                if(swt == 1 && md == false) // F
                {
                    x -= 1;
                    swt++;
                    md = true;
                }
                if(swt == 2 && md == false) // R
                {
                    y += 1;
                    dir = '>';
                    swt = 0;
                    md = true;
                }
            }
        }

        if(dir == 'v' && md == false)
        {
            if(track[x][y] == '|' && md == false)
            {
                x += 1;md = true;
            }
            else if(track[x][y] == '/' && md == false)
            {
                y -= 1;
                dir = '<';md = true;
            }
            else if(track[x][y] == '\\' && md == false)
            {
                y += 1;
                dir = '>';md = true;
            }
            else if(track[x][y] == '+' && md == false)
            {
                if(swt == 0 && md == false) // L
                {
                    y += 1;
                    dir = '>';
                    swt++;
                    md = true;
                }
                if(swt == 1 && md == false) // F
                {
                    x += 1;
                    swt++;
                    md = true;
                }
                if(swt == 2 && md == false) // R
                {
                    y -= 1;
                    dir = '<';
                    swt = 0;
                    md = true;
                }
            }
        }

        if(dir == '<' && md == false)
        {
            if(track[x][y] == '-' && md == false)
            {
                y -= 1;md = true;
            }
            else if(track[x][y] == '/' && md == false)
            {
                x += 1;
                dir = 'v';md = true;
            }
            else if(track[x][y] == '\\' && md == false)
            {
                x -= 1;
                dir = '^';md = true;
            }
            else if(track[x][y] == '+' && md == false)
            {
                if(swt == 0 && md == false) // L
                {
                    x += 1;
                    dir = 'v';
                    swt++;
                    md = true;
                }
                else if(swt == 1 && md == false) // F
                {
                    y -= 1;
                    swt++;
                    md = true;
                }
                else if(swt == 2 && md == false) // R
                {
                    x -= 1;
                    dir = '^';
                    swt = 0;
                    md = true;
                }
            }
        }

        if(dir == '>' && md == false)
        {
            if(track[x][y] == '-' && md == false)
            {
                y += 1;md = true;
            }
            else if(track[x][y] == '/' && md == false)
            {
                x -= 1;
                dir = '^';md = true;
            }
            else if(track[x][y] == '\\' && md == false)
            {
                x += 1;
                dir = 'v';md = true;
            }
            else if(track[x][y] == '+' && md == false)
            {
                if(swt == 0 && md == false) // L
                {
                    x -= 1;
                    dir = '^';
                    swt++;
                    md = true;
                }
                else if(swt == 1 && md == false) // F
                {
                    y += 1;
                    swt++;
                    md = true;
                }
                else if(swt == 2 && md == false) // R
                {
                    x += 1;
                    dir = 'v';
                    swt = 0;
                    md = true;
                }
            }
        }

    }

};
bool comp(struct cart &a, struct cart &b)
{
    if(a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}


vector<cart> c;

int main()
{
    int i = 0;
    while(!in.eof())
    {
        getline(in, track[i++]);
    }

    //for(auto it : track)
       // cout << it << endl;

    for(int i = 0; i < 150; ++i)
        for(int j = 0; j < 150; ++j) // NU UITA SA MODIFICI FORURLE
        {
            if(track[i][j] == '^' ||  track[i][j] == 'v')
            {
                cart aux;
                aux.x = i;
                aux.y = j;
                aux.dir = track[i][j];
                aux.swt = 0;
                c.push_back(aux);
                track[i][j] = '|';
            }
            else if (track[i][j] == '<' || track[i][j] == '>' )
            {
                cart aux;
                aux.x = i;
                aux.y = j;
                aux.dir = track[i][j];
                aux.swt = 0;
                c.push_back(aux);
                track[i][j] = '-';
            }
        }

    //for(auto it : c)
       // cout << it.x << ' ' << it.y << ' ' << it.dir << endl;
    sort(c.begin(), c.end(), comp);

    cout << endl;
    for(auto it : c)
        cout << it.x << ' ' << it.y << ' ' << it.dir << endl;
    while(1)
    {
        sort(c.begin(), c.end(), comp);
        for (auto it = c.begin(); it != c.end(); ++it)
        {
            (*it).mov();
            for (auto itt = c.begin(); itt != c.end(); ++itt)
                if(itt != it)
                {
                    if(it->x == itt->x && it->y == itt->y)
                    {
                        cout << "DA " << it->y << ' ' << it->x << endl;
                        return 0;
                    }
                }
        }
        //cout << endl;
        //for(auto it : c)
           // cout << it.x << ' ' << it.y << ' ' << it.dir << endl;
    }




    in.close();
    return 0;
}


