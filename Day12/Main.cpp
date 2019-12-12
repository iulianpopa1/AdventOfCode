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

class Planet
{
public:
	ll x, y, z;
	ll vel_x, vel_y, vel_z;

	Planet(int x, int y, int z, int vel_x, int vel_y, int vel_z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->vel_x = vel_x;
		this->vel_y = vel_y;
		this->vel_z = vel_z;
	}

	bool operator == (Planet other) const
	{
		if (x != other.x) return false;
		if (y != other.y) return false;
		if (z != other.z) return false;
		if (vel_x != other.vel_x) return false;
		if (vel_y != other.vel_y) return false;
		if (vel_z != other.vel_z) return false;
		return true;
	}

	void Print_info()
	{
		cout << x << ' ' << y << ' ' << z << ' ' << vel_x << ' ' << vel_y << ' ' << vel_z << endl;
	}
};

void Uplade_velocity(vector<Planet> &planets)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = i; j < 4; ++j)
		{
			if (planets[i].x < planets[j].x)
			{
				planets[i].vel_x += 1;
				planets[j].vel_x -= 1;
			}
			else if (planets[i].x > planets[j].x)
			{
				planets[i].vel_x -= 1;
				planets[j].vel_x += 1;
			}
			if (planets[i].y < planets[j].y)
			{
				planets[i].vel_y += 1;
				planets[j].vel_y -= 1;
			}
			else if (planets[i].y > planets[j].y)
			{
				planets[i].vel_y -= 1;
				planets[j].vel_y += 1;
			}
			if (planets[i].z < planets[j].z)
			{
				planets[i].vel_z += 1;
				planets[j].vel_z -= 1;
			}
			else if (planets[i].z > planets[j].z)
			{
				planets[i].vel_z -= 1;
				planets[j].vel_z += 1;
			}
		}
	}
}

void Upldate_position(vector<Planet>& planets)
{
	for (auto & it : planets)
	{
		it.x += it.vel_x;
		it.y += it.vel_y;
		it.z += it.vel_z;
	}
}

void Print_planets(vector<Planet>planets)
{
	for (auto it : planets)
	{
		it.Print_info();
	}
	cout << endl;
}

void Make_step(vector<Planet>& planets)
{
	Uplade_velocity(planets);
	Upldate_position(planets);
}

ll Calc_P_Energy(Planet planet)
{
	return abs(planet.x) + abs(planet.y) + abs(planet.z);
}

ll Calc_K_Energy(Planet planet)
{
	return abs(planet.vel_x) + abs(planet.vel_y) + abs(planet.vel_z);
}

ll Calculate_energy(vector<Planet>& planets)
{
	ll total_energy = 0;
	for (auto it : planets)
	{
		total_energy += Calc_P_Energy(it) * Calc_K_Energy(it);
	}

	return total_energy;
}

bool x_repeat(vector<Planet> planets, vector<Planet> initial)
{
	bool repeats = true;
	for (int i = 0; i < 4; ++i)
	{
		if (planets[i].x != initial[i].x)
		{
			repeats = false;
			break;
		}
	}
	return repeats;
}

bool y_repeat(vector<Planet> planets, vector<Planet> initial)
{
	bool repeats = true;
	for (int i = 0; i < 4; ++i)
	{
		if (planets[i].y != initial[i].y)
		{
			repeats = false;
			break;
		}
	}
	return repeats;
}

bool z_repeat(vector<Planet> planets, vector<Planet> initial)
{
	bool repeats = true;
	for (int i = 0; i < 4; ++i)
	{
		if (planets[i].z != initial[i].z)
		{
			repeats = false;
			break;
		}
	}
	return repeats;
}

ll GCD(ll a, ll b)
{
	if (b == 0)
		return a;
	return GCD(b, a % b);
}

ll LCM(ll x, ll y, ll z)
{
	ll ans;
	ans = (y * x) / (GCD(y, x));
	ans = (ans * z) / (GCD(ans, z));
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);

	vector<Planet> planets, initial;

	while (!in.eof())
	{
		ll x, y, z;
		in >> x >> y >> z;
		Planet aux = Planet(x, y, z, 0, 0, 0);
		planets.push_back(aux);
	}

	initial = planets;

	ll step = 0, x_rep, y_rep, z_rep;
	bool x_found = false, y_found = false, z_found = false;

	while (++step)
	{
		Make_step(planets);

		if (step == 1000)
		{
			cout << "Part1 : " << Calculate_energy(planets) << endl;
		}

		if(x_found == false)
			if (x_found = x_repeat(planets, initial))
				x_rep = step + 1;
						
		if(y_found == false)
			if (y_found = y_repeat(planets, initial))
				y_rep = step + 1;

		if(z_found == false)
			if (z_found = z_repeat(planets, initial))
				z_rep = step + 1;

		if (x_found && y_found && z_found)
			break;
	}
	cout << "X repeats at step " << x_rep << endl;
	cout << "Y repeats at step " << y_rep << endl;
	cout << "Z repeats at step " << z_rep << endl;
	cout << "Part2 : " << LCM(x_rep, y_rep, z_rep) << endl;
	
}