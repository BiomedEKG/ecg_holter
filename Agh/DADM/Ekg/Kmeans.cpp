#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "Kmeans.h"

// na razie bez statystyki
Kmeans::Kmeans(vector<double> Malinowska, vector<double> FastGrowth, vector<double> SpeedAmplitude){
	
	for(unsigned int i = 0; i < 3; i++){
		
		this->artifactsCentroid.at(i) = rand() % 30 + 1;
		this->normalQrsCentroid.at(i) = rand() % 30 + 1;
		this->vQrsCentroid.at(i) = rand() % 30 + 1;
	}
	
	MyMap temp;
	vector<double> qrsParameters;
	// ilosc wektorów
	for(unsigned int i = 0; i < Malinowska.size(); i++){
		
		qrsParameters.clear();
		qrsParameters.push_back(Malinowska.at(i));
		qrsParameters.push_back(FastGrowth.at(i));
		qrsParameters.push_back(SpeedAmplitude.at(i));
		temp.InsertToMap(i, qrsParameters);
	}
	
	this->mapedParameterValues = temp;
}

double DistanceCalculator(vector<double> centroid, vector<double> point){
	
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
	
	for(unsigned int i = 0; i < this->mapedParameterValues.size(); i++){
		
		temp = this->mapedParameterValues.FindInMap(i);
		distanceNormal = DistanceCalculator(this->normalQrsCentroid, temp);
		distanceV = DistanceCalculator(this->vQrsCentroid, temp);
		distanceArtifact = DistanceCalculator(this->artifactsCentroid, temp);
		
		if(min(distanceNormal, min(distanceV, distanceArtifact)) == distanceNormal){
			
			this->normalQrs.push_back(i);
		} 
		else if(min(distanceNormal, min(distanceV, distanceArtifact)) == distanceV){
			
			this->VQrs.push_back(i);
		}
		else{
			
			this->artifacts.push_back(i);
		}
	}
}

vector<double> CentroidDistanceCalculator(vector<double> centroidLocation, MyMap values){
	
	vector<double> newCentroidLocation;
	newCentroidLocation.clear();
	vector<double> qrsValues;
	vector<double> temp;
	double x = 0;
	double y = 0;
	double z = 0;
	
	for(unsigned int i = 0; i < centroidLocation.size(); i++){

		temp.clear();
		qrsValues = values.FindInMap(centroidLocation.at(i));
			
		x = x + qrsValues.at(0);
		y = y + qrsValues.at(1);
		z = z + qrsValues.at(2);
	}
	
	double meanX = x/centroidLocation.size();
	double meanY = y/centroidLocation.size();
	double meanZ = z/centroidLocation.size();
	
	newCentroidLocation.push_back(meanX);
	newCentroidLocation.push_back(meanY);
	newCentroidLocation.push_back(meanZ);
	
	return newCentroidLocation;
}

void PerformClassification(Kmeans &k){
	
	Kmeans temp = k;
	
	do{
		k.ClassificationStep();
		temp.normalQrsCentroid = CentroidDistanceCalculator(k.normalQrsCentroid, k.mapedParameterValues);
		temp.vQrsCentroid = CentroidDistanceCalculator(k.vQrsCentroid, k.mapedParameterValues);
		temp.artifactsCentroid = CentroidDistanceCalculator(k.artifactsCentroid, k.mapedParameterValues);	
		k.normalQrsCentroid = temp.normalQrsCentroid;
		k.vQrsCentroid = temp.vQrsCentroid;
		k.artifactsCentroid = temp.artifactsCentroid;
	}while((temp.normalQrsCentroid != k.normalQrsCentroid) && (temp.vQrsCentroid != k.vQrsCentroid) && (temp.artifactsCentroid != k.artifactsCentroid));
}





