#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <fstream>
#include <map>
#include <cmath>
#include <stdlib.h> 
#include <vector>
//#using<system.dll>

//using namespace System;
//using namespace System::IO;



//using namespace std;

struct probkaPCA {
    float PC1;
    float PC2;
    //float;//'odchylenie','sNN50_1','sNN50_2','pNN50_1','pNN50_2','SDSD', 'RMSSD', 'mediana','IQR','MAD'
    float PC3;
    float PC4;
    float PC5;
    float PC6;
    float PC7;
    float PC8;
    float PC9;
    float PC10;
    float PC11;
    char typ;
};


struct probkaWczytana {
    float srednia;
    float odchylenie;
    //float;//'odchylenie','sNN50_1','sNN50_2','pNN50_1','pNN50_2','SDSD', 'RMSSD', 'mediana','IQR','MAD'
    float NN50_1;
    float NN50_2;
    float pNN50_1;
    float pNN50_2;
    float SDSD;
    float RMSSD;
    float mediana;
    float IQR;
    float MAD;
    char typ;
};



void najmniejszeOdleglosci( float tab[2][20], float odlegl, float numerProbki )

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


int main()
{

	
std::ifstream in("danePCAProbek.txt");

probkaPCA tablicaProbekUczacych[16841]; 
int i; 
int k;

for ( i=0; i < 16841; i++){
in >> tablicaProbekUczacych[i].PC1 >> tablicaProbekUczacych[i].PC2 >> tablicaProbekUczacych[i].PC3 >>
tablicaProbekUczacych[i].PC4 >> tablicaProbekUczacych[i].PC5 >> tablicaProbekUczacych[i].PC6>>
tablicaProbekUczacych[i].PC7 >> tablicaProbekUczacych[i].PC8 >> tablicaProbekUczacych[i].PC9>>
tablicaProbekUczacych[i].PC10 >> tablicaProbekUczacych[i].PC11;
}




	std::ifstream etyk("etykiety.txt");

for ( i=0; i < 16841; i++){
	
	etyk >> tablicaProbekUczacych[i].typ;
}


std::map <int, char> etykietyBadane;	

int iter=0;

char etykietowy[30];
std::cout <<"Podaj nazwe pliku z etykietami testowymi (wraz z rozszerzeniem)\n";
std::cin >>etykietowy;
char probkowy[30];
std::cout <<"Podaj nazwe pliku z interwa³ami testowymi(wraz z rozszerzeniem)\n";
std::cin >>probkowy;

//std::ifstream etyk2("etykiety8.txt");

std::ifstream etyk2(etykietowy);
while( !etyk2.eof() ) {
    etyk2 >> etykietyBadane[iter];
    iter++;
}


//for ( i=0;i< 400;i++) {

//	 std::cout << etykietyBadane[i] << "\n";

//}


//for ( i=0;i< 10;i++) {
 /*           std::cout << tablicaProbekUczacych[i].PC1<<" ";
            std::cout << tablicaProbekUczacych[i].PC2<<" ";
            std::cout << tablicaProbekUczacych[i].PC3<<" ";
            std::cout << tablicaProbekUczacych[i].PC11 << " ";
      std::cout << tablicaProbekUczacych[i].PC6 << " ";
      std::cout << tablicaProbekUczacych[i].typ << "\n";
        }*/
        
        
        
	
std::ifstream PCA("PCAWspolczynniki.txt");	

float wspolczynnikiPCA[11][11];
	for ( i=0; i < 11; i++){
	for (k=0; k < 11; k++){
	
	PCA >> wspolczynnikiPCA[k][i];
}
}
	
	/*for ( i=0;i< 10;i++) {
            std::cout << wspolczynnikiPCA[i][0]<<" ";
}*/


std::ifstream plikSrednie("srednie.txt");	
float srednie[11];
	for ( i=0; i < 11; i++){
		
	plikSrednie >> srednie[i];
}





std::ifstream plikOdchylenia("odchylenia.txt");	
float odchylenia[11];
	for ( i=0; i < 11; i++){
		
	plikOdchylenia >> odchylenia[i];
}

	
//	for ( i=0;i< 11;i++) {
//            std::cout << odchylenia[i]<<" ";
//}



	std::map <int, float> interwalyRR;	
	
	int iterator=0;
std::ifstream interwaly(probkowy);
while( !interwaly.eof() ) {
    interwaly >> interwalyRR[iterator];
    iterator++;
}
	int liczbaUderzen=iterator;

//for ( i=1;i< 2000;i++) {
//            
//      std::cout << interwalyRR[i]<< "\n";
//        }


	float czasPomiaru=0;


for(i=0;i<liczbaUderzen;i++){

czasPomiaru=czasPomiaru+interwalyRR[i];
}

//std::cout << czasPomiaru;



int liczbaBadanychProbek=floor(czasPomiaru/60);
//std::cout << liczbaBadanychProbek;

std::vector < int > punktyPodzialu;
 punktyPodzialu.push_back( 0 );
//int punktyPodzialu[liczbaBadanychProbek+1];
//punktyPodzialu[0]=0;
//
float sumaCzasow=0;
int wskaznikPodzialu=0;
//
for (i=0; i<liczbaBadanychProbek; i++){

while (sumaCzasow<(60*(i+1))){

	sumaCzasow=sumaCzasow+interwalyRR[wskaznikPodzialu];
	wskaznikPodzialu++;
	
}
//punktyPodzialu[i+1]=wskaznikPodzialu;
 punktyPodzialu.push_back( wskaznikPodzialu );

}



//for( int i = 0; i < punktyPodzialu.size(); i++ )
//    {
//        std::cout << punktyPodzialu[ i ] << std::endl;
//    }


std::vector < probkaWczytana > tablicaWczytanych;


for(i=0;i<liczbaBadanychProbek;i++){


int liczbaUderzen=punktyPodzialu[i+1]-punktyPodzialu[i];
//liczenie sredniej
 tablicaWczytanych.push_back(probkaWczytana());

if (liczbaUderzen<2)
{
	
	tablicaWczytanych[i].typ='U';
	continue;
}



int liczbaAnalizowanych=liczbaUderzen;
for(k=punktyPodzialu[i];k<punktyPodzialu[i+1];k++){

if(interwalyRR[k]<0.5||interwalyRR[k]>1.5)
liczbaAnalizowanych--;
}

if (liczbaAnalizowanych<2)
{
	tablicaWczytanych[i].typ='U';
	continue;
}

////float tablicaAnalizowanych[liczbaAnalizowanych];

std::vector < float > tablicaAnalizowanych;


//float* tablicaAnalizowanych;
//tablicaAnalizowanych = (float*) malloc (liczbaAnalizowanych);
iterator=0;

for(k=punktyPodzialu[i];k<punktyPodzialu[i+1];k++){

if(!(interwalyRR[k]<0.5||interwalyRR[k]>1.5))

tablicaAnalizowanych.push_back(interwalyRR[k]);
//std::cout << "\n"<<tablicaAnalizowanych[iterator];

iterator++;
//std::cout << "\n"<<tablicaAnalizowanych[iterator];
}
//free (tablicaAnalizowanych);


float sumaDoSredniej=0;
for(k=0;k<liczbaAnalizowanych;k++)
{
	sumaDoSredniej=sumaDoSredniej+tablicaAnalizowanych[k];
	
}

float aktualnaSrednia=sumaDoSredniej/liczbaAnalizowanych;

//std::cout << "\n"<<aktualnaSrednia;


tablicaWczytanych[i].srednia=aktualnaSrednia;
//std::cout << "\n"<<tablicaWczytanych[i].srednia;
//}

float aktualneOdchylenie;
float sumaDoOdchylenia=0;

for (k=0;k<liczbaAnalizowanych;k++){
	
	sumaDoOdchylenia=sumaDoOdchylenia+pow((aktualnaSrednia-tablicaAnalizowanych[k]),2);
	
}
aktualneOdchylenie=sqrt(sumaDoOdchylenia/liczbaAnalizowanych);

tablicaWczytanych[i].odchylenie=aktualneOdchylenie;




////float rozniceRR[liczbaAnalizowanych-1];
std::vector < float > rozniceRR;



for(k=0;k<(liczbaAnalizowanych-1);k++){
	float roznica;
	roznica=tablicaAnalizowanych[k+1]-tablicaAnalizowanych[k];
	
	rozniceRR.push_back(roznica);
}


float aktualneNN50_1=0;
float aktualneNN50_2=0;
float aktualnepNN50_1;
float aktualnepNN50_2;


for(k=0;k<liczbaAnalizowanych-1;k++){


if(rozniceRR[k]>0.05)
{
	aktualneNN50_1++;
}
}

for(k=0;k<liczbaAnalizowanych-1;k++){


if(rozniceRR[k]<-0.05)
{
	aktualneNN50_2++;
}
}



aktualnepNN50_1=aktualneNN50_1/(liczbaAnalizowanych-1);
aktualnepNN50_2=aktualneNN50_2/(liczbaAnalizowanych-1);

tablicaWczytanych[i].NN50_1=aktualneNN50_1;
tablicaWczytanych[i].NN50_2=aktualneNN50_2;
tablicaWczytanych[i].pNN50_1=aktualnepNN50_1;
tablicaWczytanych[i].pNN50_2=aktualnepNN50_2;



float sumaDoSDSD=0;
float sumaDoSDSD2=0;
float sredniaDoSDSD;
float aktualneSDSD;

for(k=0;k<liczbaAnalizowanych-1;k++){

sumaDoSDSD=sumaDoSDSD+rozniceRR[k];

}
sredniaDoSDSD=sumaDoSDSD/(liczbaAnalizowanych-1);

for (k=0;k<liczbaAnalizowanych-1;k++){
	
	sumaDoSDSD2=sumaDoSDSD2+pow((sredniaDoSDSD-rozniceRR[k]),2);
	
}
aktualneSDSD=sqrt(sumaDoSDSD2/(liczbaAnalizowanych-1));
tablicaWczytanych[i].SDSD=aktualneSDSD;



float aktualneRMSSD;
float sumaDoRMSSD=0;

for (k=0;k<liczbaAnalizowanych-1;k++){
	
	sumaDoRMSSD=sumaDoRMSSD+pow((rozniceRR[k]),2);
	
}

aktualneRMSSD=sqrt(sumaDoRMSSD/(liczbaAnalizowanych-1));
tablicaWczytanych[i].RMSSD=aktualneRMSSD;


float aktualnaMediana;


//float sortowanaAnalizowanych[liczbaAnalizowanych];
std::vector < float > sortowanaAnalizowanych;


for(k=0;k<liczbaAnalizowanych;k++){
	
	sortowanaAnalizowanych.push_back(tablicaAnalizowanych[k]);
	
}


float pomocnicza;
int j;

for(j=0; j<liczbaAnalizowanych;j++){

 for ( k = 0; k < liczbaAnalizowanych-1-j; k++) {
                if (sortowanaAnalizowanych[k] > sortowanaAnalizowanych[k+1]) {
                    
					pomocnicza=sortowanaAnalizowanych[k];
					sortowanaAnalizowanych[k]=sortowanaAnalizowanych[k+1];
					sortowanaAnalizowanych[k+1]=pomocnicza;




            }





}


}



if(liczbaAnalizowanych%2==1){
	
	aktualnaMediana=sortowanaAnalizowanych[(liczbaAnalizowanych-1)/2];
}
else
{
	aktualnaMediana=(sortowanaAnalizowanych[liczbaAnalizowanych/2]+sortowanaAnalizowanych[(liczbaAnalizowanych/2)+1])/2;
}
tablicaWczytanych[i].mediana=aktualnaMediana;


float kwartyl1;
float kwartyl3;
float akutalneIQR;

if(liczbaAnalizowanych%4==0){
kwartyl1=0.75*sortowanaAnalizowanych[(liczbaAnalizowanych/4)-1]+0.25*sortowanaAnalizowanych[(liczbaAnalizowanych/4)];
kwartyl3=0.25*sortowanaAnalizowanych[(liczbaAnalizowanych*3/4)-1]+0.75*sortowanaAnalizowanych[(liczbaAnalizowanych*3/4)];

}

else if (liczbaAnalizowanych%4==1){
kwartyl1=0.5*sortowanaAnalizowanych[(int)((floor(liczbaAnalizowanych/4))-1)]+0.5*sortowanaAnalizowanych[(int)(floor(liczbaAnalizowanych/4))];
kwartyl3=0.5*sortowanaAnalizowanych[(int)((ceil(liczbaAnalizowanych*3/4)-1))]+0.5*sortowanaAnalizowanych[(int)(ceil(liczbaAnalizowanych*3/4))];

}

else if (liczbaAnalizowanych%4==2){
	
	if(liczbaAnalizowanych==2){
		kwartyl1=0.75*sortowanaAnalizowanych[0];
		kwartyl3=1.25*sortowanaAnalizowanych[1];
	}

	else{
		kwartyl1=0.25*sortowanaAnalizowanych[int((floor(liczbaAnalizowanych/4))-1)]+0.75*sortowanaAnalizowanych[int(floor(liczbaAnalizowanych/4))];
		kwartyl3=0.75*sortowanaAnalizowanych[int((ceil(liczbaAnalizowanych*3/4))-1)]+0.25*sortowanaAnalizowanych[int(ceil(liczbaAnalizowanych*3/4))];
	}	
}
else {
	
	if(liczbaAnalizowanych==3){
		kwartyl1=sortowanaAnalizowanych[0];
		kwartyl3=sortowanaAnalizowanych[2];
	}

	else{
		kwartyl1=sortowanaAnalizowanych[int(floor(liczbaAnalizowanych/4))];
		kwartyl3=sortowanaAnalizowanych[int(ceil(liczbaAnalizowanych*3/4))];
	}	
	

}

akutalneIQR=kwartyl3-kwartyl1;
tablicaWczytanych[i].IQR=akutalneIQR;



float akutalneMAD;
float sumaDoMAD=0;

for(k=0;k<liczbaAnalizowanych; k++)

{	

sumaDoMAD=sumaDoMAD+fabs(tablicaAnalizowanych[k]-aktualnaSrednia);

}

akutalneMAD=sumaDoMAD/liczbaAnalizowanych;
tablicaWczytanych[i].MAD=akutalneMAD;


//std::cout << "\n"<<tablicaWczytanych[i].MAD;
}

std::vector < probkaWczytana > probkiZnormalizowane;


//probkaWczytana probkiZnormalizowane[liczbaBadanychProbek];
//
//
for(i=0;i<liczbaBadanychProbek;i++){
 probkiZnormalizowane.push_back(probkaWczytana());


	if (tablicaWczytanych[i].typ=='U')
	{
	
	continue;
	}
	    //float;//'odchylenie','NN50_1','NN50_2','pNN50_1','pNN50_2','SDSD', 'RMSSD', 'mediana','IQR','MAD'

	
	probkiZnormalizowane[i].srednia=(tablicaWczytanych[i].srednia-srednie[0])/odchylenia[0];
	probkiZnormalizowane[i].odchylenie=(tablicaWczytanych[i].odchylenie-srednie[1])/odchylenia[1];
	probkiZnormalizowane[i].NN50_1=(tablicaWczytanych[i].NN50_1-srednie[2])/odchylenia[2];
	probkiZnormalizowane[i].NN50_2=(tablicaWczytanych[i].NN50_2-srednie[3])/odchylenia[3];
	probkiZnormalizowane[i].pNN50_1=(tablicaWczytanych[i].pNN50_1-srednie[4])/odchylenia[4];
	probkiZnormalizowane[i].pNN50_2=(tablicaWczytanych[i].pNN50_2-srednie[5])/odchylenia[5];
	probkiZnormalizowane[i].SDSD=(tablicaWczytanych[i].SDSD-srednie[6])/odchylenia[6];
	probkiZnormalizowane[i].RMSSD=(tablicaWczytanych[i].RMSSD-srednie[7])/odchylenia[7];
	probkiZnormalizowane[i].mediana=(tablicaWczytanych[i].mediana-srednie[8])/odchylenia[8];
	probkiZnormalizowane[i].IQR=(tablicaWczytanych[i].IQR-srednie[9])/odchylenia[9];
	probkiZnormalizowane[i].MAD=(tablicaWczytanych[i].MAD-srednie[10])/odchylenia[10];
}



std::vector < probkaPCA > wczytaneProbkiPCA;

//
//probkaPCA wczytaneProbkiPCA[liczbaBadanychProbek];
//
for(i=0;i<liczbaBadanychProbek;i++){

	wczytaneProbkiPCA.push_back(probkaPCA());

	if (tablicaWczytanych[i].typ=='U')
	{
	
	continue;
	}	
	
	//for(k=0;k<11;k++){
	
	wczytaneProbkiPCA[i].PC1=probkiZnormalizowane[i].srednia*wspolczynnikiPCA[0][0]+probkiZnormalizowane[i].odchylenie*wspolczynnikiPCA[1][0]+probkiZnormalizowane[i].NN50_1*wspolczynnikiPCA[2][0]+probkiZnormalizowane[i].NN50_2*wspolczynnikiPCA[3][0]+probkiZnormalizowane[i].pNN50_1*wspolczynnikiPCA[4][0]+probkiZnormalizowane[i].pNN50_2*wspolczynnikiPCA[5][0]+probkiZnormalizowane[i].SDSD*wspolczynnikiPCA[6][0]+probkiZnormalizowane[i].RMSSD*wspolczynnikiPCA[7][0]+probkiZnormalizowane[i].mediana*wspolczynnikiPCA[8][0]+probkiZnormalizowane[i].IQR*wspolczynnikiPCA[9][0]+probkiZnormalizowane[i].MAD*wspolczynnikiPCA[10][0];
	wczytaneProbkiPCA[i].PC2=probkiZnormalizowane[i].srednia*wspolczynnikiPCA[0][1]+probkiZnormalizowane[i].odchylenie*wspolczynnikiPCA[1][1]+probkiZnormalizowane[i].NN50_1*wspolczynnikiPCA[2][1]+probkiZnormalizowane[i].NN50_2*wspolczynnikiPCA[3][1]+probkiZnormalizowane[i].pNN50_1*wspolczynnikiPCA[4][1]+probkiZnormalizowane[i].pNN50_2*wspolczynnikiPCA[5][1]+probkiZnormalizowane[i].SDSD*wspolczynnikiPCA[6][1]+probkiZnormalizowane[i].RMSSD*wspolczynnikiPCA[7][1]+probkiZnormalizowane[i].mediana*wspolczynnikiPCA[8][1]+probkiZnormalizowane[i].IQR*wspolczynnikiPCA[9][1]+probkiZnormalizowane[i].MAD*wspolczynnikiPCA[10][1];
	wczytaneProbkiPCA[i].PC3=probkiZnormalizowane[i].srednia*wspolczynnikiPCA[0][2]+probkiZnormalizowane[i].odchylenie*wspolczynnikiPCA[1][2]+probkiZnormalizowane[i].NN50_1*wspolczynnikiPCA[2][2]+probkiZnormalizowane[i].NN50_2*wspolczynnikiPCA[3][2]+probkiZnormalizowane[i].pNN50_1*wspolczynnikiPCA[4][2]+probkiZnormalizowane[i].pNN50_2*wspolczynnikiPCA[5][2]+probkiZnormalizowane[i].SDSD*wspolczynnikiPCA[6][2]+probkiZnormalizowane[i].RMSSD*wspolczynnikiPCA[7][2]+probkiZnormalizowane[i].mediana*wspolczynnikiPCA[8][2]+probkiZnormalizowane[i].IQR*wspolczynnikiPCA[9][2]+probkiZnormalizowane[i].MAD*wspolczynnikiPCA[10][2];
	wczytaneProbkiPCA[i].PC4=probkiZnormalizowane[i].srednia*wspolczynnikiPCA[0][3]+probkiZnormalizowane[i].odchylenie*wspolczynnikiPCA[1][3]+probkiZnormalizowane[i].NN50_1*wspolczynnikiPCA[2][3]+probkiZnormalizowane[i].NN50_2*wspolczynnikiPCA[3][3]+probkiZnormalizowane[i].pNN50_1*wspolczynnikiPCA[4][3]+probkiZnormalizowane[i].pNN50_2*wspolczynnikiPCA[5][3]+probkiZnormalizowane[i].SDSD*wspolczynnikiPCA[6][3]+probkiZnormalizowane[i].RMSSD*wspolczynnikiPCA[7][3]+probkiZnormalizowane[i].mediana*wspolczynnikiPCA[8][3]+probkiZnormalizowane[i].IQR*wspolczynnikiPCA[9][3]+probkiZnormalizowane[i].MAD*wspolczynnikiPCA[10][3];
	wczytaneProbkiPCA[i].PC5=probkiZnormalizowane[i].srednia*wspolczynnikiPCA[0][4]+probkiZnormalizowane[i].odchylenie*wspolczynnikiPCA[1][4]+probkiZnormalizowane[i].NN50_1*wspolczynnikiPCA[2][4]+probkiZnormalizowane[i].NN50_2*wspolczynnikiPCA[3][4]+probkiZnormalizowane[i].pNN50_1*wspolczynnikiPCA[4][4]+probkiZnormalizowane[i].pNN50_2*wspolczynnikiPCA[5][4]+probkiZnormalizowane[i].SDSD*wspolczynnikiPCA[6][4]+probkiZnormalizowane[i].RMSSD*wspolczynnikiPCA[7][4]+probkiZnormalizowane[i].mediana*wspolczynnikiPCA[8][4]+probkiZnormalizowane[i].IQR*wspolczynnikiPCA[9][4]+probkiZnormalizowane[i].MAD*wspolczynnikiPCA[10][4];
	wczytaneProbkiPCA[i].PC6=probkiZnormalizowane[i].srednia*wspolczynnikiPCA[0][5]+probkiZnormalizowane[i].odchylenie*wspolczynnikiPCA[1][5]+probkiZnormalizowane[i].NN50_1*wspolczynnikiPCA[2][5]+probkiZnormalizowane[i].NN50_2*wspolczynnikiPCA[3][5]+probkiZnormalizowane[i].pNN50_1*wspolczynnikiPCA[4][5]+probkiZnormalizowane[i].pNN50_2*wspolczynnikiPCA[5][5]+probkiZnormalizowane[i].SDSD*wspolczynnikiPCA[6][5]+probkiZnormalizowane[i].RMSSD*wspolczynnikiPCA[7][5]+probkiZnormalizowane[i].mediana*wspolczynnikiPCA[8][5]+probkiZnormalizowane[i].IQR*wspolczynnikiPCA[9][5]+probkiZnormalizowane[i].MAD*wspolczynnikiPCA[10][5];
	wczytaneProbkiPCA[i].PC7=probkiZnormalizowane[i].srednia*wspolczynnikiPCA[0][6]+probkiZnormalizowane[i].odchylenie*wspolczynnikiPCA[1][6]+probkiZnormalizowane[i].NN50_1*wspolczynnikiPCA[2][6]+probkiZnormalizowane[i].NN50_2*wspolczynnikiPCA[3][6]+probkiZnormalizowane[i].pNN50_1*wspolczynnikiPCA[4][6]+probkiZnormalizowane[i].pNN50_2*wspolczynnikiPCA[5][6]+probkiZnormalizowane[i].SDSD*wspolczynnikiPCA[6][6]+probkiZnormalizowane[i].RMSSD*wspolczynnikiPCA[7][6]+probkiZnormalizowane[i].mediana*wspolczynnikiPCA[8][6]+probkiZnormalizowane[i].IQR*wspolczynnikiPCA[9][6]+probkiZnormalizowane[i].MAD*wspolczynnikiPCA[10][6];
	wczytaneProbkiPCA[i].PC8=probkiZnormalizowane[i].srednia*wspolczynnikiPCA[0][7]+probkiZnormalizowane[i].odchylenie*wspolczynnikiPCA[1][7]+probkiZnormalizowane[i].NN50_1*wspolczynnikiPCA[2][7]+probkiZnormalizowane[i].NN50_2*wspolczynnikiPCA[3][7]+probkiZnormalizowane[i].pNN50_1*wspolczynnikiPCA[4][7]+probkiZnormalizowane[i].pNN50_2*wspolczynnikiPCA[5][7]+probkiZnormalizowane[i].SDSD*wspolczynnikiPCA[6][7]+probkiZnormalizowane[i].RMSSD*wspolczynnikiPCA[7][7]+probkiZnormalizowane[i].mediana*wspolczynnikiPCA[8][7]+probkiZnormalizowane[i].IQR*wspolczynnikiPCA[9][7]+probkiZnormalizowane[i].MAD*wspolczynnikiPCA[10][7];
	wczytaneProbkiPCA[i].PC9=probkiZnormalizowane[i].srednia*wspolczynnikiPCA[0][8]+probkiZnormalizowane[i].odchylenie*wspolczynnikiPCA[1][8]+probkiZnormalizowane[i].NN50_1*wspolczynnikiPCA[2][8]+probkiZnormalizowane[i].NN50_2*wspolczynnikiPCA[3][8]+probkiZnormalizowane[i].pNN50_1*wspolczynnikiPCA[4][8]+probkiZnormalizowane[i].pNN50_2*wspolczynnikiPCA[5][8]+probkiZnormalizowane[i].SDSD*wspolczynnikiPCA[6][8]+probkiZnormalizowane[i].RMSSD*wspolczynnikiPCA[7][8]+probkiZnormalizowane[i].mediana*wspolczynnikiPCA[8][8]+probkiZnormalizowane[i].IQR*wspolczynnikiPCA[9][8]+probkiZnormalizowane[i].MAD*wspolczynnikiPCA[10][8];
	wczytaneProbkiPCA[i].PC10=probkiZnormalizowane[i].srednia*wspolczynnikiPCA[0][9]+probkiZnormalizowane[i].odchylenie*wspolczynnikiPCA[1][9]+probkiZnormalizowane[i].NN50_1*wspolczynnikiPCA[2][9]+probkiZnormalizowane[i].NN50_2*wspolczynnikiPCA[3][9]+probkiZnormalizowane[i].pNN50_1*wspolczynnikiPCA[4][9]+probkiZnormalizowane[i].pNN50_2*wspolczynnikiPCA[5][9]+probkiZnormalizowane[i].SDSD*wspolczynnikiPCA[6][9]+probkiZnormalizowane[i].RMSSD*wspolczynnikiPCA[7][9]+probkiZnormalizowane[i].mediana*wspolczynnikiPCA[8][0]+probkiZnormalizowane[i].IQR*wspolczynnikiPCA[9][9]+probkiZnormalizowane[i].MAD*wspolczynnikiPCA[10][9];
	wczytaneProbkiPCA[i].PC11=probkiZnormalizowane[i].srednia*wspolczynnikiPCA[0][10]+probkiZnormalizowane[i].odchylenie*wspolczynnikiPCA[1][10]+probkiZnormalizowane[i].NN50_1*wspolczynnikiPCA[2][10]+probkiZnormalizowane[i].NN50_2*wspolczynnikiPCA[3][10]+probkiZnormalizowane[i].pNN50_1*wspolczynnikiPCA[4][10]+probkiZnormalizowane[i].pNN50_2*wspolczynnikiPCA[5][10]+probkiZnormalizowane[i].SDSD*wspolczynnikiPCA[6][10]+probkiZnormalizowane[i].RMSSD*wspolczynnikiPCA[7][10]+probkiZnormalizowane[i].mediana*wspolczynnikiPCA[8][10]+probkiZnormalizowane[i].IQR*wspolczynnikiPCA[9][10]+probkiZnormalizowane[i].MAD*wspolczynnikiPCA[10][10];
	//}
	

}

int metoda;
        
std::cout<<"Podaj metryke jaka stosujesz: eukildesowa(1),Manhattan(2), Czebyszywa(3)\n";
std::cin>>metoda;

for (i=0; i<liczbaBadanychProbek;++i){


	if (tablicaWczytanych[i].typ=='U')
		
	{
	wczytaneProbkiPCA[i].typ='U';
	continue;
	}
		float tablicaOdleglosci[2][20];
		
		for(int z=0;z<20;z++){
			
			tablicaOdleglosci[0][z]=1000000;
			tablicaOdleglosci[1][z]=0;
			
			
		}

float odleglosc;
	for (k=0;k<16841; k++){
		
		switch(metoda){
			
			case 1:
				
				odleglosc=sqrt(pow((wczytaneProbkiPCA[i].PC1-tablicaProbekUczacych[k].PC1),2)+pow((wczytaneProbkiPCA[i].PC2-tablicaProbekUczacych[k].PC2),2)+pow((wczytaneProbkiPCA[i].PC3-tablicaProbekUczacych[k].PC3),2)+pow((wczytaneProbkiPCA[i].PC4-tablicaProbekUczacych[k].PC4),2)+pow((wczytaneProbkiPCA[i].PC5-tablicaProbekUczacych[k].PC5),2)+pow((wczytaneProbkiPCA[i].PC6-tablicaProbekUczacych[k].PC6),2)+pow((wczytaneProbkiPCA[i].PC7-tablicaProbekUczacych[k].PC7),2)+pow((wczytaneProbkiPCA[i].PC8-tablicaProbekUczacych[k].PC8),2)+pow((wczytaneProbkiPCA[i].PC9-tablicaProbekUczacych[k].PC9),2)+pow((wczytaneProbkiPCA[i].PC10-tablicaProbekUczacych[k].PC10),2)+pow((wczytaneProbkiPCA[i].PC11-tablicaProbekUczacych[k].PC11),2));
				najmniejszeOdleglosci(tablicaOdleglosci, odleglosc, k);
				break;
				
			case 2:
				
				odleglosc=fabs(wczytaneProbkiPCA[i].PC1-tablicaProbekUczacych[k].PC1)+fabs(wczytaneProbkiPCA[i].PC2-tablicaProbekUczacych[k].PC2)+fabs(wczytaneProbkiPCA[i].PC3-tablicaProbekUczacych[k].PC3)+fabs(wczytaneProbkiPCA[i].PC4-tablicaProbekUczacych[k].PC4)+fabs(wczytaneProbkiPCA[i].PC5-tablicaProbekUczacych[k].PC5)+fabs(wczytaneProbkiPCA[i].PC6-tablicaProbekUczacych[k].PC6)+fabs(wczytaneProbkiPCA[i].PC7-tablicaProbekUczacych[k].PC7)+fabs(wczytaneProbkiPCA[i].PC8-tablicaProbekUczacych[k].PC8)+fabs(wczytaneProbkiPCA[i].PC9-tablicaProbekUczacych[k].PC9)+fabs(wczytaneProbkiPCA[i].PC10-tablicaProbekUczacych[k].PC10)+fabs(wczytaneProbkiPCA[i].PC11-tablicaProbekUczacych[k].PC11);
				najmniejszeOdleglosci(tablicaOdleglosci, odleglosc, k);
				break;
				
			case 3:
			
				float odlegloscCzybyszew[11];


				odlegloscCzybyszew[0]=fabs(wczytaneProbkiPCA[i].PC1-tablicaProbekUczacych[k].PC1);
				odlegloscCzybyszew[1]=fabs(wczytaneProbkiPCA[i].PC2-tablicaProbekUczacych[k].PC2);
				odlegloscCzybyszew[2]=fabs(wczytaneProbkiPCA[i].PC3-tablicaProbekUczacych[k].PC3);
				odlegloscCzybyszew[3]=fabs(wczytaneProbkiPCA[i].PC4-tablicaProbekUczacych[k].PC4);
				odlegloscCzybyszew[4]=fabs(wczytaneProbkiPCA[i].PC5-tablicaProbekUczacych[k].PC5);
				odlegloscCzybyszew[5]=fabs(wczytaneProbkiPCA[i].PC6-tablicaProbekUczacych[k].PC6);
				odlegloscCzybyszew[6]=fabs(wczytaneProbkiPCA[i].PC7-tablicaProbekUczacych[k].PC7);
				odlegloscCzybyszew[7]=fabs(wczytaneProbkiPCA[i].PC8-tablicaProbekUczacych[k].PC8);
				odlegloscCzybyszew[8]=fabs(wczytaneProbkiPCA[i].PC9-tablicaProbekUczacych[k].PC9);
				odlegloscCzybyszew[9]=fabs(wczytaneProbkiPCA[i].PC10-tablicaProbekUczacych[k].PC10);
				odlegloscCzybyszew[10]=fabs(wczytaneProbkiPCA[i].PC11-tablicaProbekUczacych[k].PC11);
				
				float odleglosc=odlegloscCzybyszew[0];
				
				for (int y=1;y<11;y++){
					
					
					if (odlegloscCzybyszew[y]>odleglosc)
					{
					odleglosc=odlegloscCzybyszew[y];
					
					}
					
					
					}
					
					
				najmniejszeOdleglosci(tablicaOdleglosci, odleglosc, k);
	
				break;					
				}
			}
			
			
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
				wczytaneProbkiPCA[i].typ=tablicaProbekUczacych[(int)tablicaOdleglosci[1][0]].typ;
				
			}
			
			
		else if(sasiedziZBezdechem<sasiedzBezBezdechu){
			
			
			wczytaneProbkiPCA[i].typ='A';
			
		}
		
		else{
			
			wczytaneProbkiPCA[i].typ='N';
			
		}
					
		}
		
		
	

