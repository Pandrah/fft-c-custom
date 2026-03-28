#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
using namespace std;
#include <cmath>
#define pi 3.141592653589

struct cplx; // sinon il est débile il comprend pas 

double computeRe(cplx c1);
double computeIm(cplx c1);
double computeAbs(cplx c1);
double computeArg(cplx c1);
void show(cplx c1);

cplx operator+(cplx c1,cplx c2);
cplx operator-(cplx c1,cplx c2);
cplx operator*(cplx c1,cplx c2);
cplx operator/(cplx c1,cplx c2);

ostream& operator<<(ostream& os,cplx c1);

cplx operator+(cplx c1,double d);
cplx operator-(cplx c1,double d);
cplx operator*(cplx c1,double d);
cplx operator/(cplx c1,double d);

void reset(cplx *c); //tout les paramètres à 0

typedef struct cplx
{
	double re,im,abs,arg;
	
	cplx(double cRe=0,double cIm=0,double cabs=0,double carg=0):
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

}cplx;
#endif
