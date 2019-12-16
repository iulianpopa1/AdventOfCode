/**/
#include <iostream>
#include <fstream>
#include <string> //stoi, atoi
#include <algorithm>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <math.h>

using namespace std;
using ll = long long;

ifstream in("P_input.txt");

map<string, map<string, ll>> components;
map<string, ll> extra;
map<string, ll> per_combination;


ll ores_for_element(string element, ll quantity)
{
    ll ores = 0;

    if(element == "ORE")
        return quantity;

    if(extra[element] > quantity)
    {
        extra[element] -= quantity;
        quantity = 0;
    }
    else
    {
        quantity -= extra[element];
        extra[element] = 0;
    }

    ll multiplyer = quantity / per_combination[element];
    if(quantity % per_combination[element])
    {
        multiplyer++;
    }

    for(auto it : components[element])
    {
        ores += ores_for_element(it.first, it.second * multiplyer);
    }

    extra[element] += per_combination[element] * multiplyer - quantity;

    return ores;
}


int main()
{
	ios::sync_with_stdio(false);
    map<string, ll> aux_components;

	while (!in.eof())
	{
		ll quantity;
        string chemical;
        in >> quantity >> chemical;
        if(quantity == -1 && chemical == "=>")
        {
            in >> quantity >> chemical;
            per_combination[chemical] = quantity;
            components[chemical] = aux_components;
            aux_components.clear();
        }
        else
        {
            aux_components[chemical] = quantity;
        }
	}

	cout << "Part1: " <<  ores_for_element("FUEL", 1) << endl;
    extra.clear();
    //Part2
	ll input = 1000000000000;
	ll left = 0, right = input;

    while (left + 1 < right)
    {
		ll mid = (left + right )/ 2;
		if (ores_for_element("FUEL", mid) <= input)
		{
			left = mid;
		}
		else
		{
			right = mid;
		}
		extra.clear();
	}
	cout << "Part2: " << left << endl;
}
