#include "SleepApnea.h"
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <fstream>
#include <map>
#include <cmath>
#include <stdlib.h> 
#include <vector>

using namespace std;






void SleepApnea::najmniejszeOdleglosci( float tab[2][20], float odlegl, float numerProbki )

	{
		for(int x=0;x<20;x++){
			
			if(odlegl<tab[0][x]){
				
				for(int j=19;j>x;j--){
					
					tab[0][j]=tab[0][j-1];
					tab[1][j]=tab[1][j-1];
				}
				
					tab[0][x]=odlegl;
					tab[1][x]=numerProbki;
					break;
			}
			
			
		}
	}



//wczytywanie danyc PCA do klasyfikacji
void SleepApnea::wczytywanie (probkaPCA tablicaProbekUczacych[16841],float wspolczynnikiPCA[11][11],float srednie[11],float odchylenia[11]){

	int i; 
	int k;

	ifstream in("SleepdanePCAProbek.txt");


	for ( i=0; i < 16841; i++){
		in >> tablicaProbekUczacych[i].PC1 >> tablicaProbekUczacych[i].PC2 >> tablicaProbekUczacych[i].PC3 >>
		tablicaProbekUczacych[i].PC4 >> tablicaProbekUczacych[i].PC5 >> tablicaProbekUczacych[i].PC6>>
		tablicaProbekUczacych[i].PC7 >> tablicaProbekUczacych[i].PC8 >> tablicaProbekUczacych[i].PC9>>
		tablicaProbekUczacych[i].PC10 >> tablicaProbekUczacych[i].PC11;
	}

	ifstream etyk("Sleepetykiety.txt");

	for ( i=0; i < 16841; i++){
	
		etyk >> tablicaProbekUczacych[i].typ;
	}


	ifstream PCA("SleepPCAWspolczynniki.txt");	


	for ( i=0; i < 11; i++){
		for (k=0; k < 11; k++){
	
		PCA >> wspolczynnikiPCA[k][i];
		}
	}
	
	

	ifstream plikSrednie("Sleepsrednie.txt");	
	
	for ( i=0; i < 11; i++){
		
		plikSrednie >> srednie[i];
	}





	ifstream plikOdchylenia("Sleepodchylenia.txt");	

	for ( i=0; i < 11; i++){
		
		plikOdchylenia >> odchylenia[i];
	}


}

//wczytwanie r peakow na bazie tego co zrobily dziwczyny w sig_edr i robienie interwalow
vector<float> SleepApnea::RR(vector<float> R_peaks_in, int size_Rpeaks,int fs){

	int czestotliwoscProbkowania=fs;///wpisac trzeba ta co trzeba albo wsadzic jako arg funkcji
	float* R_peaks = new float[size_Rpeaks];
	for(int i=0; i<size_Rpeaks; i++) R_peaks[i] = R_peaks_in[i];
	// Zapisywanie do wektora interwa³ów
	vector<float> RX;
	for(int i = 0; i < size_Rpeaks-1; i++ ) RX.push_back( (R_peaks[i+1]- R_peaks[i])/czestotliwoscProbkowania);
	delete [] R_peaks;
	return RX;
}





//przyjmuje argument od r_peaksow - ilosc R; mowi jak d³ugi sygna³ jest w minutach
int SleepApnea::iloscMinut(vector<float> RX, int size_Rpeaks){
	
	
	float czasPomiaru=0;
	
	
	for(int i=0;i<size_Rpeaks-1;i++){
		czasPomiaru=czasPomiaru+RX[i];
	}

	int iloscProbekCzasu=floor(czasPomiaru/60);
	return iloscProbekCzasu;
}


/// informuje o numerach interwalow ktory koncza dana minute
vector < int > SleepApnea::punktyPodzialu(vector<float> RX, int liczbaMinut){

	vector < int > punktyPodzial;
	punktyPodzial.push_back( 0 );
	float sumaCzasow=0;
	int wskaznikPodzialu=0;
	//float czestotliwosc_probkowania=120;
	for (int i=0; i<liczbaMinut; i++){

		while (sumaCzasow<(60*(i+1))){

		sumaCzasow=sumaCzasow+RX[wskaznikPodzialu];
		wskaznikPodzialu++;
	
		}

	 punktyPodzial.push_back( wskaznikPodzialu );
	}

	return punktyPodzial;
}


vector < probkaWczytana >  SleepApnea::inicjowanieProbek(int liczbaMinut){

	vector < probkaWczytana > tablica;
	for (int i=0; i<liczbaMinut; i++){

		tablica.push_back(probkaWczytana());
	}

	return tablica;
}



