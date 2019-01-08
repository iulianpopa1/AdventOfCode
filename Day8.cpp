#include <bits/stdc++.h>
using namespace std;
ifstream in("input.txt");

int solve(vector<int> &numbers, int &index)
{
    if(index >= numbers.size()) return 0;

    const int nChild = numbers[index], nMData = numbers[++index];
    vector<int> childrenSum;
    int sum = 0;


    for(int i = 0; i < nChild; i++)
        childrenSum.push_back(solve( numbers, ++index) );


    for(auto it : childrenSum)      //PART 1
        sum += it;                  //PART 1
    for(int j = 0; j < nMData; j++) //PART 1
        sum += numbers[++index];    //PART 1
    /*
    if(nChild == 0)                              //PART 2
        for(int j = 0; j < nMData; j++)          //PART 2
            sum += numbers[++index];             //PART 2
    else                                         //PART 2
        for(int j = 0; j < nMData; j++) {        //PART 2
            int metadata = numbers[++index];     //PART 2
            if(metadata > nChild) continue;      //PART 2
            sum += childrenSum[metadata - 1];    //PART 2
        }
    */

    return sum;
}


int main()
{
    vector<int> numbers;
    int n;
    while(!in.eof())
    {
        in >> n;
        numbers.push_back(n);
    }
    int index = 0;
    cout << solve(numbers, index);
    in.close();
    return 0;
}

