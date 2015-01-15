#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "Kmeans.h"

using namespace std;
// na razie bez statystyki
Kmeans::Kmeans(vector<double> malinowska, vector<double> fastGrowth, vector<double> speedAmplitude){
	
	this->calculatedParametersMap.clear();
	this->artifactsCentroid.clear();
	this->normalQrsCentroid.clear();
	this->vQrsCentroid.clear();
	
	for(unsigned int i = 0; i < 3; i++){
		
		this->artifactsCentroid.push_back(3);
		this->normalQrsCentroid.push_back(3);
		this->vQrsCentroid.push_back(4);
	}
	
	// ilosc wektorów
	for(unsigned int i = 0; i < malinowska.size(); i++){
		
		this->calculatedParametersMap[i].push_back(malinowska.at(i));
		this->calculatedParametersMap[i].push_back(fastGrowth.at(i));
		this->calculatedParametersMap[i].push_back(speedAmplitude.at(i));
	}
}

double Kmeans::DistanceCalculator(vector<double> centroid, vector<double> point){
	
	double x = centroid.at(0) - point.at(0);
	double y = centroid.at(1) - point.at(1);
	double z = centroid.at(2) - point.at(2);
	double calculatedDistance = sqrt((x*x)+(y*y)+(z*z));
	
	return calculatedDistance;
}

void Kmeans::ClassificationStep(){

	vector<double> temp;
	double distanceNormal;
	double distanceV;
	double distanceArtifact;
	
	for(unsigned int i = 0; i < this->calculatedParametersMap.size(); i++){
		
		distanceNormal = DistanceCalculator(this->normalQrsCentroid, calculatedParametersMap[i]);
		distanceV = DistanceCalculator(this->vQrsCentroid, calculatedParametersMap[i]);
		distanceArtifact = DistanceCalculator(this->artifactsCentroid, calculatedParametersMap[i]);
		
		if(min(distanceNormal, min(distanceV, distanceArtifact)) == distanceNormal){
			
			this->normalQrs.push_back(i);
		} 
		else if(min(distanceNormal, min(distanceV, distanceArtifact)) == distanceV){
			
			this->vQrs.push_back(i);
		}
		else{
			
			this->artifacts.push_back(i);
		}
	}
}

vector<double> Kmeans::centroidLocationCalculator(vector<double> classCalculatedParameters){
	
	double distanceMalinowska;
	double distanceFastGrowth;
	double distanceSpeedAmplitude;
	double meanDistanceMalinowska = 0;
	double meanDistanceFastGrowth = 0;
	double meanDistanceSpeedAmplitude = 0;
	vector<double> temp;
	vector<double> newLocation;
	newLocation.clear();
	
	for(unsigned int i = 0; i < classCalculatedParameters.size(); i++){
		
		temp = calculatedParametersMap.at(classCalculatedParameters.at(i));
		distanceMalinowska = fabs(classCalculatedParameters.at(0) - temp.at(0));
		distanceFastGrowth = fabs(classCalculatedParameters.at(1) - temp.at(1));
		distanceSpeedAmplitude = fabs(classCalculatedParameters.at(2) - temp.at(2));
		meanDistanceMalinowska = meanDistanceMalinowska + distanceMalinowska;
		meanDistanceFastGrowth = meanDistanceFastGrowth + distanceFastGrowth;
		meanDistanceSpeedAmplitude = meanDistanceSpeedAmplitude + distanceSpeedAmplitude;
	}
	
	meanDistanceMalinowska = meanDistanceMalinowska/classCalculatedParameters.size();
	meanDistanceFastGrowth = meanDistanceFastGrowth/classCalculatedParameters.size();
	meanDistanceSpeedAmplitude = meanDistanceSpeedAmplitude/classCalculatedParameters.size();
	
	newLocation.push_back(meanDistanceMalinowska);
	newLocation.push_back(meanDistanceFastGrowth);
	newLocation.push_back(meanDistanceSpeedAmplitude);
	
	return newLocation;
}




















/**/

