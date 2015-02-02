#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "ResultKeeper.h"
#include "HeartClassResult.h"
#ifndef HEART_CLASS_H
#define HEART_CLASS_H

using namespace std;

class HeartClass{
	
	public:
		
		//TODO dowiedzie� si� sk�d wzi�� frequency
		double frequency;
		
		map<int, vector<double> > signalMap;
		map<int, vector<double> > yQRS;
		map<int, vector<double> > samplesBetweenMax;

		//Wype�ni� w compute!!!
		vector<double> qrsMinAmplitudes;
		vector<double> qrsMaxAmplitudes;
		vector<double> qrsMinAmplitudesSamples;
		vector<double> qrsMaxAmplitudesSamples;
		
		vector<double> leftMaxAmplitudeSamples;
		vector<double> rightMaxAmplitudeSamples;
		vector<double> leftMinAmplitudeSamples;
		vector<double> rightMinAmplitudeSamples;
		
		vector<double> maxArea;
		vector<double> maxSamplesBetween;
    	vector<double> minSamplesBetween;
    	vector<double> qrsOnset;
    	vector<double> qrsEnd;
		
		double meanMaxAmplitude;
		double meanMinAmplitude;
		double meanMaxArea;
		double meanSamplesBetweenMax;
		double meanSamplesBetweenMin;
		
		HeartClass();
		HeartClass(ResultKeeper* rpk);
		
		virtual HeartClassResult* compute(ResultKeeper* rkp); const override;
		
		double ComplexArea(vector<double>* tempArea);
		void Amplitudes(vector<double>* temp);
		void FrameLocator();
		void MeanAmplitude();
		void SamplesBetween();
		void Conditioning();
};

#endif // HEART_CLASS_H

