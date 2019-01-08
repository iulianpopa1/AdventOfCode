#include <bits/stdc++.h>

using namespace std;

vector<int>v;

int main()
{
    int input = 380621;
    v.push_back(3);
    v.push_back(7);

    int curr1 = 0;
    int curr2 = 1;

    for(int i = 1; i <= 100000000; ++i)
    {
        int sum = v[curr1] + v[curr2];
        if(sum >= 10)
        {
            v.push_back(sum / 10);
            v.push_back(sum % 10);
        }else
            v.push_back(sum);
        int c1 = v[curr1];
        int c2 = v[curr2];

        curr1 += c1 + 1;
        curr2 += c2 + 1;

        curr1 = curr1 % v.size();
        curr2 = curr2 % v.size();
    }

    string ans;                          //PART 1
    for(int i = 0; i < 10; ++i)          //PART 1
        ans += (v[input + i] + '0');     //PART 1
    cout << ans << endl;                 //PART 1

    for(int i = 1; i <= 100000000; ++i)
    {
        int sum = 0;
        for(int j = 0; j < 6; ++j)
        {
            sum *= 10;
            sum += v[i + j];
        }
        if(sum == input)
        {
            cout << i << endl;
            return 0;
        }
    }


    return 0;
}
