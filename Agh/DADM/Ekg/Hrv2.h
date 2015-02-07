#pragma once
#include<vector>
#include<map>
#include<string>
#include <Hrv2Result.h>
#include <AbstractModule.h>
#include <ResultKeeper.h>
using namespace std;

class Hrv2 : public AbstractModule<Hrv2Result>{
  
	public:

		//pola
		string paramsUnits[6]; //jednostki parametrów apen, samen, tinn, triangle index, sd1,sd2
		string histUnits[2]; //jednostki histogramu x i y
		string poincareUnits[2]; //jednostki wykresu Poincare x i y
		unsigned int freq;
        vector<double> r_peaks;
        int N;
		map<string, vector<double>> x1_x2;
		map<string, vector<double>> histValues;
		//metody
		Hrv2();
		void setValues(vector<double> x, unsigned int y);
		virtual Hrv2Result* compute(ResultKeeper* rkp);

private:
		vector<double> create_RR_intervals();
        map<string, vector<double>> poincareVectors(vector<double> val);
		map<string, vector<double>> createHist(vector<double> val, double s);
		double mean2(vector<double> z);
        double stDeviation2 (vector<double> z);
        double sum(vector<double> elem);
		double maxIndex(vector<double> v);
		map<string,double>  getCoff(vector<double> war, vector<double> c);
		double Hrv2:: getCorrelation(double varb1, double varb2, vector<double> war, vector<double> c);
		map<string, double> fit(map<string,vector<double>> histValues);
        double calculateApen(vector<double> val, double s, int dim = 2);
        double calculateSamen(vector<double> val, double s, int dim = 2);
        map<string, double> poincareParams(map<string,vector<double>> x1_x2);
		map<string, vector<double>> sdPoints(map<string,vector<double>> x1_x2 );
        double triangleRR(map<string,vector<double>> histValues);
        double tinn(map<string,vector<double>> histValues);
		
		
      
};