//
/////blok wywietlania
//
////for ( k=0; k< 10;k++) {
//            
//  //    std::cout << sortowanaAnalizowanych[k]<< "\n";
//       // }
////koniec bloku
//}

		int niesklasyfikowane =0;
		int zgodnieSklasyfikowane=0;
		int nieZgodnieSklasyfikowane=0;

		for (i=0;i<liczbaBadanychProbek;i++){

			if(wczytaneProbkiPCA[i].typ=='U'){
				niesklasyfikowane++;
			}

			else if(wczytaneProbkiPCA[i].typ==etykietyBadane[i]){
				zgodnieSklasyfikowane++;


			}
				else if(wczytaneProbkiPCA[i].typ!=etykietyBadane[i]){
				nieZgodnieSklasyfikowane++;
				}
		}

		std::cout<< "Pozadany rezultat     uzyskany rezultat";
		
		for(i=0;i<liczbaBadanychProbek;i++){
			std::cout<<etykietyBadane[i]<<"\t"<<wczytaneProbkiPCA[i].typ<<"\t"<<i+1<<"\n";
		}

		
				std::cout <<"Probki  niesklasyfikowane "<< niesklasyfikowane<<"\n";
				std::cout <<"Probki zgodnie sklasyfikowane "<<zgodnieSklasyfikowane<<"\n";
				std::cout <<"Probki niezgodnie sklasyfikowane "<<nieZgodnieSklasyfikowane<<"\n";
				
//std::cout << "This is a native C++ program.";


system("PAUSE");
	std::cin.get();

	

    return 0;
}