//pozostaiwa tylko interwaly dluzsze ni¿ 0,5 i krotsze niz 1,5 sek
vector < float > SleepApnea::wyborAnalizowanych(int poczatek, int koniec, vector<float> RX){


	vector < float >tablicaAnalizowanych;
	
	for(int k=poczatek;k<koniec;k++){

		if(!(RX[k]<0.5||RX[k]>1.5)){

			tablicaAnalizowanych.push_back(RX[k]);
		}
	}

	return tablicaAnalizowanych;
}




float  SleepApnea::obliczSrednia(int liczbaUderzen, vector < float > tablicaAnalizowanych){

	float sumaDoSredniej=0;
	for(int k=0;k<liczbaUderzen;k++)
	
	{
		sumaDoSredniej=sumaDoSredniej+tablicaAnalizowanych[k];
	
	}

	float srednia=sumaDoSredniej/liczbaUderzen;

	return srednia;

}

float  SleepApnea::obliczOdchylenie(int liczbaUderzen, vector < float > tablicaAnalizowanych,float aktualnaSrednia){

	float sumaDoOdchylenia=0;
	for(int k=0;k<liczbaUderzen;k++)
	
	{
		sumaDoOdchylenia=sumaDoOdchylenia+pow((aktualnaSrednia-tablicaAnalizowanych[k]),2);
	
	}

	float odchylenie=sqrt(sumaDoOdchylenia/liczbaUderzen);

	return odchylenie;

}



vector < float > SleepApnea::rozniceRR(int liczbaUderzen, vector < float > tablicaAnalizowanych){

	float roznica;
	vector < float > roznice;
	
	for(int k=0;k<(liczbaUderzen-1);k++){
		
		roznica=tablicaAnalizowanych[k+1]-tablicaAnalizowanych[k];
		roznice.push_back(roznica);
	}

	return roznice;
}


float  SleepApnea::obliczNN50_1(int liczbaUderzen, vector < float > roznice){

	float NN50_1=0;
	
	for(int k=0;k<liczbaUderzen-1;k++){


		if(roznice[k]>0.05){
			NN50_1++;
		}
	}
	

	return NN50_1;

}

float  SleepApnea::obliczNN50_2(int liczbaUderzen, vector < float > roznice){

	float NN50_2=0;
	
	for(int k=0;k<liczbaUderzen-1;k++){


		if(roznice[k]<-0.05){
			NN50_2++;
		}
	}
	

	return NN50_2;

}

float  SleepApnea::obliczSDSD(int liczbaUderzen, vector < float > roznice){

	float sumaDoSDSD=0;
	float sumaDoSDSD2=0;
	float sredniaDoSDSD;
	float aktualneSDSD;

	for(int k=0;k<liczbaUderzen-1;k++){

		sumaDoSDSD=sumaDoSDSD+roznice[k];

	}
	sredniaDoSDSD=sumaDoSDSD/(liczbaUderzen-1);

	for (int k=0;k<liczbaUderzen-1;k++){
	
		sumaDoSDSD2=sumaDoSDSD2+pow((sredniaDoSDSD-roznice[k]),2);
	
	}
	float SDSD=sqrt(sumaDoSDSD2/(liczbaUderzen-1));
	return SDSD;

}


float  SleepApnea::obliczRMSSD(int liczbaUderzen, vector < float > roznice){

	float sumaDoRMSSD=0;

	for (int k=0;k<liczbaUderzen-1;k++){
	
	sumaDoRMSSD=sumaDoRMSSD+pow((roznice[k]),2);
	
	}

	float RMSSD=sqrt(sumaDoRMSSD/(liczbaUderzen-1));
	
	return RMSSD;

}



//sortowanie tablicy analizowanych uderzen - potrzebne do policzenia mediany i IQR
vector < float > SleepApnea::sortuj(int liczbaUderzen, vector < float > tablicaAnalizowanych) {

	vector<float> sortowanaAnalizowanych;

	for(int k=0;k<liczbaUderzen;k++){
	
		sortowanaAnalizowanych.push_back(tablicaAnalizowanych[k]);
	
	}


	float pomocnicza;
	int j;

	for(j=0; j<liczbaUderzen;j++){

		 for (int k = 0; k < liczbaUderzen-1-j; k++) {
                if (sortowanaAnalizowanych[k] > sortowanaAnalizowanych[k+1]) {
                    
					pomocnicza=sortowanaAnalizowanych[k];
					sortowanaAnalizowanych[k]=sortowanaAnalizowanych[k+1];
					sortowanaAnalizowanych[k+1]=pomocnicza;

            }

		}

	}

	return sortowanaAnalizowanych;

}


float  SleepApnea::obliczMediane(int liczbaUderzen, vector < float > sortowanaAnalizowanych){

	float mediana;

	if(liczbaUderzen%2==1){
	
		mediana=sortowanaAnalizowanych[(liczbaUderzen+1)/2];
	}
	
	else{
	
		mediana=(sortowanaAnalizowanych[liczbaUderzen/2]+sortowanaAnalizowanych[(liczbaUderzen/2)+1])/2;
	}


	return mediana;
}


