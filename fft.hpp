#ifndef FFT_HPP
#define FFT_HPP

#include "cplx.hpp"
#include <vector>
#include <algorithm>

#define LOW_PASS 0
#define HIGH_PASS 1

using namespace std;

vector<cplx> fft(vector<double> * signal);
vector<double> getAbs(vector<cplx> *spectre);
vector<double> getArg(vector<cplx>* spectre);
vector<double> ifft(vector<cplx>* spectre);

void filter(vector<cplx> * spectre,double Fc,double Fe, int mode);
void filtering(vector<cplx>*spectre,int i, int mode);


#endif
