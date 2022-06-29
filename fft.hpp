#ifndef FFT_HPP
#define FFT_HPP

#include "complex.hpp"
#include <vector>
#include <algorithm>

#define LOW_PASS 0
#define HIGH_PASS 1

using namespace std;

vector<complex> fft(vector<double> * signal);
vector<double> getAbs(vector<complex> *spectre);
vector<double> getArg(vector<complex>* spectre);
vector<double> ifft(vector<complex>* spectre);

void filter(vector<complex> * spectre,double Fc,double Fe, int mode);
void filtering(vector<complex>*spectre,int i, int mode);


#endif