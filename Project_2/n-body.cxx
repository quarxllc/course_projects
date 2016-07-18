#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <math.h>


#define N = 100
#define G 35.5

using namespace std;

int const n = 3;
float const dt = 0.01;

struct planet{

	float x, y;
	float vx, vy;
	float fx, fy;
	float mass;
};

planet reset_force(planet p){

	p.fx = 0.0;
	p.fy = 0.0;

	return p;
}

planet update(planet p){

	p.vx += dt * p.fx / p.mass;
	p.vy += dt * p.fy / p.mass;
	p.x += dt * p.vx;
	p.y += dt * p.vy;

	return p;
}


planet add_force(planet a, planet b){

	float dx = b.x - a.x;
	float dy = b.y - a.y;

	float EPS = 3e4;

	double dist = sqrt( dx * dx + dy * dy);

	double F = (G * a.mass * b.mass) / (dist * dist + EPS * EPS);

	a.fx += F * dx / dist;
	a.fy += F * dy / dist;

	return a;
}

void print(planet p){

	cout << p.x << ", " << p.y << ", " << p.vx << ", " << p.vy << ", " << p.mass <<endl;
}

int main(int argc, const char * argv[]){

	planet planets[n];

	srand(time(NULL));

	for ( int i = 0; i < n; i++){

		float x = (rand() % 10) + 1;
		planets[i].x = x;

		float y = (rand() % 10) + 1;
		planets[i].y = y;

		float vx = (rand() % 10) + 1;
		planets[i].vx = vx;

		float vy = (rand() % 10) + 1;
		planets[i].vy = vy;

		float mass = (rand() % 10) + 1;
		mass = fabs(mass);
		planets[i].mass = mass;

	}

	//print(planets[0]);

	int count = 0;
	int n_of_iter = 1000;

	while (count < n_of_iter){

		for( int i = 0; i < n; i++){

			planets[i] = reset_force(planets[i]);

			for ( int j = 0; j < n; j++){

				if (i != j)

					planets[i] = add_force(planets[i], planets[j]);

			}
		}

		for ( int i = 0; i < n; i++){

			planets[i] = update(planets[i]);
		}

		for ( int i = 0; i < n; i++){

			print(planets[i]);
		}

		count++;
	}

	return 0;
}



