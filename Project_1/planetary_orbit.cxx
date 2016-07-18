#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cstdio>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>


#include "TROOT.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraph2D.h"
#include "TApplication.h"
#include "TRint.h"
#include "TF1.h"
#include "TAxis.h"
#include "TMultiGraph.h"
#include "TFormula.h"
#include "TH2.h"
#include "TStyle.h"


#define G 4 * M_PI * M_PI
#define N  10000

using namespace std;

struct planet {
	float x;
	float y;
	float v_x;
	float v_y;
	float a_x;
	float a_y;
	float mass;
};

struct planet earth, oldEarth,  sun, oldSun;

void updatePlanets(struct planet *earth, float dt);

int main( int argc, char **argv ){

	TRint theApp("App",&argc, argv);

	float t[N], earth_x[N], earth_y[N], earth_v_x[N], earth_v_y[N];

	float dt = 0.01;

	FILE *result = fopen("results/earth/earth_3.csv","w");

	float e = 0.0167;
	float a = 1;
	earth.v_x = 0.0;
	earth.x = a + a * e;
	earth.y = 0.0;
	earth.mass = 2.44e-6;	

	sun.mass = 1.0;

	earth.v_y = sqrt(G ) * sqrt((1-e)/(a*(1+e))*(1 + earth.mass/ sun.mass));


	for ( int i = 0; i < N; i++){


		t[i] = i * dt;


		earth_x[i] = earth.x;
		earth_y[i] = earth.y;
		earth_v_x[i] = earth.v_x;
		earth_v_y[i] = earth.v_y;



		fprintf(result, "%lf, %lf, %lf, %lf \n", earth.x, earth.y, earth.v_x, earth.v_y);


		updatePlanets(&earth, dt);


	}


	TGraph *gr = new TGraph (N, earth_x, earth_y);


	float b = earth_y[0];

	for(int i = 0; i < N; i++){
		
		if(earth_y[i] > b)
			b = earth_y[i];
		
	}
	
	cout << a << endl;
	cout << b << endl;

	float e_2 = sqrt(1-(b*b)/(a*a));

	cout << e_2 << endl;


	fprintf(result,"%lf, %lf %lf", dt, e, e_2, (e-e_2)/e);

	gr->Draw("AP*");
	theApp.Run();

	fclose(result);

	return 0;

}


void updatePlanets(struct planet *earth, float dt)
{


	oldEarth = *earth;

	float r_earth_sun = sqrt(earth->x * earth->x + earth->y * earth->y);

	earth->v_x = oldEarth.v_x -  4 * M_PI * M_PI * earth->x / pow(r_earth_sun,3) * dt;
	earth->v_y = oldEarth.v_y -  4 * M_PI * M_PI * earth->y / pow(r_earth_sun,3) * dt;

	earth->x = oldEarth.x + earth->v_x * dt;
	earth->y = oldEarth.y + earth->v_y * dt;
}


