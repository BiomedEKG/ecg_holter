#include <iostream>
#include "TS.h"
#define NORMVALUE 3

void TS::show(){

	
	std::cout << "Wartosc wspolczynnika a: "; std::cout << this->a << std::endl;
	std::cout << "Wartosc wspolczynnika b: "; std::cout << this->b << std::endl << std::endl;

	if(this->TScorrect == true)
		std::cout << "Wartosc TS wynosi " << this->a << "jest poprawna.";
	else{
		std::cout << "Wartosc TS wynosi " << this->a <<  " i jest nieprawidlowa. Norma wynosi "; std::cout << NORMVALUE << std::endl;
	}
};


void TS::weightedLeastSquares(std::vector<double> meanTachogram, static const int before){

	

	std::vector<double>::iterator T_it = meanTachogram.begin();
	std::vector<double>::iterator T_it1 = meanTachogram.begin();
	double y[5][15];
	int i=0, j=0, k=0;
	for(T_it=T_it+before+2; T_it!=meanTachogram.end()-5; T_it++, j++){
		for(int i=0; i<5; i++){
			y[i][j] = *(T_it+i);
		}
		i=0;
	}

	double A[5][2] = {{1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}};
	double AT[2][5] = {{1, 1, 1, 1, 1}, {1, 2, 3, 4, 5}};
	//A'*A
	 i=0;
	 j=0;
	 k=0;

	double out[2][2] = {0};

	for(k=0; k<2; k++){
		for(j=0; j<2; j++){  
			for(i=0; i<5; i++){     
				out[k][j] = out[k][j] + ((AT[k][i]) * (A[i][j]));	
			}
		}
	}

	double det_out = out[0][0]*out[1][1] - out[0][1]*out[1][0];

	double dopel_out[2][2] = {{out[1][1], -out[1][0]}, {-out[0][1], out[0][0]}};
	double dopel_outT[2][2] = {{dopel_out[0][0], dopel_out[1][0]}, {dopel_out[0][1], dopel_out[1][1]}};
	double out_inv[2][2] = {{dopel_outT[0][0]/det_out, dopel_outT[0][1]/det_out}, {dopel_outT[1][0]/det_out, dopel_outT[1][1]/det_out}};

	 i=0;
	 j=0;
	 k=0;
	 double out1[2][5] = {0};
	 for(k=0; k<2; k++){
		for(j=0; j<5; j++){ //kolumny pierwszej 
			for(i=0; i<2; i++){			//wiersze drugiej
				out1[k][j] = out1[k][j] + ((out_inv[k][i]) * (AT[i][j]));	
			}
		}
	}

	double temp[5][1] = {0};
	double coeff[2][1][14] = {0};

	for(int n=0; n<14; n++){
		i=0;
		j=0;
		k=0;
		for(k=0; k<2; k++){
			coeff[k][j][n] *  0;
			for(j=0; j<1; j++){ //kolumny pierwszej 
				for(i=0; i<2; i++){			//wiersze drugiej
					coeff[k][j][n] = coeff[k][j][n] + ((out1[k][i]) * (y[i][n]));	
					
				}
			}
			/*std::cout <<  coeff[0][0][n] << std::endl;
			std::cout <<  coeff[1][0][n] << std::endl;
			std::cout << std::endl;*/}
	}

		//teraz szukam prostej o najwiêkszym nachyleniu.
	double max = coeff[1][0][0];
	int ind=0;
	for(int n=1; n<14; n++){
		if(coeff[1][0][n]>max){
			max = coeff[1][0][n];
			ind = n;
			
		}
	}

	this->a=max;
	this->b=coeff[0][0][ind];
	//dwa punkty przez które przechodziæ bêdzie prosta nachylenia TS
	double P1 = this->a * meanTachogram[ind]  - this->b;
	double P2 = this->a * meanTachogram[ind+4] - this->b;
	this->points.push_back(P1);
	this->points.push_back(P2);
	this->indexes.push_back(ind);
	this->indexes.push_back(ind+4);

}



void TS::turbulenceSlopeEvaluation(){

	if(this->a > NORMVALUE)
		this->TScorrect = true;
	else
		this->TScorrect = false;

}