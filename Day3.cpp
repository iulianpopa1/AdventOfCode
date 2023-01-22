#include <bits/stdc++.h>
#include <string>

using namespace std;

ifstream in("mod_input.txt");
//ofstream out("out.txt");
int mat[2000][2000];

int main()
{
    while(!in.eof())
    {
        int id, x, y, w, h;
        in >> id >> x >> y >> w >> h;
        //cout << id << ' ' << x << ' ' << y << ' ' << w << ' ' << h << endl;
        for(int i = 0; i < w; ++i)
            for(int j = 0; j < h; ++j)
                mat[x + i][y + j] += 1;
    }
    in.clear();
    in.seekg(0, ios::beg);
    while(!in.eof())
    {
        int id, x, y, w, h;
        in >> id >> x >> y >> w >> h;
        //cout << id << ' ' << x << ' ' << y << ' ' << w << ' ' << h << endl;
        bool ok = true;
        for(int i = 0; i < w; ++i)
            for(int j = 0; j < h; ++j)
                if(mat[x + i][y + j] > 1)
                    ok = false;
        if(ok) cout << "\nP2 : " << id << endl;
    }


    int ans = 0;

	for (int i = 0; i <= 1999; ++i)
		for (int j = 0; j <= 1999; ++j)
			if (mat[i][j] >= 2) ans++;
    cout << "\nP1 : " << ans;






    in.close();
    return 0;
}