float  SleepApnea::obliczIQR(int liczbaUderzen, vector < float > sortowanaAnalizowanych){

	float kwartyl1;
	float kwartyl3;
	float IQR;

	if(liczbaUderzen%4==0){
		kwartyl1=0.5*sortowanaAnalizowanych[(liczbaUderzen  /4)]+0.5*sortowanaAnalizowanych[(liczbaUderzen   /4)+1];
		kwartyl3=0.5*sortowanaAnalizowanych[(liczbaUderzen*3/4)]+0.5*sortowanaAnalizowanych[(liczbaUderzen*3/4)+1];

	}

	else if (liczbaUderzen%4==1){
		kwartyl1=0.25*sortowanaAnalizowanych[(int)(floor(liczbaUderzen /4))]+0.75*sortowanaAnalizowanych[(int)(floor(liczbaUderzen /4))+1];
		kwartyl3=0.75*sortowanaAnalizowanych[(int)(ceil(liczbaUderzen*3/4))]+0.25*sortowanaAnalizowanych[(int)(ceil(liczbaUderzen*3/4))+1];

	}

	else if (liczbaUderzen%4==2){
	
		if(liczbaUderzen==2){
			kwartyl1=0.75*sortowanaAnalizowanych[0];
			kwartyl3=1.25*sortowanaAnalizowanych[1];
		}

		else{
			kwartyl1=sortowanaAnalizowanych[int(ceil(liczbaUderzen/4))];
			kwartyl3=sortowanaAnalizowanych[int(ceil(liczbaUderzen*3/4))];
		}	
	}
	
	else {
	
		if(liczbaUderzen==3){
			kwartyl1=sortowanaAnalizowanych[0];
			kwartyl3=sortowanaAnalizowanych[2];
		}

		else{
			kwartyl1=0.75*sortowanaAnalizowanych[(int)(ceil(liczbaUderzen  /4))  ]+0.25*sortowanaAnalizowanych[(int)(ceil(liczbaUderzen  /4))+1];
			kwartyl3=0.25*sortowanaAnalizowanych[(int)(ceil(liczbaUderzen*3/4))+1]+0.75*sortowanaAnalizowanych[(int)(ceil(liczbaUderzen*3/4))+2];
		}	
	
	}

	IQR=kwartyl3-kwartyl1;
	return IQR;
}


float  SleepApnea::obliczMAD(int liczbaUderzen, vector < float > tablicaAnalizowanych, float aktualnaSrednia){

	float MAD;
	float sumaDoMAD=0;

	for(int k=0;k<liczbaUderzen; k++){

		

	sumaDoMAD=sumaDoMAD+fabs(tablicaAnalizowanych[k]-aktualnaSrednia);

	}

	MAD=sumaDoMAD/liczbaUderzen;
	return MAD;

}


//standaryzacja
probkaWczytana SleepApnea::normalizacja( probkaWczytana wczytana, float tablicaSrednich[11], float tablicaOdchylen[11]){

	
	probkaWczytana probkaZnormalizowana;
	
		
	probkaZnormalizowana.srednia=(wczytana.srednia-tablicaSrednich[0])/tablicaOdchylen[0];
	probkaZnormalizowana.odchylenie=(wczytana.odchylenie-tablicaSrednich[1])/tablicaOdchylen[1];
	probkaZnormalizowana.NN50_1=(wczytana.NN50_1-tablicaSrednich[2])/tablicaOdchylen[2];
	probkaZnormalizowana.NN50_2=(wczytana.NN50_2-tablicaSrednich[3])/tablicaOdchylen[3];
	probkaZnormalizowana.pNN50_1=(wczytana.pNN50_1-tablicaSrednich[4])/tablicaOdchylen[4];
	probkaZnormalizowana.pNN50_2=(wczytana.pNN50_2-tablicaSrednich[5])/tablicaOdchylen[5];
	probkaZnormalizowana.SDSD=(wczytana.SDSD-tablicaSrednich[6])/tablicaOdchylen[6];
	probkaZnormalizowana.RMSSD=(wczytana.RMSSD-tablicaSrednich[7])/tablicaOdchylen[7];
	probkaZnormalizowana.mediana=(wczytana.mediana-tablicaSrednich[8])/tablicaOdchylen[8];
	probkaZnormalizowana.IQR=(wczytana.IQR-tablicaSrednich[9])/tablicaOdchylen[9];
	probkaZnormalizowana.MAD=(wczytana.MAD-tablicaSrednich[10])/tablicaOdchylen[10];

	return probkaZnormalizowana;
}


