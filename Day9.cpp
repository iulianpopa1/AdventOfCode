#include<bits/stdc++.h>

using namespace std;
list<int> m;
list<int>::iterator prev(list<int>::iterator it)
{
    if(it == m.begin())
        return m.end();
    return --it;
}
list<int>::iterator next(list<int>::iterator it)
{
    if(it == m.end())
        return m.begin();
    return ++it;
}

int main() {
    //mrbl = variabila din input
    int players = 441, mrbl = 71032;
    vector<long long> p (players + 5);

    auto curr = m.begin();

    for (int i = 1; i < mrbl; ++i) {
        if (i % 23 == 0) {
            curr = prev(prev(prev(prev(prev(prev(prev(curr)))))));
            p[i % players] += i + *curr;
            curr = m.erase(curr);
        } else {
            curr = m.insert(next(next(curr)), i);
        }
    }
    cout << *max_element(p.begin(), p.end()) << '\n';
    return 0;
}

