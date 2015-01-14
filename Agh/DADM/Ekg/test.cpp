// main.cpp

#include "stdafx.h"
#include "SIG_EDR.h"
#include <fstream>
#include <string>
#include <vector> 
#include <iostream>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;


int main(){

	vector<double> T1;
	vector<double> T2;
	SIG_EDR *EDR = new SIG_EDR();
	vector<double> wynik_EDR;
	SIG_EDR *X_AXIS = new SIG_EDR();
	vector<double> wynik_X_AXIS;

    ifstream signalIn("signalIn.txt");
    ifstream R_real("R_real.txt");
   
   //Wczytanie pierwszego pliku
    if (!signalIn)
    {
        cout << "Nie mozna otworzyc pliku";
        getchar();
        return 1;
    }

	double x;
    while (!signalIn.eof())
    	while(signalIn >> x) T1.push_back(x); 
 
    signalIn.close();

    //Wczytanie drugiego pliku
        if (!R_real)
    {
        cout << "Nie mozna otworzyc pliku";
        getchar();
        return 1;
    }


	double y;
    while (!R_real.eof())
    	while(R_real >> y) T2.push_back(y); 
 
    R_real.close();

 	//Wywo³anie funkcji Rampl
	int signal_size = T1.size();
	int Rpeaks_size = T2.size();

	
 	wynik_EDR = EDR->Rampl(T1,signal_size,360,T2,Rpeaks_size);
	wynik_X_AXIS = X_AXIS->Rx(T2,Rpeaks_size);

	int EDR_size = wynik_EDR.size();

    //Zapisywanie do pliku
    
	fstream plik;
	string nazwapliku;
	cout << "Podaj nazwe pliku: ";
	cin >> nazwapliku;
	nazwapliku += ".txt";
	plik.open( nazwapliku.c_str(), ios::out );
	
	if( !plik.good() ){
    cout << "Nie udalo sie utworzyc pliku!\n";
	}
	else{
    cout << "Plik zostal utworzony\n";
	}

		for(int i=1; i<EDR_size ; i++)
        plik << wynik_EDR[i] <<endl;

getchar(); 

return 0;
    
}