probkaPCA SleepApnea::rzutowaniePCA( probkaWczytana znormalizowana, float wspolczynnikiPCA[11][11]){

	probkaPCA wczytanaProbkaPCA;
	wczytanaProbkaPCA.PC1=znormalizowana.srednia*wspolczynnikiPCA[0][0]+znormalizowana.odchylenie*wspolczynnikiPCA[1][0]+znormalizowana.NN50_1*wspolczynnikiPCA[2][0]+znormalizowana.NN50_2*wspolczynnikiPCA[3][0]+znormalizowana.pNN50_1*wspolczynnikiPCA[4][0]+znormalizowana.pNN50_2*wspolczynnikiPCA[5][0]+znormalizowana.SDSD*wspolczynnikiPCA[6][0]+znormalizowana.RMSSD*wspolczynnikiPCA[7][0]+znormalizowana.mediana*wspolczynnikiPCA[8][0]+znormalizowana.IQR*wspolczynnikiPCA[9][0]+znormalizowana.MAD*wspolczynnikiPCA[10][0];
	wczytanaProbkaPCA.PC2=znormalizowana.srednia*wspolczynnikiPCA[0][1]+znormalizowana.odchylenie*wspolczynnikiPCA[1][1]+znormalizowana.NN50_1*wspolczynnikiPCA[2][1]+znormalizowana.NN50_2*wspolczynnikiPCA[3][1]+znormalizowana.pNN50_1*wspolczynnikiPCA[4][1]+znormalizowana.pNN50_2*wspolczynnikiPCA[5][1]+znormalizowana.SDSD*wspolczynnikiPCA[6][1]+znormalizowana.RMSSD*wspolczynnikiPCA[7][1]+znormalizowana.mediana*wspolczynnikiPCA[8][1]+znormalizowana.IQR*wspolczynnikiPCA[9][1]+znormalizowana.MAD*wspolczynnikiPCA[10][1];
	wczytanaProbkaPCA.PC3=znormalizowana.srednia*wspolczynnikiPCA[0][2]+znormalizowana.odchylenie*wspolczynnikiPCA[1][2]+znormalizowana.NN50_1*wspolczynnikiPCA[2][2]+znormalizowana.NN50_2*wspolczynnikiPCA[3][2]+znormalizowana.pNN50_1*wspolczynnikiPCA[4][2]+znormalizowana.pNN50_2*wspolczynnikiPCA[5][2]+znormalizowana.SDSD*wspolczynnikiPCA[6][2]+znormalizowana.RMSSD*wspolczynnikiPCA[7][2]+znormalizowana.mediana*wspolczynnikiPCA[8][2]+znormalizowana.IQR*wspolczynnikiPCA[9][2]+znormalizowana.MAD*wspolczynnikiPCA[10][2];
	wczytanaProbkaPCA.PC4=znormalizowana.srednia*wspolczynnikiPCA[0][3]+znormalizowana.odchylenie*wspolczynnikiPCA[1][3]+znormalizowana.NN50_1*wspolczynnikiPCA[2][3]+znormalizowana.NN50_2*wspolczynnikiPCA[3][3]+znormalizowana.pNN50_1*wspolczynnikiPCA[4][3]+znormalizowana.pNN50_2*wspolczynnikiPCA[5][3]+znormalizowana.SDSD*wspolczynnikiPCA[6][3]+znormalizowana.RMSSD*wspolczynnikiPCA[7][3]+znormalizowana.mediana*wspolczynnikiPCA[8][3]+znormalizowana.IQR*wspolczynnikiPCA[9][3]+znormalizowana.MAD*wspolczynnikiPCA[10][3];
	wczytanaProbkaPCA.PC5=znormalizowana.srednia*wspolczynnikiPCA[0][4]+znormalizowana.odchylenie*wspolczynnikiPCA[1][4]+znormalizowana.NN50_1*wspolczynnikiPCA[2][4]+znormalizowana.NN50_2*wspolczynnikiPCA[3][4]+znormalizowana.pNN50_1*wspolczynnikiPCA[4][4]+znormalizowana.pNN50_2*wspolczynnikiPCA[5][4]+znormalizowana.SDSD*wspolczynnikiPCA[6][4]+znormalizowana.RMSSD*wspolczynnikiPCA[7][4]+znormalizowana.mediana*wspolczynnikiPCA[8][4]+znormalizowana.IQR*wspolczynnikiPCA[9][4]+znormalizowana.MAD*wspolczynnikiPCA[10][4];
	wczytanaProbkaPCA.PC6=znormalizowana.srednia*wspolczynnikiPCA[0][5]+znormalizowana.odchylenie*wspolczynnikiPCA[1][5]+znormalizowana.NN50_1*wspolczynnikiPCA[2][5]+znormalizowana.NN50_2*wspolczynnikiPCA[3][5]+znormalizowana.pNN50_1*wspolczynnikiPCA[4][5]+znormalizowana.pNN50_2*wspolczynnikiPCA[5][5]+znormalizowana.SDSD*wspolczynnikiPCA[6][5]+znormalizowana.RMSSD*wspolczynnikiPCA[7][5]+znormalizowana.mediana*wspolczynnikiPCA[8][5]+znormalizowana.IQR*wspolczynnikiPCA[9][5]+znormalizowana.MAD*wspolczynnikiPCA[10][5];
	wczytanaProbkaPCA.PC7=znormalizowana.srednia*wspolczynnikiPCA[0][6]+znormalizowana.odchylenie*wspolczynnikiPCA[1][6]+znormalizowana.NN50_1*wspolczynnikiPCA[2][6]+znormalizowana.NN50_2*wspolczynnikiPCA[3][6]+znormalizowana.pNN50_1*wspolczynnikiPCA[4][6]+znormalizowana.pNN50_2*wspolczynnikiPCA[5][6]+znormalizowana.SDSD*wspolczynnikiPCA[6][6]+znormalizowana.RMSSD*wspolczynnikiPCA[7][6]+znormalizowana.mediana*wspolczynnikiPCA[8][6]+znormalizowana.IQR*wspolczynnikiPCA[9][6]+znormalizowana.MAD*wspolczynnikiPCA[10][6];
	wczytanaProbkaPCA.PC8=znormalizowana.srednia*wspolczynnikiPCA[0][7]+znormalizowana.odchylenie*wspolczynnikiPCA[1][7]+znormalizowana.NN50_1*wspolczynnikiPCA[2][7]+znormalizowana.NN50_2*wspolczynnikiPCA[3][7]+znormalizowana.pNN50_1*wspolczynnikiPCA[4][7]+znormalizowana.pNN50_2*wspolczynnikiPCA[5][7]+znormalizowana.SDSD*wspolczynnikiPCA[6][7]+znormalizowana.RMSSD*wspolczynnikiPCA[7][7]+znormalizowana.mediana*wspolczynnikiPCA[8][7]+znormalizowana.IQR*wspolczynnikiPCA[9][7]+znormalizowana.MAD*wspolczynnikiPCA[10][7];
	wczytanaProbkaPCA.PC9=znormalizowana.srednia*wspolczynnikiPCA[0][8]+znormalizowana.odchylenie*wspolczynnikiPCA[1][8]+znormalizowana.NN50_1*wspolczynnikiPCA[2][8]+znormalizowana.NN50_2*wspolczynnikiPCA[3][8]+znormalizowana.pNN50_1*wspolczynnikiPCA[4][8]+znormalizowana.pNN50_2*wspolczynnikiPCA[5][8]+znormalizowana.SDSD*wspolczynnikiPCA[6][8]+znormalizowana.RMSSD*wspolczynnikiPCA[7][8]+znormalizowana.mediana*wspolczynnikiPCA[8][8]+znormalizowana.IQR*wspolczynnikiPCA[9][8]+znormalizowana.MAD*wspolczynnikiPCA[10][8];
	wczytanaProbkaPCA.PC10=znormalizowana.srednia*wspolczynnikiPCA[0][9]+znormalizowana.odchylenie*wspolczynnikiPCA[1][9]+znormalizowana.NN50_1*wspolczynnikiPCA[2][9]+znormalizowana.NN50_2*wspolczynnikiPCA[3][9]+znormalizowana.pNN50_1*wspolczynnikiPCA[4][9]+znormalizowana.pNN50_2*wspolczynnikiPCA[5][9]+znormalizowana.SDSD*wspolczynnikiPCA[6][9]+znormalizowana.RMSSD*wspolczynnikiPCA[7][9]+znormalizowana.mediana*wspolczynnikiPCA[8][0]+znormalizowana.IQR*wspolczynnikiPCA[9][9]+znormalizowana.MAD*wspolczynnikiPCA[10][9];
	wczytanaProbkaPCA.PC11=znormalizowana.srednia*wspolczynnikiPCA[0][10]+znormalizowana.odchylenie*wspolczynnikiPCA[1][10]+znormalizowana.NN50_1*wspolczynnikiPCA[2][10]+znormalizowana.NN50_2*wspolczynnikiPCA[3][10]+znormalizowana.pNN50_1*wspolczynnikiPCA[4][10]+znormalizowana.pNN50_2*wspolczynnikiPCA[5][10]+znormalizowana.SDSD*wspolczynnikiPCA[6][10]+znormalizowana.RMSSD*wspolczynnikiPCA[7][10]+znormalizowana.mediana*wspolczynnikiPCA[8][10]+znormalizowana.IQR*wspolczynnikiPCA[9][10]+znormalizowana.MAD*wspolczynnikiPCA[10][10];

	return wczytanaProbkaPCA;

}


