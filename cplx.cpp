#include <iostream>

#include "cplx.hpp"
using namespace std;

double computeRe(cplx c1){
	return c1.abs*cos(c1.arg);
}
double computeIm(cplx c1){
	return c1.abs*sin(c1.arg);
}
double computeAbs(cplx c1){
	return sqrt((c1.re*c1.re)+(c1.im*c1.im));
}

double computeArg(cplx c1){

	if(c1.re !=0){
	double arg = atan(c1.im/c1.re);
	
	if(c1.re <0){ //BORDEL IL FALLAIT CE TRUC LA
		arg+=pi;
	}

	return arg;
	}
	else{

		if(c1.im !=0){
			return 0;
		}

		else{
			return pi/2;
		}
	}
}

cplx operator+(cplx c1,cplx c2){

	cplx c3;
	c3.re = c1.re+c2.re;
	c3.im = c1.im+c2.im;

	c3.abs = computeAbs(c3);
	c3.arg = computeArg(c3);

	return c3;
}

cplx operator-(cplx c1,cplx c2){

	cplx c3;
	c3.re = c1.re-c2.re;
	c3.im = c1.im-c2.im;

	c3.abs = computeAbs(c3);
	c3.arg = computeArg(c3);

	return c3;

}

cplx operator*(cplx c1,cplx c2){

	cplx c3;
	c3.abs = c1.abs*c2.abs;
	c3.arg = c1.arg+c2.arg;

	c3.re = computeRe(c3);
	c3.im = computeIm(c3);

	return c3;
}
cplx operator/(cplx c1,cplx c2){

	cplx c3;
	c3.abs = c1.abs/c2.abs;
	c3.arg = c1.arg-c2.arg;

	c3.re = computeRe(c3);
	c3.im = computeIm(c3);

	return c3;
}

ostream& operator<<(ostream& os,cplx c1){
	show(c1);
	return os;	
}

void show(cplx c1){
	cout <<"Carth : \n " << to_string(c1.re) <<" + i." << to_string(c1.im) << endl;
	cout <<"Exp : " << to_string(c1.abs) <<".exp(i." << to_string(c1.arg)<<".	pi)\n\n";

}

cplx operator+(cplx c1,double d){
	c1.re+=d;
	c1.abs=computeAbs(c1);
	c1.arg=computeArg(c1);
	return c1;
}
cplx operator-(cplx c1,double d){
	c1.re-=d;
	c1.abs=computeAbs(c1);
	c1.arg=computeArg(c1);
	return c1;
}
cplx operator*(cplx c1,double d){
	c1.abs*=d;
	c1.re=computeRe(c1);
	c1.im=computeIm(c1);
	return c1;
}
cplx operator/(cplx c1,double d){
	c1.abs/=d;
	c1.re=computeRe(c1);
	c1.im=computeIm(c1);
	return c1;
}

void reset(cplx *c){
	c->re=0;
	c->im=0;
	c->abs=0;
	c->arg=0;	
}
