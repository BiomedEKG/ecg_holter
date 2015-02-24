#ifndef STSEGMENT_H
#define STSEGMENT_H

#include <AbstractModule.h>
#include <iterator>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <string>
#include <fstream>
#include <map>
#include "stsegmentresult.h"

using namespace std;


class STSegment : public AbstractModule<STSegmentResult>
{
	public:

	vector<int> QRSonset ; 
	vector<int> QRSend;
	vector<double> Signal;
	vector<int> Tpeak;
	vector<unsigned int> Rpeak;
	int SizeVector;
	double Frequency;


	vector<double> HeartRate;
	vector<int> J20;
	vector<int> Ton;
	vector<int> TE;
	vector<int> TMax;
	vector <double> SlopeTpeak;
	vector <double> SlopeTon;
	vector <double> SlopeSKST;
	vector <double> MaxDistanceTpeak;
	vector <double> MaxDistanceTon;
	vector <double> MaxDistanceShapeSKST;
	vector<string> OffsetLevel;
	vector<string> ShapeST;
	vector <string> TypeShapeST;
	double k1offset;
	double k2offset;
	double k1slope;
	double k2slope;
	double threshold;
	map<string, vector<string>> Results;


	vector< int>  computeJ20 ();
	vector<double>  computeSlope (vector<int> TE);
	vector<int> computeMaxDistanceIndex (vector <double> Slope,  vector< int> TE,vector<double>& MaxDistance);
	vector<string> defineOffsetLevel ();
	vector<double> correctSlopeorMaxDistanceForShapeST(vector<double> StraightTpeak,vector <double> StraighTon);
	vector< int> correctTEForShapeST ();
	vector<string>  defineShapeST ();
	vector<string>  defineTypeShapeST ();
	vector <double> computeHeartRate ();
	void CorrectSize();
	void Run();

	public:
  
	 STSegmentResult* compute(ResultKeeper *rkp) override;
	
															
};


#endif