#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "HeartClass.h"
#include "MalinowskaParameter.h"
#include "SpeedAmplitudeParameter.h"
#include "FastGrowthParameter.h"
#include "Kmeans.h"

using namespace std;

HeartClass::HeartClass(vector<double> qrsOnsetFromWaves, vector<double> qrsEndFromWaves, 
															vector<double> signalFromEcgBaseline){
	
	FastGrowthParameter fastGrowth(qrsOnsetFromWaves, qrsEndFromWaves, signalFromEcgBaseline);
    fastGrowth.FastGrowthExtractor();
    
	SpeedAmplitudeParameter speedAmplitude(qrsOnsetFromWaves, qrsEndFromWaves, signalFromEcgBaseline);
    speedAmplitude.SpeedAmplitudeExtractor();
    
	MalinowskaParameter malinowska(qrsOnsetFromWaves, qrsEndFromWaves, signalFromEcgBaseline);
    malinowska.MalinowskaExtractor();
    
    Kmeans kmeans(malinowska.malinowskaValues, fastGrowth.fastGrowthValues, speedAmplitude.speedAmplitudeValues);
    
    Kmeans temp(malinowska.malinowskaValues, fastGrowth.fastGrowthValues, speedAmplitude.speedAmplitudeValues);
    
	do{
		
		temp.normalQrsCentroid = kmeans.normalQrsCentroid;
		temp.vQrsCentroid = kmeans.vQrsCentroid;
		temp.artifactsCentroid = kmeans.artifactsCentroid;
		
		kmeans.ClassificationStep();
		kmeans.normalQrsCentroid = kmeans.centroidLocationCalculator(kmeans.normalQrs);
		kmeans.artifactsCentroid = kmeans.centroidLocationCalculator(kmeans.artifacts);
		kmeans.vQrsCentroid = kmeans.centroidLocationCalculator(kmeans.vQrs);
		
	}while((temp.normalQrsCentroid != kmeans.normalQrsCentroid) && (temp.vQrsCentroid != kmeans.vQrsCentroid) && (temp.artifactsCentroid != kmeans.artifactsCentroid));
	
	for(unsigned int i = 0; i < kmeans.normalQrs.size(); i++){

		this->qrsClassificationMap["NormalQRS"].push_back(kmeans.normalQrs.at(i));
	}
		
	for(unsigned int i = 0; i < kmeans.vQrs.size(); i++){

		this->qrsClassificationMap["VQRS"].push_back(kmeans.vQrs.at(i));
	}	
		
	for(unsigned int i = 0; i < kmeans.artifacts.size(); i++){

		this->qrsClassificationMap["Artifacts"].push_back(kmeans.artifacts.at(i));
	}	
}
