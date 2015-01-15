#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#ifndef KMEANS_H
#define KMEANS_H

using namespace std;

class Kmeans{
	
	public:
		vector<double> normalQrs;
		vector<double> vQrs;
		vector<double> artifacts;
		
		vector<double> normalQrsCentroid;
		vector<double> vQrsCentroid;
		vector<double> artifactsCentroid;
		
		map<int, vector<double> > calculatedParametersMap;
		
		Kmeans(vector<double> malinowska, vector<double> fastGrowth, vector<double> speedAmplitude);
		double DistanceCalculator(vector<double> centroid, vector<double> point);
		void ClassificationStep();
		vector<double> centroidLocationCalculator(vector<double> classCalculatedParameters);
};

#endif // KMEANS_H

