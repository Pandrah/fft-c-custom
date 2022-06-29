#include <iostream>
#include <vector>
#include <algorithm>

#include "fft.hpp"
#include "complex.hpp"

using namespace std;

vector<complex> fft(vector<double> * in){

	vector<complex> out; 

	long unsigned int n = in->size();
	double N = (double)n;
		
	for(unsigned int i=0; i < n; i++)
	{
		complex j; //par défaut à 0,0,0,0
			/*TEST
			vector<double>::iterator it = in->begin();

			while(it != in->end() )
			{
				complex e;

				e.abs = *it;
				it++;
			}
			*///FIN TEST
		for(unsigned int e = 0; e < n; e++){

			complex k(0,0,1,-2*pi*(double)i*(double)e/N);	//la partie reelle et immaginaire est ajustée automatiquement
			complex n((*in)[e],0,abs((*in)[e]),0);//pas de partie immaginaire
			n.arg = computeArg(n); // sécurité sur l'argument
				//source : https://fr.wikipedia.org/wiki/Transformation_de_Fourier_rapide#Formulation_math%C3%A9matique
			j = j+(k*n);			
		}
		out.push_back(j); 
	}

return out;
}

vector<double> getAbs(vector<complex> *spectre){

	vector<double> amp;

	for_each(begin(*spectre),end(*spectre), [&](complex elem){
		
		amp.push_back(elem.abs);

	});

	return amp;
}

vector<double> getArg(vector<complex> *spectre){

	vector<double> arguments;

	for_each(begin(*spectre),end(*spectre), [&](complex elem){ //std::for each
		
		arguments.push_back(elem.arg);

	});

	return arguments;

}

vector<double> ifft(vector<complex>* spectre){

	vector<double> signal;
	double N = (double) spectre->size();

	for(unsigned int i=0; i < spectre->size(); i++)
	{	
		complex j;

		for(unsigned int e = 0; e < N; e++){

			complex k(0,0,1,2*pi*(double)e*(double)i/N); //1*exp(2ijk/N)
			j=j+((*spectre)[e]*k);
			//source : https://www.rfwireless-world.com/Terminology/IFFT-vs-FFT.html
		}

		j=j/N; //normalisation à 1/N
		j.re=computeRe(j);
		signal.push_back(j.re);
	
	}

	return signal;
}


// ON RAPELLE QU'ON PEUT PAS FILTER AU DELÀ DE FE/2 SINON ÇA PLANTE
void filtering(vector<complex>*spectre,unsigned int i, int mode){ //est appelée par filter

	switch(mode){

		case LOW_PASS: //On pourrait faire comme le passe haut, c-a-d dégager uniquement un intervalle autour de Fe/2 mais flemme

		for(i;i<spectre->size();i++){
			reset(&(*spectre)[i]);
		}
			
		break;

		case HIGH_PASS: // dans le cas d'un passe haut, on dégage tout ce qui est inférieur à Fe/2-Fc -> et tout ce qui est supérieur à Fe/2+Fc (répétition du motif cardinal) 
		for(unsigned int a =0 ;a<i;a++){ // autrement dit on conserve uniquement un intervalle autour de Fe/2
			reset(&(*spectre)[a]);
			reset(&(*spectre)[spectre->size()-a]);
		}
		break;
	}

	
}

void filter(vector<complex> * spectre,double Fc, double Fe, int mode){// reste à implémenter la sécurité pour Fc pas trop haut
	double deltaF = Fe/(double)spectre->size();
	unsigned int i = int(Fc/deltaF);
	filtering(spectre,i,mode);
}

