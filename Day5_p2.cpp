#include <bits/stdc++.h>
using namespace std;


int react(string s) {
    deque<char> q;
    for (char c: s) {
        if (q.empty()) {
            q.push_back(c);
        } else {
            char last = q.back();
            if (abs(last - c) == abs('A'-'a')) {
                q.pop_back();
            } else {
                q.push_back(c);
            }
        }
    }
    return q.size();
}
ifstream in("input.txt");

int main() {
    string s;
    in >> s;
    int ans = 50000;
    for (int i = 0; i < 26; i++) {
        string new_s;
        for (char c: s) {
            if (!(c == 'a'+i || c == 'A'+i)) {
                new_s += c;
            }
        }
        ans = min(ans, react(new_s));
    }
    cout << ans << endl;
    return 0;
}
