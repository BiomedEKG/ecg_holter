#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "MyMap.h"
#ifndef KMEANS_H
#define KMEANS_H

using namespace std;

class Kmeans{
	
	public:
		vector<double> normalQrs;
		vector<double> VQrs;
		vector<double> artifacts;
		
		vector<double> normalQrsCentroid;
		vector<double> vQrsCentroid;
		vector<double> artifactsCentroid;

		MyMap mapedParameterValues;
		
		Kmeans(vector<double> Malinowska, vector<double> FastGrowth, vector<double> SpeedAmplitude);
		void ClassificationStep();
		friend double DistanceCalculator(vector<double> centroid, vector<double> point);
		friend vector<double> CentroidDistanceCalculator(vector<double> centroidLocation, MyMap values);
		friend void PerformClassification(Kmeans &k);
};

#endif // KMEANS_H
