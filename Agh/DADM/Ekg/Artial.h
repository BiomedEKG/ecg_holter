#ifndef ARTIAL_H
#define ARTIAL_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

class Artial //: public AbstractModule

{
private:

	vector<double> signal;
	vector <vector <double> > signal128;
	vector <vector <double> > signal112;
	vector<double> average;
	vector<double> tpr;
	vector<double> se;
	vector<double> rmssd;
	vector<int> licznikAF;
	vector<int> numbersOfAF;
	static const int lengthSegment;
	
public:

	/*constructor with parameter signal
	Artial(vector<double> signal); */

	/*constructor with no parameters for testing as far*/
	Artial();

	/*definition of function round*/
	double round( double fValue );

	/*read data from file*/
	void readData();

	/*find 8th min value in sorted signal128*/
	double minValue(vector <double> rawSeparateSignal);

	/*find 8th max value in sorted signal128*/
	double maxValue(vector <double> rawSeparateSignal);

	/*Seperate data into many vectors with 128 values*/
	void separateSegments();

	/*Prepare segments without outliers*/
	void prepareSegmentsWithoutOutlieres();

	/*calculate mean from each segment*/
	void meanSegment();

	/*calculate RMSSD from each segment*/
	void rmssdSegment();

	/*calculate Shannon Entropy from each segment*/
	void seSegment();

	/*calculate TPR*/
	void tprSegment();

	/*check if it is artial fibrillation in signal*/
	void checkAF();

	/*Run everything */
	void ArtialFibrilattion();

	/*Grupa funkcji odpowiedzialna za wyœwietlanie danej funckji statystycznej*/
	/*shows the dividded siganl vector using cout*/
	void showsignal128();

	void showsignal112();

	void showAverage();

	void showRmssd();

	void showTpr();

	void showSe();

	void showAF();

	
};

#endif 
