#ifndef AtrialFibrillation_H
#define AtrialFibrillation_H
#include "AbstractModule.h"
#include "AtrfibrResult.h"
#include "ResultKeeper.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
using namespace std;

class AtrFibr :
	public AbstractModule<AtrfibrResult>
{
private: 
	//Dane 
	vector<double> signal; //zawiera obliczone interwaly RR
	vector <vector <double> > signal128; //interwaly RR w blokach 128
	vector <vector <double> > signal112; // 112
	vector<double> average; // srednia
	vector<double> tpr; // #1wsp statyczny turning point ratio
	vector<double> se; // #2wsp statyczny Shanon entrophy
	vector<double> rmssd; //3#wsp RMSSD
	vector<int> licznikAF; // Licznik AF
	vector<int> numbersOfAF; // Liczba AF
	static const int lengthSegment = 128;
	//Funkcje
	void createrr(vector<unsigned int>& peaksNum, double freq);
	double round( double fValue );/*definition of function round*/
	void separateSegments();/*Seperate data into many vectors with 128 values*/
	void prepareSegmentsWithoutOutlieres();/*Prepare segments without outliers*/
	void meanSegment();/*calculate mean from each segment*/
	void rmssdSegment();/*calculate RMSSD from each segment*/
	void seSegment();/*calculate Shannon Entropy from each segment*/
	void tprSegment();/*calculate TPR*/
	bool checkAF();/*check if it is AtrialFibrillation fibrillation in signal*/
	vector <unsigned int> returnDeteckedAF(vector<unsigned int> r_peaks);/*prepare vector with detecked samples with AF*/
	double minValue(vector <double> rawSeparateSignal);/*find 8th min value in sorted signal128*/
	double maxValue(vector <double> rawSeparateSignal);/*find 8th max value in sorted signal128*/
public:
	AtrFibr(void);
	~AtrFibr(void);
	/*Metoda compute*/
	AtrfibrResult* compute(ResultKeeper* rkp);
};

#endif