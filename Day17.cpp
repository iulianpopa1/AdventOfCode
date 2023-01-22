#include <bits/stdc++.h>

using namespace std;

ifstream in("input_modif.txt");


void print(char mat[4000][4000]);
void spring(int x, int y, char mat[4000][4000]);

int minx1 = 9999, minx2 = 9999, miny1 = 9999, miny2 = 9999, minx, miny;
int maxx1 = 0, maxx2 = 0, maxy1 = 0, maxy2 = 0, maxx, maxy;
char mat[4000][4000];
//SAND = .
//CLAY = #
//STATIC WATER = ~
//NOT STATIC WATER = |

int main()
{
    for(int i = 0; i < 4000; ++i)
        for(int j = 0; j < 4000; ++j)
            mat[i][j] = '.';
    mat[0][500] = '+';

    while(!in.eof())
    {
        int x1, x2, y1, y2;
        char c1, c2;
        in >> c1;
        if(c1 == 'x')
        {
            in >> x1  >> c2 >> y1 >> y2;
            for(int i = y1; i <= y2; ++i)
            {
                mat[x1][i] = '#';
            }
            minx1=min(minx1, x1); miny1=min(miny1, y1); miny2 = min(miny2, y2);
            maxx1=max(maxx1, x1); maxy1=max(maxy1, y1); maxy2=max(maxy2, y2);
        }
        else
        {
            in >> y1  >> c2 >> x1 >> x2;
            for(int i = x1; i <= x2; ++i)
            {
                mat[i][y1] = '#';
            }
            minx1=min(minx1, x1); minx2=min(minx2, x2); miny1=min(miny1, y1);
            maxx1=max(maxx1, x1); maxx2=max(maxx2, x2); maxy1=max(maxy1, y1);
        }
    }
    minx = min(minx1, minx2);   miny = min(miny1, miny2);
    maxx = max(maxx1, maxx2);   maxy = max(maxy1, maxy2);

    //print(mat);



    bool found = false;
    int x = 500, y = 0;
    int ans = 0;
    //SAND = .
    //CLAY = #
    //STATIC WATER = ~
    //NOT STATIC WATER = |
    while(1)
    {
        if(found)
        {
            x = 500;
            y = 0;
            found = false;
        }
        while(mat[x][y + 1] == '.' && y <= maxy - 1)y++;

        if(y == maxy)
        {
            found = true;
            mat[x][y] = '|';
            ans++;
            continue;
        }
        else if(y < miny)
        {
            break;
        }
        if(mat[x - 1][y] == '.')
        {
            while(mat[x - 1][y] == '.' && (mat[x][y + 1] == '#' || mat[x][y + 1] == '~') )
                x--;
        }
        else if(mat[y + 1][x] == '.')
        {
            while(mat[x + 1][y] == '.' && (mat[x][y + 1] == '#' || mat[x][y + 1] == '~') )
                x++;
        }

        if(mat[x][y + 1] != '.')
        {
            found = true;
            if( mat[x][y + 1] == '|' || mat[x + 1][y] == '|' || mat[x - 1][y] == '|')
            {
                mat[x][y] = '|';

                int aux = x;
                while(mat[aux - 1][y] == '~')
                {
                    mat[aux - 1][y] = '|';
                    aux--;
                }
                aux = x;
                while(mat[aux + 1][y] == '~')
                {
                    mat[aux + 1][y] = '|';
                    aux++;
                }
            }
            else
                mat[x][y] = '~';
        ans++;
        }
    }
    //print(mat);
    cout << ans;

    int ans2 = 0;
    for(int i = 0; i < 4000; ++i)
        for(int j = 0; j < 4000; ++j)
			if(mat[i][j] == '~') ans2++;
    cout << endl << ans2;
    in.close();
    return 0;
}

void print(char mat[4000][4000])
{
    //cout << endl << minx1 << ' ' << minx2 << ' ' << miny1 << ' ' << miny2 << endl;
    //cout << endl << maxx1 << ' ' << maxx2 << ' ' << maxy1 << ' ' << maxy2 << endl;
    //cout << endl << minx << ' ' << miny << endl;
    //cout << endl << maxx << ' ' << maxy << endl;
    cout << endl;
    for(int i = 0; i <= maxy; ++i)
    {
        for(int j = min(minx, 500); j <= max(maxx, 500); ++j)
            cout << mat[j][i];
        cout << endl;
    }
    cout << endl;
}

