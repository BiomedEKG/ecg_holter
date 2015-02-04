#include <vector>
#include <iostream>
#include <AbstractModule.h>
#include <ResultKeeper.h>
#include <SleepApneaResult.h>
#include <string>
#include <StructApnea.h>
using namespace std;

#pragma once


class SleepApnea : public AbstractModule<SleepApneaResult>{


public:
	/*  niepotrzebne jesli get result sam wprowadza stringi
	string XUnit;
	string YUnit;
		
		/*
		& XUnit() // te dwa na zyczenie in out to chyba tu
		{
			static string foo("min");
			return foo;
		}
		
	string& YUnit()
		{
			static string boo("");
			return boo;
		};		//
		*/
	void SleepApnea::najmniejszeOdleglosci( float tab[2][20], float odlegl, float numerProbki );
	void SleepApnea::wczytywanie (probkaPCA tablicaProbekUczacych[16841],float wspolczynnikiPCA[11][11],float srednie[11],float odchylenia[11]);
	vector<float> SleepApnea::RR(vector<float> R_peaks_in, int size_Rpeaks, int fs);
	int SleepApnea::iloscMinut(vector<float> RX, int size_Rpeaks);
	float  SleepApnea::obliczSrednia(int liczbaUderzen, vector < float > tablicaAnalizowanych);
	float  SleepApnea::obliczOdchylenie(int liczbaUderzen, vector < float > tablicaAnalizowanych,float aktualnaSrednia);
	vector < float > SleepApnea::rozniceRR(int liczbaUderzen, vector < float > tablicaAnalizowanych);
	float  SleepApnea::obliczNN50_1(int liczbaUderzen, vector < float > roznice);
	float  SleepApnea::obliczNN50_2(int liczbaUderzen, vector < float > roznice);
	float  SleepApnea::obliczSDSD(int liczbaUderzen, vector < float > roznice);
	float  SleepApnea::obliczRMSSD(int liczbaUderzen, vector < float > roznice);
	vector < float > SleepApnea::sortuj(int liczbaUderzen, vector < float > tablicaAnalizowanych) ;
	float  SleepApnea::obliczMediane(int liczbaUderzen, vector < float > sortowanaAnalizowanych);
	float  SleepApnea::obliczIQR(int liczbaUderzen, vector < float > sortowanaAnalizowanych);
	float  SleepApnea::obliczMAD(int liczbaUderzen, vector < float > tablicaAnalizowanych, float aktualnaSrednia);
	probkaWczytana SleepApnea::normalizacja( probkaWczytana wczytana, float tablicaSrednich[11], float tablicaOdchylen[11]);
	probkaPCA SleepApnea::rzutowaniePCA( probkaWczytana znormalizowana, float wspolczynnikiPCA[11][11]);
	char SleepApnea::klasyfikuj(probkaPCA analizowanaProbka, probkaPCA tablicaProbekUczacych[16841], int metoda);
	vector <int> SleepApnea::zamianaNaInt(vector<probkaPCA>analizowaneProbki, int liczbaProbek);
	vector < int > SleepApnea::punktyPodzialu(vector<float> RX, int liczbaMinut);
	vector < probkaWczytana >  SleepApnea::inicjowanieProbek(int liczbaMinut);
	vector < float > SleepApnea::wyborAnalizowanych(int poczatek, int koniec, vector<float> RX);

	SleepApneaResult* SleepApnea :: Rampl(int fs, vector<float> R_peaks_in, int size_Rpeaks, int metoda);
	SleepApneaResult* SleepApnea :: compute(ResultKeeper* rkp);//   ZAPYTAC czy byl wazny const ;
	


};