//zmeinna metoda pobierana pewnie od gui albo in/out - akutalnie int przerobcie na co uwazacie 1 - euklidesowa 2 - manhattan 3 -czebyszewa

char SleepApnea::klasyfikuj(probkaPCA analizowanaProbka, probkaPCA tablicaProbekUczacych[16841], int metoda)
{

		char rodzaj;
		float tablicaOdleglosci[2][20]; //inicjalzowanie talbicy do szukania nejmniejszych odleglosci
		
		for(int z=0;z<20;z++)
		{
			
			tablicaOdleglosci[0][z]=1000000;
			tablicaOdleglosci[1][z]=0;
			
		}

		float odleglosc;
		for (int k=0;k<16841; k++)
		{
		
			switch(metoda)
			{
			
				case 1:
				
					odleglosc=sqrt(pow((analizowanaProbka.PC1-tablicaProbekUczacych[k].PC1),2)+pow((analizowanaProbka.PC2-tablicaProbekUczacych[k].PC2),2)+pow((analizowanaProbka.PC3-tablicaProbekUczacych[k].PC3),2)+pow((analizowanaProbka.PC4-tablicaProbekUczacych[k].PC4),2)+pow((analizowanaProbka.PC5-tablicaProbekUczacych[k].PC5),2)+pow((analizowanaProbka.PC6-tablicaProbekUczacych[k].PC6),2)+pow((analizowanaProbka.PC7-tablicaProbekUczacych[k].PC7),2)+pow((analizowanaProbka.PC8-tablicaProbekUczacych[k].PC8),2)+pow((analizowanaProbka.PC9-tablicaProbekUczacych[k].PC9),2)+pow((analizowanaProbka.PC10-tablicaProbekUczacych[k].PC10),2)+pow((analizowanaProbka.PC11-tablicaProbekUczacych[k].PC11),2));
					najmniejszeOdleglosci(tablicaOdleglosci, odleglosc, k);
					break;
				
				case 2:
				
					odleglosc=fabs(analizowanaProbka.PC1-tablicaProbekUczacych[k].PC1)+fabs(analizowanaProbka.PC2-tablicaProbekUczacych[k].PC2)+fabs(analizowanaProbka.PC3-tablicaProbekUczacych[k].PC3)+fabs(analizowanaProbka.PC4-tablicaProbekUczacych[k].PC4)+fabs(analizowanaProbka.PC5-tablicaProbekUczacych[k].PC5)+fabs(analizowanaProbka.PC6-tablicaProbekUczacych[k].PC6)+fabs(analizowanaProbka.PC7-tablicaProbekUczacych[k].PC7)+fabs(analizowanaProbka.PC8-tablicaProbekUczacych[k].PC8)+fabs(analizowanaProbka.PC9-tablicaProbekUczacych[k].PC9)+fabs(analizowanaProbka.PC10-tablicaProbekUczacych[k].PC10)+fabs(analizowanaProbka.PC11-tablicaProbekUczacych[k].PC11);
					najmniejszeOdleglosci(tablicaOdleglosci, odleglosc, k);
					break;
				
				case 3:
			
					float odlegloscCzybyszew[11];


					odlegloscCzybyszew[0]=fabs(analizowanaProbka.PC1-tablicaProbekUczacych[k].PC1);
					odlegloscCzybyszew[1]=fabs(analizowanaProbka.PC2-tablicaProbekUczacych[k].PC2);
					odlegloscCzybyszew[2]=fabs(analizowanaProbka.PC3-tablicaProbekUczacych[k].PC3);
					odlegloscCzybyszew[3]=fabs(analizowanaProbka.PC4-tablicaProbekUczacych[k].PC4);
					odlegloscCzybyszew[4]=fabs(analizowanaProbka.PC5-tablicaProbekUczacych[k].PC5);
					odlegloscCzybyszew[5]=fabs(analizowanaProbka.PC6-tablicaProbekUczacych[k].PC6);
					odlegloscCzybyszew[6]=fabs(analizowanaProbka.PC7-tablicaProbekUczacych[k].PC7);
					odlegloscCzybyszew[7]=fabs(analizowanaProbka.PC8-tablicaProbekUczacych[k].PC8);
					odlegloscCzybyszew[8]=fabs(analizowanaProbka.PC9-tablicaProbekUczacych[k].PC9);
					odlegloscCzybyszew[9]=fabs(analizowanaProbka.PC10-tablicaProbekUczacych[k].PC10);
					odlegloscCzybyszew[10]=fabs(analizowanaProbka.PC11-tablicaProbekUczacych[k].PC11);
				
					odleglosc=odlegloscCzybyszew[0];
				
					for (int y=1;y<11;y++){
					
					
						if (odlegloscCzybyszew[y]>odleglosc){
					
							odleglosc=odlegloscCzybyszew[y];
					
						}
					
					
					}
					
					
				najmniejszeOdleglosci(tablicaOdleglosci, odleglosc, k);
	
				break;					
				}
			}
			
			//badanie jakich sasiadow ma wiecej
			int sasiedziZBezdechem=0;
			int sasiedzBezBezdechu=0;
				
			for(int l=0; l<20; l++){
					
					if(tablicaProbekUczacych[(int)tablicaOdleglosci[1][l]].typ=='A'){
					
						sasiedziZBezdechem++;
					
					}
				
					else{
					
						sasiedzBezBezdechu++;
					}
				}


				if(sasiedziZBezdechem==sasiedzBezBezdechu)	{		
					
					analizowanaProbka.typ=tablicaProbekUczacych[(int)tablicaOdleglosci[1][0]].typ;
				
				}
			
			
				else if(sasiedziZBezdechem<sasiedzBezBezdechu){
			
			
					rodzaj='A';
			
				}
		
				else{
			
					rodzaj='N';
			
				}
		return rodzaj;
					
}
		
		
vector <int> SleepApnea::zamianaNaInt(vector<probkaPCA> analizowaneProbki, int liczbaProbek)
{

	vector <int> ostatni;

	for (int k=0;k<liczbaProbek;k++){

		if (analizowaneProbki[k].typ=='A')//wykrycie bezdechu
			ostatni.push_back(1);
		else if (analizowaneProbki[k].typ=='N')//brak bezdechu
			ostatni.push_back(0);
		else 
			ostatni.push_back(-1);// pozosta³e przypadki czyli niesklasyfikowane

	}
	return ostatni;
}

