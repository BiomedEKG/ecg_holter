#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "Kmeans.h"
#include <algorithm> 

using namespace std;

Kmeans::Kmeans(vector<double>* malinowska, vector<double>* fastGrowth, vector<double>* speedAmplitude){
	
	this->calculatedParametersMap.clear();
	this->artifactsCentroid.clear();
	this->normalQrsCentroid.clear();
	this->vQrsCentroid.clear();
	
	// wype³nienie wektorów okreslajacych polozenie poczatkowe centroidow

	this->normalQrsCentroid.push_back(rand()%3+21);
	this->normalQrsCentroid.push_back(rand()%1+3);
	this->normalQrsCentroid.push_back(rand()%4+20);
	
	this->vQrsCentroid.push_back(rand()%3+20);
	this->vQrsCentroid.push_back(rand()%1+5);
	this->vQrsCentroid.push_back(rand()%3+22);
	
	this->artifactsCentroid.push_back(rand()%3+20);
	this->artifactsCentroid.push_back(rand()%1+4);
	this->artifactsCentroid.push_back(rand()%3+22);

	
	// Zapisanie do mapy wszystkich wyliczonych wartosci parametrow (dla kazdego punktu inny klucz)
	for(unsigned int i = 0; i < malinowska->size(); i++){
		
		this->calculatedParametersMap[i].push_back(malinowska->at(i));
		this->calculatedParametersMap[i].push_back(fastGrowth->at(i));
		this->calculatedParametersMap[i].push_back(speedAmplitude->at(i));
	}
}

double Kmeans::DistanceCalculator(vector<double> centroid, vector<double>* point){
	
	double x = centroid.at(0) - point->at(0);
	double y = centroid.at(1) - point->at(1);
	double z = centroid.at(2) - point->at(2);
	double calculatedDistance = sqrt((x*x)+(y*y)+(z*z));
	
	return calculatedDistance;
}

void Kmeans::ClassificationStep(){

	vector<double> temp;
	double distanceNormal;
	double distanceV;
	double distanceArtifact;
	this->normalQrs.clear();
	this->vQrs.clear();
	this->artifacts.clear();
	
	for(unsigned int i = 0; i < this->calculatedParametersMap.size(); i++){
		
		distanceNormal = DistanceCalculator(this->normalQrsCentroid, &calculatedParametersMap[i]);
		distanceV = DistanceCalculator(this->vQrsCentroid, &calculatedParametersMap[i]);
		distanceArtifact = DistanceCalculator(this->artifactsCentroid, &calculatedParametersMap[i]);
		
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

vector<double> Kmeans::centroidLocationCalculator(vector<double> tempCalculatedParameters){
	
	double newValueMalinowska = 0;
	double newValueFastGrowth = 0;
	double newValueSpeedAmplitude = 0;
	
	double meanNewValueMalinowska = 0;
	double meanNewValueFastGrowth = 0;
	double meanNewValueSpeedAmplitude = 0;
	
	vector<double> newLocation;
	newLocation.clear();

	for(unsigned int i = 0; i < tempCalculatedParameters.size(); i++){
		
		if(tempCalculatedParameters.empty()){
			
			meanNewValueMalinowska = 1;
			meanNewValueFastGrowth = 1;
			meanNewValueSpeedAmplitude = 1;
		}
		else{
			
			newValueMalinowska = this->calculatedParametersMap[tempCalculatedParameters.at(i)].at(0);
			newValueFastGrowth = this->calculatedParametersMap[tempCalculatedParameters.at(i)].at(1);
			newValueSpeedAmplitude = this->calculatedParametersMap[tempCalculatedParameters.at(i)].at(2);
			
			meanNewValueMalinowska = meanNewValueMalinowska + newValueMalinowska;
			meanNewValueFastGrowth = meanNewValueFastGrowth + newValueFastGrowth;
			meanNewValueSpeedAmplitude = meanNewValueSpeedAmplitude + newValueSpeedAmplitude;
		}
	}
	
	if(!tempCalculatedParameters.empty()){
		
		meanNewValueMalinowska = meanNewValueMalinowska/tempCalculatedParameters.size();
		meanNewValueFastGrowth = meanNewValueFastGrowth/tempCalculatedParameters.size();
		meanNewValueSpeedAmplitude = meanNewValueSpeedAmplitude/tempCalculatedParameters.size();
	}
	
	newLocation.push_back(meanNewValueMalinowska);
	newLocation.push_back(meanNewValueFastGrowth);
	newLocation.push_back(meanNewValueSpeedAmplitude);
	
	return newLocation;
}


/**/
