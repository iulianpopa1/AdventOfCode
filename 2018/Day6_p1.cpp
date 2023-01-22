#include <bits/stdc++.h>

using namespace std;

ifstream in("input.txt");
//ofstream out("out.txt");
// abs(x1 - x2) + abs (y1 - y2);

int mdist(pair<int, int> A, pair<int, int> B){
    return abs(A.first - B.first) + abs(A.second - B.second);
}

vector<pair<int, int>> points;
pair<int, int> mat[750][750];
int main(){
    while(!in.eof()){
        int x, y; char c;
        in >> x  >> c >> y;
        points.push_back({x, y});
    }

    map<int, int> cnt;
    for(int i = -1000; i < 1000; i++){
        for(int j = -1000; j < 1000; j++){
            int mindist = 99999, minpct;
            bool found = true;
            for(int k = 0; k < points.size(); k++){
                int cdist = abs(points[k].first - i) + abs(points[k].second -j);
                if (cdist < mindist){
                    mindist = cdist;
                    minpct = k;
                    found = true;
                }else{
                    if(cdist == mindist)
                        found = false;
                }
            }
            if(found)cnt[minpct]++;
        }
    }
    vector<pair<int, int>>ans;
    for(auto it : cnt){
        ans.push_back({it.second, it.first});
    }
    sort(ans.begin(), ans.end());
    for(auto it : ans)
        if(it.first < 10000)
            cout << it.first << ' ' << it.second << endl;
    cout << "\n\nSe ia prima valoare din ultima pereche afisata\n";

    in.close();
    return 0;
}
