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
    int ans = 0;
    for(int i = -2000; i < 2000; i++){
        for(int j = -2000; j < 2000; j++){
            int totDist = 0;
            for(int k = 0; k < points.size(); k++) {
                int curDist = abs(points[k].first - i) + abs(points[k].second -j);
                totDist += curDist;
            }
            if(totDist < 10000) ans++;
        }
    }
    cout << ans << endl;
    in.close();
    return 0;
}