//  Jak pobierac dane z obiektu resultsKeeper

SleepApneaResult* SleepApnea :: Rampl(int fs, vector<float> R_peaks_in, int size_Rpeaks, int metoda)
{
	probkaPCA tablicaUczacych[16841];
	float wspolczynnikiDoPCA[11][11];
	float srednieDoPCA[11];
	float odchyleniaDoPCA[11];
	int i;

	wczytywanie (tablicaUczacych,wspolczynnikiDoPCA, srednieDoPCA, odchyleniaDoPCA);
	vector <float> interwalyRR =RR(R_peaks_in,size_Rpeaks,fs);
	int liczbaMinut= iloscMinut(interwalyRR, size_Rpeaks);
	vector < int > miejscaPodzialu=punktyPodzialu(interwalyRR, liczbaMinut);
	vector < probkaWczytana > tablicaWczyt = inicjowanieProbek (liczbaMinut);

	//obliczanie parametrow kazdej probki
	for ( i=0; i<liczbaMinut; i++){

		int liczbaUderzen=miejscaPodzialu[i+1]-miejscaPodzialu[i];	//ilosc Rpeakow w danej minucie
		

		//stwierdzenie o braku mozliwosci klasyfikacji ze wzgledu na za mala ilosc peakow R
		if (liczbaUderzen<2)
			{
					tablicaWczyt[i].typ='U';
					continue;
			}

		int liczbaAnalizowanych=liczbaUderzen;


		//stwierdzenie o braku mozliwosci klasyfikacji ze wzgledu na za mala ilosc peakow R miesczacyh sie w normie
		for(int k=miejscaPodzialu[i];k<miejscaPodzialu[i+1];k++){

			if(interwalyRR[k]<0.5||interwalyRR[k]>1.5){
				liczbaAnalizowanych--;
			}

		}

		if (liczbaAnalizowanych<2){
			tablicaWczyt[i].typ='U';
			continue;
		}


		vector < float > tablicaAnaliz = wyborAnalizowanych(miejscaPodzialu[i], miejscaPodzialu[i+1], interwalyRR);

		vector < float > akutalneRozniceRR = rozniceRR(liczbaAnalizowanych,  tablicaAnaliz);

		vector < float > posortowanaAnalizowanych =sortuj(liczbaAnalizowanych, tablicaAnaliz) ;


		tablicaWczyt[i].srednia=obliczSrednia(liczbaAnalizowanych,tablicaAnaliz);
		tablicaWczyt[i].odchylenie=obliczOdchylenie(liczbaAnalizowanych,tablicaAnaliz,tablicaWczyt[i].srednia);
		tablicaWczyt[i].NN50_1=obliczNN50_1(liczbaAnalizowanych, akutalneRozniceRR);
		tablicaWczyt[i].NN50_2=obliczNN50_2(liczbaAnalizowanych, akutalneRozniceRR);
		tablicaWczyt[i].pNN50_1=obliczNN50_1(liczbaAnalizowanych, akutalneRozniceRR)/liczbaAnalizowanych;
		tablicaWczyt[i].pNN50_2=obliczNN50_2(liczbaAnalizowanych, akutalneRozniceRR)/liczbaAnalizowanych;
		tablicaWczyt[i].SDSD=obliczSDSD(liczbaAnalizowanych,akutalneRozniceRR);
		tablicaWczyt[i].RMSSD=obliczRMSSD(liczbaAnalizowanych,akutalneRozniceRR);
		tablicaWczyt[i].mediana=obliczMediane(liczbaAnalizowanych, posortowanaAnalizowanych);
		tablicaWczyt[i].IQR=obliczIQR(liczbaAnalizowanych, posortowanaAnalizowanych);
		tablicaWczyt[i].MAD=obliczMAD(liczbaAnalizowanych, tablicaAnaliz, tablicaWczyt[i].srednia);
	}
	//koniec obliczania parametrow kazdej probki

	vector < probkaWczytana > probkiZnormalizowane;
	vector < probkaPCA > wczytaneProbkiPCA;


	for ( i=0; i<liczbaMinut; i++){
	
		probkiZnormalizowane.push_back(probkaWczytana());
				
		if (tablicaWczyt[i].typ=='U'){	
			continue;
		}

		probkiZnormalizowane[i]=normalizacja(tablicaWczyt[i], srednieDoPCA, odchyleniaDoPCA);

	}


	for ( i=0; i<liczbaMinut; i++){
	
		wczytaneProbkiPCA.push_back(probkaPCA());
				
		if (tablicaWczyt[i].typ=='U'){	
			continue;
		}
		
		wczytaneProbkiPCA[i]=rzutowaniePCA(probkiZnormalizowane[i], wspolczynnikiDoPCA);

	}

	for (i=0; i<liczbaMinut;i++){


		if (tablicaWczyt[i].typ=='U')
		
		{
			wczytaneProbkiPCA[i].typ='U';
			continue;
		}

		wczytaneProbkiPCA[i].typ=klasyfikuj(wczytaneProbkiPCA[i],  tablicaUczacych,  metoda);

	}

	vector <int> wynik=zamianaNaInt(wczytaneProbkiPCA, liczbaMinut); //ponoc lepiej pracowaæ n atym dla wizulaizacji

// Zapisywanie do wektora
	vector<int> result;
	for(int i = 0; i < liczbaMinut; i++ ) result.push_back(wynik[i]);
	
	vector<int> dres;
	int roz=result.size();

	for(int i=0; i<roz;i++)
	{
		if(i==0)			dres.push_back(result[0]);
		else if(i==roz-1)	dres.push_back(result[roz-1]*-1);
		else				dres.push_back(result[i]-result[i-1]);
	}

	vector<string> NrEpizodu;
	vector<double> PoczEpizo;
	vector<double> KoniEpizo;

	
	for(int i=0, a=1; i<roz;i++)
	{
		if(dres[i]==-1)		KoniEpizo.push_back(floor(i/60)+(i%60)/100);
		else if(dres[i]==1)	
		{
			PoczEpizo.push_back(floor(i/60)+(i%60)/100);
			NrEpizodu.push_back(to_string(a));
			a=a++;
		}
	}
	if(NrEpizodu.size()==0)
	{
		KoniEpizo.push_back( 0 );
		PoczEpizo.push_back( 0 );
		NrEpizodu.push_back("0");
	}
	/*
	map<string,vector<double>> ResMap;
	vector<double> ResVal;
	vector<double> ResXbeg;
	vector<double> ResXend;
	unsigned roz=result.size();
	
	for(unsigned i=0;i<roz;i++)
	{
		ResVal.push_back(result[i]);
		ResXbeg.push_back(i);
		ResXend.push_back(i+1);
	}
	ResMap["values"]=ResVal;
	ResMap["start_time"]=ResXbeg;
	ResMap["end_time"]=ResXend;
	*/

	SleepApneaResult res = SleepApneaResult();
	res.setResult(NrEpizodu,PoczEpizo,KoniEpizo);
	return res.getResult();
}


SleepApneaResult* SleepApnea :: compute(ResultKeeper* rkp) {
	
	//int fs=rkp->getInput()->GetFs();
	int fs=360;
	vector<unsigned int> uintR_peaks_in =rkp->getRPeaks()->getRPeaks();
	vector<float> R_peaks_in(uintR_peaks_in.begin(),uintR_peaks_in.end());
	int size_Rpeaks =R_peaks_in.size();

	int metoda=1;															  //  z UI rkp->;                                                              

	return Rampl( fs , R_peaks_in, size_Rpeaks ,metoda);
}

