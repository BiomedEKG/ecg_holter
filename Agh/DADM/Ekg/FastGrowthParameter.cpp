#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <fstream>
#include "FastGrowthParameter.h"

using namespace std;

FastGrowthParameter::FastGrowthParameter(vector<double>* qrsOnsetData, vector<double>* qrsEndData, vector<double>* signalData) : 
										AbstractExtractor(qrsOnsetData, qrsEndData, signalData){

}

void FastGrowthParameter::FastGrowthExtractor(){

	vector<double> signalData;
	vector<double> speedValues;
	//ofstream speedTestTxt;
   // speedTestTxt.open("D:\\Dadm\\MójProjekt2\\speedTest.txt", ios::app);
	for(unsigned int i = 0; i < this->signalMap.size(); i++){

		signalData.clear();
		speedValues.clear();
		double maxSpeed = 0;
		double speed = 0;
		double samplesCount = 0;
		signalData = this->signalMap[i];
		
		speed = abs(signalData.at(2) + signalData.at(0) - 2*signalData.at(1));
		speedValues.push_back(speed);
		maxSpeed = speed;
		
		for(unsigned int j = 2; j < signalData.size(); j++){
			
			speed = abs(signalData.at(j) + signalData.at(j-2) - 2*signalData.at(j-1));
			speedValues.push_back(speed);
			if(speed > maxSpeed){
				maxSpeed = speed;
			}
		
		//	speedTestTxt << signalData.at(j) << " + " << signalData.at(j-2) << " - " << 2*signalData.at(j-1);
		//	speedTestTxt << "  speed = " << speed << endl;
		}
		
		//speedTestTxt << endl << "max speed = " << maxSpeed << endl << endl;
		//speedTestTxt << "40% max speed = " << 0.4*maxSpeed << endl << endl;
		maxSpeed = maxSpeed*0.4;

		for(unsigned int k = 0; k < speedValues.size(); k++){

			if(speedValues.at(k) > maxSpeed){
				samplesCount++;
			}
		}
		
		this->fastGrowthValues.push_back((samplesCount/(speedValues.size()-1))*10);
	}
	
	//speedTestTxt.close();
	
	// zapis do pliku
	/*ofstream fastGrowthTestTxt;
    fastGrowthTestTxt.open("D:\\Dadm\\MójProjekt2\\fastGrowthTest.txt");
	for(unsigned int i = 0; i < this->fastGrowthValues.size(); i++){
	    	
	    fastGrowthTestTxt << this->fastGrowthValues.at(i) << endl;
	}
    fastGrowthTestTxt.close();*/
}
