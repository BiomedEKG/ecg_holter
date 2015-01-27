#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <map>
#include "MalinowskaParameter.h"

using namespace std;

MalinowskaParameter::MalinowskaParameter(vector<double>* qrsOnsetData, vector<double>* qrsEndData, vector<double>* signalData) : 
										AbstractExtractor(qrsOnsetData, qrsEndData, signalData){
											
}

// Testing on a different data
void MalinowskaParameter::MalinowskaExtractor(){

	vector<double> signalData;

	for(unsigned int i = 0; i < this->signalMap.size(); i++){

		double area = 0;
		double sum = 0;
		signalData.clear();
		signalData = this->signalMap[i];
		
		for(unsigned int j = 0; j < signalData.size(); j++){

			if(j > 0){
				area = area + abs(signalData.at(j) - signalData.at(j-1));
			}

			sum = sum + abs(signalData.at(j));
		}

		this->malinowskaValues.push_back(10*sum/area);
	}
	
	// zapis do pliku
	/*ofstream malinowskaTestTxt;
    malinowskaTestTxt.open("D:\\Dadm\\MójProjekt2\\malinowskaTest.txt");
	for(unsigned int i = 0; i < this->malinowskaValues.size(); i++){
	    	
	    malinowskaTestTxt << this->malinowskaValues.at(i) << endl;
	}
    malinowskaTestTxt.close();*/
}

