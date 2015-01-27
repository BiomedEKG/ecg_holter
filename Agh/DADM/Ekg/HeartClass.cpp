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

HeartClass::HeartClass(vector<double>* qrsOnsetFromWaves, vector<double>* qrsEndFromWaves, 
															vector<double>* signalFromEcgBaseline){
	
    vector<double>* wsignal;
    vector<double>* wqrsOnset;
    vector<double>* wqrsEnd;
	wsignal = signalFromEcgBaseline;
	wqrsOnset = qrsOnsetFromWaves;
	wqrsEnd = qrsEndFromWaves;
	
	FastGrowthParameter fastGrowth(wqrsOnset, wqrsEnd, wsignal);
    fastGrowth.FastGrowthExtractor();

	SpeedAmplitudeParameter speedAmplitude(wqrsOnset, wqrsEnd, wsignal);
    speedAmplitude.SpeedAmplitudeExtractor();
   
	MalinowskaParameter malinowska(wqrsOnset, wqrsEnd, wsignal);
    malinowska.MalinowskaExtractor();
    
    vector<double>* wMalinowska;
    vector<double>* wSpeedAmplitude;
    vector<double>* wFastGrowth;
    wMalinowska = &malinowska.malinowskaValues;
    wSpeedAmplitude = &speedAmplitude.speedAmplitudeValues;
    wFastGrowth = &fastGrowth.fastGrowthValues;

	Kmeans kmeans(wMalinowska, wFastGrowth, wSpeedAmplitude);
	Kmeans temp(wMalinowska, wFastGrowth, wSpeedAmplitude);
    
	do{
		
		temp.normalQrsCentroid = kmeans.normalQrsCentroid;
		temp.vQrsCentroid = kmeans.vQrsCentroid;
		temp.artifactsCentroid = kmeans.artifactsCentroid;
		
		kmeans.ClassificationStep();
		kmeans.normalQrsCentroid = kmeans.centroidLocationCalculator(kmeans.normalQrs);
		kmeans.artifactsCentroid = kmeans.centroidLocationCalculator(kmeans.artifacts);
		kmeans.vQrsCentroid = kmeans.centroidLocationCalculator(kmeans.vQrs);
		
	}while((temp.normalQrsCentroid != kmeans.normalQrsCentroid) && (temp.vQrsCentroid != kmeans.vQrsCentroid) && (temp.artifactsCentroid != kmeans.artifactsCentroid));

	qrsClassificationMap.insert(pair<string, vector<double> > ("NormalQRS", kmeans.normalQrs));
	qrsClassificationMap.insert(pair<string, vector<double> > ("VQRS", kmeans.vQrs));
	qrsClassificationMap.insert(pair<string, vector<double> > ("Artifacts", kmeans.artifacts));
}