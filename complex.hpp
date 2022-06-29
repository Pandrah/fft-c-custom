#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
using namespace std;
#include <cmath>
#define pi 3.141592653589

struct complex; // sinon il est débile il comprend pas 

double computeRe(complex c1);
double computeIm(complex c1);
double computeAbs(complex c1);
double computeArg(complex c1);
void show(complex c1);

complex operator+(complex c1,complex c2);
complex operator-(complex c1,complex c2);
complex operator*(complex c1,complex c2);
complex operator/(complex c1,complex c2);

ostream& operator<<(ostream& os,complex c1);

complex operator+(complex c1,double d);
complex operator-(complex c1,double d);
complex operator*(complex c1,double d);
complex operator/(complex c1,double d);

void reset(complex *c); //tout les paramètres à 0

typedef struct complex
{
	double re,im,abs,arg;
	
	complex(double cRe=0,double cIm=0,double cabs=0,double carg=0):
	re(cRe),im(cIm),abs(cabs),arg(carg)
	{	
		if(re==0 && im==0){ //si on précise que les coordonnées polaires et non carthésiennes, il ajuste les carthésiennes
		re=computeRe(*this);
		im=computeIm(*this);
		}
		
		else if(abs==0 && arg==0){ // ________________________________carthésiennes____polaires_____________________polaires
		abs = computeAbs(*this);
		arg = computeArg(*this);
		}
	}

}complex;
#endif