#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>

#include "fft.hpp"

using namespace std;

#define SINUS
//#define CARRE
//#define TRIANGLE

//~~~~~~~~~Une fonction qui affiche les valeurs dans le terminal~~~~~~~~~~~~~
template<typename d>
void showData(vector<d> *signal){
	cout<<"\n";
	for(long unsigned int a=0;a<signal->size();a++){
		//cout<<a << "] ";
		cout << (*signal)[a]<<",";
	}
	cout<<endl;
}


//~~~~~~~~La fonction qui crée un .txt avec les valeurs dedans pour les afficher avec matplotlib~~~~~~~~~
template<typename info>
void createFile(string path,vector <info> *inf){

	ofstream flux(path.c_str());

	if(flux){

		unsigned int i=0;

		for_each(begin(*inf),end(*inf), [&](info elem){
			
			flux<<elem;

			if(i != inf->size()-1){
				flux<<"\n";
				i++;
			}
		});
	}
}

int main(){
	
	vector<double> signal; //signal temporel qu'on remplit un peu plus tard - On décomentera les signaux qu'on souhaite obtenir

	double freq = 1; //fréquences pour les tests de sinus
	double freq2 = 5;
	double freq3 = 10;
	double freq4 = 20;
	double freq5 = 30;
	double freq6 = 50;

	double Fe = 100; //j'ai vraiment besoin d'expliquer ?
	double Te = 1/Fe;

	int Tf=5; //Fenêtre temporelle d'étude

	double coef_dir=1; //pour le triangle

	double i=0;

	//~~~~~~~~~~~~~~~~signal sinusoidal~~~~~~~~~~~~~~ -> Amplitudes au pif
#ifdef SINUS
	for(double i =0; i < Tf; i+=Te){
		signal.push_back(2*sin(2*pi*freq*i));
						//+0.5*sin(2*pi*freq2*i)
						//+0.3*sin(2*pi*freq3*i)
						//+0.2*sin(2*pi*freq4*i)
						//+0.1*sin(2*pi*freq5*i)
						//+0.07*sin(2*pi*freq6*i));
	}

#endif


	//~~~~~~~~~~~~~~~~signal carré~~~~~~~~~~~~~~~~~
#ifdef CARRE
	for(i = 0; i< Tf;i+=Te){

		((int)i%2==0?signal.push_back(1):signal.push_back(-1));
		
	}
#endif

	//~~~~~~~~~~~~~~~signal triangle~~~~~~~~~~~~~~ 
#ifdef TRIANGLE
	signal.push_back(-Te);//tkt -> il faut remplir le signal avec au moins un élément avant de procéder à la boucle for

	for(i = 0; i<Tf;i+=Te){

		double elem=signal[signal.size()-1];
		((int)i%2<1 ? elem+=Te*coef_dir : elem-=Te*coef_dir ); //modifier le 10 et le 5 pour ajuster la période et le tps à l'état haut en fonction de Fe et Tf
		signal.push_back(elem);
	}
#endif

	//cout << "\n~~~~~~~~~~Signal in time domain ~~~~~~~~"; 
	//showData(&signal);

	vector <complex> spectre = fft(&signal);
	vector <double> abs = getAbs(&spectre); // Pour obtenir le spectre d'amplitude

	//cout << "\n\n~~~~~~~~~Signal in frequencies domain ~~~~~~~~"; 
	//showData(abs);

	//showData(&spectre);

	filter(&spectre,3,Fe,LOW_PASS); //On décide de filtrer à 5 HZ en mode passe bas (filtre parfait donc gain = -inf dB)
	//On rappelle qu'on peut pas filtrer au delà de Fe/2 

	vector<double> abs2=getAbs(&spectre); // spectre d'amplitude filtré
	vector<double> arg2=getArg(&spectre); // spectre de phase filtré
	//vector<double> arg = getArg(&spectre); //pour obtenir le spectre de phase
	vector<double> Rec= ifft(&spectre);
	//cout<<"\n\n~~~~~~~~~~~~Recomposed signal in time domain~~~~~~~~~~";
	//showData(Rec)

	createFile("textes/time_Signal.txt",&signal);
	createFile("textes/Spectre_Signal.txt",&abs);
	createFile("textes/recomposed_Signal.txt",&Rec); // ON RAPPELLE CELUI LÀ C'EST LE SIGNAL TEMPOREL RECOMPOSÉ MAIS FILTRÉ (voir ligne 107)
	createFile("textes/spectre_Filtre.txt",&abs2);
	//createFile("textes/spectre_FiltreA.txt",&arg2);
	//createFile("textes/arguments.txt",&arg);

	return 0;
}
