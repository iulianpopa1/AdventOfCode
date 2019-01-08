#include <bits/stdc++.h>

using namespace std;

int sum[301][301];
int input = 4172;

int main() {

    int best_x, best_y, best_s, best = -999999;

    for(int y = 1; y <= 300; y++) {
        for(int x = 1; x <= 300; x++) {
            int rack_id = x + 10;
            int pow_lvl = rack_id * y;
            pow_lvl += input;
            pow_lvl *= rack_id;
            pow_lvl = (pow_lvl % 1000)/100;
            pow_lvl -= 5;
            sum[y][x] = pow_lvl + sum[y - 1][x] + sum[y][x - 1] - sum[y - 1][x - 1];
        }
    }
    //int s = 3;  // PART 1
    //for(int s = 1; s <= 300; s++) // PART 2
        for(int y = s; y <= 300; y++) {
            for(int x = s; x <= 300; x++) {
                int total = sum[y][x] - sum[y - s][x] - sum[y][x - s] + sum[y - s][x - s];
                if(total > best) {
                    best = total, best_x = x, best_y = y, best_s = s;
                }
            }
        }

    cout << '(' << best_x - best_s + 1 << ',' << best_y - best_s + 1 << ')' << ',' << best_s << endl;
    return 0;
}
