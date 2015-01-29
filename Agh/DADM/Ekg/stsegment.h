#ifndef STSEGMENT_H
#define STSEGMENT_H


#include <vector>
#include <iterator>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <string>
#include <fstream>
#include <map>

using namespace std;


class STSegment : public AbstractModule
{
	private:

	vector<unsigned int> QRSonset ; 
	vector<unsigned int> QRSend;
	vector<double> Signal;
	vector<unsigned int> Tpeak;
	vector<unsigned int> Rpeak;
	int SizeVector;
	double Frequency;

	public:
  
	vector<double> HeartRate;
	vector<unsigned int> J20;
	vector<unsigned int> Ton;
	vector<unsigned int> TE;
	vector<unsigned int> TMax;
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
	
	  
	vector<unsigned int>  computeJ20 ();
	vector<double>  computeSlope (vector<unsigned int> TE);
	vector<unsigned int> computeMaxDistanceIndex (vector <double> Slope,  vector<unsigned int> TE,vector<double>& MaxDistance);
	vector<string> defineOffsetLevel ();
	vector<double> correctSlopeorMaxDistanceForShapeST(vector<double> StraightTpeak,vector <double> StraighTon);
	vector<unsigned int> correctTEForShapeST ();
	vector<string>  defineShapeST ();
	vector<string>  defineTypeShapeST ();
	vector <double> computeHeartRate ();
	void CorrectSize();
	void Run();
	
	STSegmentResult compute(map <string, vector<unsigned int> >*resultFromWaves, vector<double>* signal,vector<unsigned int>*Rpeaks);
	STSegment (vector<double> Signal, int Frequency, vector<unsigned int> QRSonset, vector<unsigned int> QRSend, 
		vector<unsigned int> Tpeak,vector <unsigned int> Rpeak);
	
	
														
};

class STSegmentResult 
{
	public:
	vector <string> OffsetLevel;
	vector <string> ShapeST;
	vector <string> TypeShapeST; 
	STSegmentResult(vector<string> OffsetLevel, vector<string>ShapeST, vector <string> TypeShapeST);


};

#endif