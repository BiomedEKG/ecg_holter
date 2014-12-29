//#define _USE_MATH_DEFINES

#include "hrv1.h"
#include <numeric> //std::accumulate
#include <cmath> //sqrt,pow,ceil floor, M_PI
#include <map>
#include <iostream>
#include <string>

using namespace std;

class HRV1 {
public:
	map<string, double> timeParameter;

	map<string, double> compute(vector < double > tab){
		timeParameter["RR_mean"]= RR_mean(tab);
		timeParameter["RR_sdnn"]= RR_sdnn(tab);
		timeParameter["RR_rmssd"]= RR_rmssd(tab);
		timeParameter["RR_nn50"]= RR_nn50(tab);
		timeParameter["RR_pnn50"]= RR_pnn50(tab);
		timeParameter["RR_sdann"]= RR_sdann(tab);
		timeParameter["RR_sdanni"]= RR_sdanni(tab);
		timeParameter["RR_sdsd"]= RR_sdsd(tab);
		return timeParameter;
	}


vector<double> type_change(vector<unsigned int> &vec){
	vector<double> nowy(vec.size());
	nowy.clear();
	for (unsigned int i = 0; i<vec.size(); i++)
	{
		nowy.push_back((double)vec[i]);
	}
		return nowy;
}

vector<double> RR(vector<double> &vec, double fp){ //zmieniamy wektor probek na odstepy R-R,
    vector<double> rr(vec.size()-1);
    for (unsigned i = 1; i<vec.size(); i++)
            rr[i-1] = (vec[i] - vec[i-1]) /fp;
    return rr; //obliczenia w innych metodach na tym wektorze
}
vector<double> RR_time(vector<double> &vec, double fp){ //zmieniamy wektor probek na odstepy R-R,
    vector<double> rr_time(vec.size()-1);
	double suma = vec[0]/fp;
    for (unsigned i = 0; i<vec.size()-1; i++){
			rr_time[i] = suma;
			suma +=(vec[i+1] - vec[i]) /fp;
	}
    return rr_time; //obliczenia w innych metodach na tym wektorze
}



double RR_mean(vector<double> &vec){

    double sum = std::accumulate(vec.begin(),vec.end(),0.0);
    double mean = sum/vec.size();
    return mean;
}

double RR_sdnn(vector<double> &vec){ //odchylenie standardowe
    double mean = RR_mean(vec);
	vector<double> temp(vec.size());
    for (unsigned i = 0; i<vec.size(); i++)
	{
        temp[i] = pow((vec[i] - mean),2);
	}
    double sdnn = sqrt((std::accumulate(temp.begin(),temp.end(),0.0))/temp.size());
	temp.clear();
    return sdnn;
}

double RR_rmssd(vector<double> &vec){
   //RMSSD = sqrt(sum((A(2:l) - A(1:(l-1))).^2)/(l-1))
   //pierwiastek kwadratowy ze œredniej kwadratów ró¿nic pomiêdzy dwoma interwa³ami RR
	vector<double> temp(vec.size());
    for (unsigned i = 0; i<(vec.size()-1); i++)
        temp[i] = pow(vec[i+1] - vec[i],2);
    double rmssd = sqrt((std::accumulate(temp.begin(),temp.end(),0.0))/temp.size());
	temp.clear();
    return rmssd;
}

int RR_nn50(vector<double> &vec){ //tutaj nie musi zwracac double, wystarczylby int
    int nn50 = 0;
    for (unsigned i = 1; i<vec.size(); i++)
    {
        if ((vec[i]-vec[i-1]) > 0.05)
            nn50 = nn50 +1;
    }
 return nn50;
}

double RR_pnn50(vector<double> &vec){

	double a = (double)RR_nn50(vec);
    double b = a/(vec.size()-1);
	return b;
}

double round(double value){ //czy nie powinna int zwracac?
    double round;
    if (value<0)
            round = ceil(value-0.5);
    else
             round = floor(value+0.5);
    return round;
}

vector<int> index_300(vector<double> &vec){

	int N = int(floor((std::accumulate(vec.begin(),vec.end(),0.0))/300)); //;liczba przedzialow 300-sekundoych
    int i = 0 ; //indeks calego wektora
	vector<int> index(N+1); //wektor na indeksy przedzialow co 300 s
	index.clear();
    index.push_back(0); //poczatek pierwszego przedzialu to pierwsza probka
    //int k = 1; //indeks tablicy przedzialow

    for (int j = 0; j <	N; j++)
    {
        double sum = 0;
        while ( (sum<300) && (i<vec.size())) //czy tu nie trzeba dodac lub i<vec.size? nie. bo petla j tylko po pelnych przedzialach.
        {
            sum = sum + vec[i];
            i = i + 1;
        }
        index.push_back(i-1); //-1 bo zwiêkszylismy przy ostatniej iteracji na nastepna probke
        //k = k + 1;
    } 

	return index;

}

double RR_sdann(vector<double> &vec){
//    %SDANN - odchylenie standardowe ze wszystkich srednich interwa³ów RR w 5-minutowych
//    %segmentach czasu ca³ego zapisu
    
	vector<int> tab = index_300(vec);
    vector<double> srednia;
    for (unsigned int i = 1; i < tab.size() ; i++)
    {
        srednia.push_back((std::accumulate(vec.begin()+tab[i-1],vec.begin()+tab[i],0.0))/(tab[i-1]-tab[i]));
    }
    double sdann = RR_sdnn(srednia); //odchylenie standardowe ze srednich
	tab.clear();
	srednia.clear();
    return sdann;
}

double RR_sdanni(vector<double> &vec){
	//srednia z odchylen stanardowych interwalow 5-min

	vector<int> tab = index_300(vec);
	int N = tab.size();
    vector<double> temp;
	double od;
	vector <double> odchylenia;

    for (int i = 1; i<N; i++)
    {
		temp.assign(vec.begin()+tab[i-1],vec.begin()+tab[i]); //skopiowanie do temp przedzialu 300 s
		od = RR_sdnn(temp); //policzenie odchylenia standardowego z przedzialu 300 s
        odchylenia.push_back(od);
    }
    double sdanni = RR_mean(odchylenia); //srednia z odchylen

	tab.clear();
	temp.clear();
	odchylenia.clear();

    return sdanni;
}

double RR_sdsd(vector<double> &vec){
    vector<double> a;
    for (unsigned i = 1; i<vec.size(); i++)
        a.push_back(vec[i] - vec[i-1]);
    double sdsd = RR_sdnn(a);
	a.clear();
    return sdsd;
}

};
